#include <iostream>

#include "infoSystem.cpp"
#include "console.cpp"
#include "activity.cpp"
#include "lessonListPage.cpp"
#include "studentListPage.cpp"
#include "inputPage.cpp"


using namespace std;
class ChooseActivity:public FrameActivity {
    const static int CHOOSE_COUNT =3;

    char* operationTitles[CHOOSE_COUNT]= {
        " 学 生 列 表 ",
        " 录 入 学 生 ",
//        " 插 入 ",
//        " 删 除 ",
//        " 查 询 ",
        " 退 出 "
    };
    int selected=0;
public:
    void onNavKeyClick(int key) {
        if (key==Key::DOWN) {
            selected=selected<CHOOSE_COUNT-1?selected+1:0;

        } else if (key==Key::UP) {
            selected=selected>0?selected-1:CHOOSE_COUNT-1;
        }
        update();
    }
    void onKeyClick(int key) {
        if (key==Key::ENTER) {
            switch(selected) {
            case 0:
                activityManager.run(studentListPage);
                break;
            case 1:
                activityManager.run(inputPage);
                break;
            case 2:
                activityManager.finish();
                break;
            }

        }
        if (key==Key::ESC) {
            activityManager.finish();
        }
    }
    void onDraw() {


        console.gotoxy(0,0);
        console.color(0,14);
        printf("w=%d h=%d \n",console.width(),console.height());
        console.color(0,7);
        printHorizenCenter("教务信息管理系统",0,console.width(),1);

        for (int row=0; row<CHOOSE_COUNT; row++) {
            console.color(0,selected==row?8:7);
            printHorizenCenter(operationTitles[row],0,console.width(),4+row*2);

        }
    }



} mainPage;


int main() {
    console.init();
    console.setTitle("教务信息管理系统");
    console.setWinSize(160,40);


    infoSystem.init();
    activityManager.run(mainPage);
    infoSystem.save();
    infoSystem.quit();
    console.quit();
    return 0;
}
