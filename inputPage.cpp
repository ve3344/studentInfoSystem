#pragma once
#include"console.cpp"
class InputActivity:public FrameActivity {
public:
    Student *stu;
    Lesson *les;
    Restudy *res=NULL;
    char buff[128];

    void onKeyClick(int key) {
        if (key==Key::ESC) {
            activityManager.finish();
        }
        if (key==Key::ENTER) {
            input();
        }

    }

    void onDraw() {
        console.color(0,15);
        printHorizenCenter("按Enter录入",0,console.width(),console.height()/2-1);
        printHorizenCenter("按Esc退出",0,console.width(),console.height()/2);


    }
    void input() {
        stu=NULL;
        les=NULL;
        res=NULL;

        setHandleKey(false);
        console.clearScreen();
        console.showCursor(true);
        console.gotoxy(0,0);
        console.color(0,11);
        int studentCount=0;
        printf("请输入学生数量:");
        gets(buff);
        sscanf(buff,"%d",&studentCount);

        for(int s=0; s<studentCount; s++) {

            console.color(0,12);
            printf("\t请输入第%d个学生信息: 学号 名字 性别 年龄 房间号 电话\n\t",s+1);
            gets(buff);
            stu=new Student();
            sscanf(buff,"%d %s %d %d %d %s\n",&stu->id,stu->name,&stu->male,&stu->age,&stu->room,stu->phone);
            infoSystem.students.pushBack(stu);

            int lessonCount=0;
            printf("\t请输入‘%s’的课程数量:",stu->name);
            gets(buff);
            sscanf(buff,"%d",&lessonCount);
            for(int i=0; i<lessonCount; i++) {
                console.color(0,13);
                printf("\t\t请输入第%d门课程信息: 编号 名字 平时分数 考试分数 综合分数 学分\n\t\t",i+1);
                gets(buff);
                les=new Lesson();
                sscanf(buff,"%d %s %d %d %d %d\n",&les->id,les->name,&les->ordinaryScore,&les->examScore,&les->syntheticalScore,&les->credits);
                stu->lessons.pushBack(les);
                printf("\t\t请输入‘%s’重修次数:",les->name);
                gets(buff);

                int restudyCount=0;
                sscanf(buff,"%d",&restudyCount);
                for(int j=0; j<restudyCount; j++) {
                    console.color(0,14);
                    printf("\t\t\t请输入%s第%d次重修信息: 学期 分数 \n\t\t\t",les->name,i+1);
                    gets(buff);
                    res=new Restudy();
                    sscanf(buff,"%d %d\n",&res->term,&res->score);
                    les->restudies.pushBack(res);
                }
            }
        }

        console.showCursor(false);
        setHandleKey(true);

        console.color(10,15);
        console.clearScreen();
        printHorizenCenter("已录入学生",0,console.width(),console.height()/2);
        getch();
        activityManager.finish();
        //update();
    }


} inputPage;
