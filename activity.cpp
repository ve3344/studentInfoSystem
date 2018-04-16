#pragma once
#include "console.cpp"
#include "utils.cpp"
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include<unistd.h>
#include<unistd.h>
class Activity {
protected:
    enum Status {
        PREPARED,
        RUNNING,
        PAUSE,
        FINISHED

    };
    Status status;
    bool keyBlock=true;
    bool handleKey=true;
    virtual void create() {
        console.showCursor(false);
        onCreate();
    }
    virtual void destroy() {
    }
    virtual void loop() {

        listenKey();
        console.gotoxy(0,0);
        onDraw();
    }
public:
    void printBg(int start,int end,int y) {
        end=min(end,console.width());
        console.gotoxy(start,y);
        char *text=new char[1+end-start];
        memset(text,' ',end-start);
        text[end-start]='\0';
        printf("%s",text);
        delete text;
    }

        void printHorizenCenter(const char *text,int start,int end,int y) {
        end=min(end,console.width());
        console.gotoxy((start+end-strwid(text))/2,y);
        printf("%s",text);
    }
        void printHorizenCenter(int num,int start,int end,int y) {
        end=min(end,console.width());
        console.gotoxy((start+end-strwid(num))/2,y);
        printf("%d",num);
    }
    void print(char *text,int x,int y) {
        console.gotoxy(min(x,console.width()),min(y,console.height()-1));
        printf("%s",text);
    }

void setHandleKey(bool b){
    handleKey=b;
}
public:
    Activity() {}

    void setKeyBlock(bool b) {
        keyBlock=b;
    }

    virtual void onCreate() {}
    virtual void onResume() {}
    virtual void onDraw() {}
    virtual void onKeyClick(int key) {}
    virtual void onNavKeyClick(int key) {}
protected:
    virtual void draw() {}
    virtual void update() {}
    friend class ActivityManager;
    void finish() {
        status=FINISHED;
        destroy();
    }
    void resume() {
        if (status!=PAUSE) {
            create();
        }
        status=RUNNING;
        onResume();
        update();
        run();
    }
    void pause() {
        status=PAUSE;
    }
    void run() {

        while(status==RUNNING) {
            loop();
        }
    }
    void listenKey() {
 if (!handleKey){
    return;
 }
        int key;
        if (keyBlock) {
            key=getch();
            if (kbhit()) {
                onNavKeyClick(getch());
            } else {
                onKeyClick(key);
            }
        } else {
            if (kbhit()) {
                key=getch();
                if (kbhit()) {
                    onNavKeyClick(getch());
                } else {
                    onKeyClick(key);
                }
            }

        }
    }


};




class FrameActivity:public Activity {
    const static int Frame_BUFF_SIZE=2048;
    char static Frame_data[Frame_BUFF_SIZE];
    COORD coord= {0,0};
    DWORD bytes=0;
    HANDLE outBuff;
    int scrollY=0;
    const static int FRAME_PER_SECOND=20;
    int frame=0,fps=0;
    float ftimer=0;
    int bg=7;

    void create()override {
        Activity::create();
        outBuff = CreateConsoleScreenBuffer(
                      GENERIC_READ | GENERIC_WRITE,
                      FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,
                      CONSOLE_TEXTMODE_BUFFER,NULL    );
        Console::showCursor(outBuff,false);
        onCreate();
        draw();
    }
    void destroy() override {
        CloseHandle(outBuff);
        outBuff=NULL;
        //console.clearScreen();
    }
    void draw() {
        console.color(0,bg);
        console.clearScreen();
        console.gotoxy(0,scrollY);
        onDraw();
        coord.Y=scrollY;
        SetConsoleCursorPosition(outBuff,COORD({0,scrollY}));
        ReadConsoleOutputCharacterA(console.out, Frame_data, Frame_BUFF_SIZE, coord, &bytes);
        WriteConsoleOutputCharacterA(outBuff, Frame_data, Frame_BUFF_SIZE, coord, &bytes);
    }
    void loop() override {
        float timer=console.now();
        listenKey();

        if ((console.now()-timer)*FRAME_PER_SECOND<1.0) {
            usleep(((1.0f/FRAME_PER_SECOND)-(console.now()-timer))*1000000);
            timer=console.now();
        }

        frame++;
        if (console.now()-ftimer>1) {
            ftimer=console.now();
            fps=frame;
            frame=0;
            onSecond();
        }

    }
public:
    FrameActivity():Activity() {
        keyBlock=(false);
    }
    int getFps() {
        return fps;
    }
    void setBackColor(int b) {
        bg=b;
    }
    void scroll(int dy) {
        scrollY+=dy;
    }
    void update() {
        draw();
    }
    virtual void onSecond() {

    }
        void moveText(int dx, int dy, SMALL_RECT rc) {
        COORD crDest = {rc.Left+dx, rc.Top+dy};

        CONSOLE_SCREEN_BUFFER_INFO bInfo;
        GetConsoleScreenBufferInfo(console.out, &bInfo );
        CHAR_INFO chFill;
        chFill.Attributes = bInfo.wAttributes;
        chFill.Char.AsciiChar = '+';
        ScrollConsoleScreenBuffer(console.out, &rc, NULL, crDest, &chFill);
    }
    ~FrameActivity() {}
protected:

};

class ActivityManager {
    int top=0;
    const static int MAX=48;
    Activity* activities[MAX];
    bool running=true;
public:
    void run(Activity &a) {
        if (top>0) {
            activities[top-1]->pause();
        }
        if (top<MAX-1) {
            activities[top++]=&a;
            a.resume();
        }
        console.clearScreen();
    }
    void finish() {
        if (top>0) {
            activities[top-1]->finish();
            top--;
            if (top>0) {
                activities[top-1]->resume();
            }
        }


    }

} activityManager;
char FrameActivity:: Frame_data[Frame_BUFF_SIZE];







