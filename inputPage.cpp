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
        printHorizenCenter("��Enter¼��",0,console.width(),console.height()/2-1);
        printHorizenCenter("��Esc�˳�",0,console.width(),console.height()/2);


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
        printf("������ѧ������:");
        gets(buff);
        sscanf(buff,"%d",&studentCount);

        for(int s=0; s<studentCount; s++) {

            console.color(0,12);
            printf("\t�������%d��ѧ����Ϣ: ѧ�� ���� �Ա� ���� ����� �绰\n\t",s+1);
            gets(buff);
            stu=new Student();
            sscanf(buff,"%d %s %d %d %d %s\n",&stu->id,stu->name,&stu->male,&stu->age,&stu->room,stu->phone);
            infoSystem.students.pushBack(stu);

            int lessonCount=0;
            printf("\t�����롮%s���Ŀγ�����:",stu->name);
            gets(buff);
            sscanf(buff,"%d",&lessonCount);
            for(int i=0; i<lessonCount; i++) {
                console.color(0,13);
                printf("\t\t�������%d�ſγ���Ϣ: ��� ���� ƽʱ���� ���Է��� �ۺϷ��� ѧ��\n\t\t",i+1);
                gets(buff);
                les=new Lesson();
                sscanf(buff,"%d %s %d %d %d %d\n",&les->id,les->name,&les->ordinaryScore,&les->examScore,&les->syntheticalScore,&les->credits);
                stu->lessons.pushBack(les);
                printf("\t\t�����롮%s�����޴���:",les->name);
                gets(buff);

                int restudyCount=0;
                sscanf(buff,"%d",&restudyCount);
                for(int j=0; j<restudyCount; j++) {
                    console.color(0,14);
                    printf("\t\t\t������%s��%d��������Ϣ: ѧ�� ���� \n\t\t\t",les->name,i+1);
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
        printHorizenCenter("��¼��ѧ��",0,console.width(),console.height()/2);
        getch();
        activityManager.finish();
        //update();
    }


} inputPage;
