#pragma once
#include <windows.h>
#include <time.h>
#include <conio.h>

typedef HWND (WINAPI *PROCGETCONSOLEWINDOW)();
PROCGETCONSOLEWINDOW GetConsoleWindow;

class Key {
public:
    const static int UP=72;
    const static int DOWN=80;
    const static int LEFT=75;
    const static int RIGHT=77;
    const static int ENTER=13;
    const static int ESC=27;
};


class Console {

    int w=0,h=0;

    void updateSize(){
        CONSOLE_SCREEN_BUFFER_INFO scbi;
        GetConsoleScreenBufferInfo(out, &scbi);
        this->w=scbi.srWindow.Right-scbi.srWindow.Left;
        this->h=scbi.srWindow.Bottom-scbi.srWindow.Top;
    }

    void setWindowBody(int x,int y,int w,int h) {
        HWND hWnd = GetConsoleWindow();
        SetWindowLongPtr(hWnd,GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
        SetWindowPos(hWnd,NULL,x,y,w, h,NULL);
updateSize();

    }

public:
    HANDLE out,in;
    Console() {}

    void init() {
        srand(time(NULL));
        in=GetStdHandle(STD_INPUT_HANDLE);
        out=GetStdHandle(STD_OUTPUT_HANDLE);

        HMODULE hKernel32 = GetModuleHandle("kernel32");
        GetConsoleWindow = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32,"GetConsoleWindow");
        setWindowBody(0,0,0,0);
        setWinSize(100,30);
        system("color f0");
    }
        void setWinSize(int colum,int row){
        char cmd[36];
        sprintf(cmd,"mode con cols=%d lines=%d",colum,row);
        system(cmd);
        updateSize();
    }
    void setTitle(const char *title){
        SetConsoleTitle(title);
    }

    int width() {
        return w;
    } int height() {
        return h;
    }

    void quit() {
        CloseHandle(out);
        CloseHandle(in);
    }
    void gotoxy(int x,int y) {
        COORD pos= {x,y};
        SetConsoleCursorPosition(out,pos);
    }
    void showCursor(bool show) {
        showCursor(out,show);
    }
    static void showCursor(HANDLE out,bool show) {
        CONSOLE_CURSOR_INFO info;
        GetConsoleCursorInfo(out, &info);
        info.bVisible = show;
        SetConsoleCursorInfo(out, &info);
    }
    void color(short fg,short bg) {
        SetConsoleTextAttribute(out,fg+bg*0x10);
    }

    void clearScreen() {
        system("cls");
    }
    inline static float now() {
        return ((float)clock())/CLOCKS_PER_SEC;
    }
} console;
