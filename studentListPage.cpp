#pragma once
#include"utils.cpp"
class StudentListActivity:public FrameActivity {

    int selected=0;
    const static int STUDENT_INFO_COUNT=7;
    char* studentInfoTitles[STUDENT_INFO_COUNT]= {
        "  序  号  ",
        "  学  号  ",
        "  名  字  ",
        "  性  别  ",
        "  年  龄  ",
        "  宿  舍  ",
        "  电  话  "
    };
    int width=0,height=0;
    int page=0;
public:
    void onCreate()override {
        setBackColor(15);
        width=80;
        height=console.height()-3;
        selected=0;
    }
    int toIndex(int pos) {
        return pos+height*page;
    }
    void onKeyClick(int key) {
        if (key==Key::ENTER&&toIndex(selected)<infoSystem.students.length()) {
            lessonListPage.setStudent(infoSystem.students.get(toIndex(selected)));
            activityManager.run(lessonListPage);
        }
        if (key==Key::ESC) {
            activityManager.finish();
        }
        if (key=='r') {
            remove();
        }
        if (key=='1') {
            infoSystem.students.sort([&](Student *s1,Student *s2){
                             return (s1->id)-(s2->id);
                             });
          update();
        } if (key=='2') {
            infoSystem.students.sort([&](Student *s1,Student *s2){
                             return (s1->age)-(s2->age);
                             });
          update();
        }
        if (key=='3') {
            infoSystem.students.sort([&](Student *s1,Student *s2){
                             return (s1->male)-(s2->male);
                             });
          update();
        }
        if (key=='4') {
            infoSystem.students.sort([&](Student *s1,Student *s2){
                             return (s1->room)-(s2->room);
                             });
          update();
        }
        if (key=='f') {
            finding=true;
            updateFind();
        }
    }
    void remove() {
        infoSystem.removeStudent(toIndex(selected));
        update();

    }
    void onNavKeyClick(int key) {
        if (infoSystem.students.empty()) {
            return;
        }

        int old=selected;
        if (key==Key::DOWN) {
            if (toIndex(selected)< infoSystem.students.length()-1) {
                selected++;
                if (selected>=height) {
                    page++;
                    selected=0;
                    update();
                    return;
                }
            }
        } else if (key==Key::UP) {
            if (toIndex(selected)>0) {
                selected--;
                if (selected<0) {
                    page--;
                    selected=0;
                    update();
                    return;
                }
            }
        } else if (key==Key::LEFT) {
            if (page>0) {
                page--;
                selected=0;
                update();
                return;
            }

        } else if (key==Key::RIGHT) {
            if (page<getPageCount()) {
                page++;
                selected=0;
                update();
                return;
            }

        }

        if (old!=selected) {
            updateListItem(toIndex(old),infoSystem.students.get(toIndex(old)));
        }
        updateListItem(toIndex(selected),infoSystem.students.get(toIndex(selected)));
    }

    bool finding=false;
    char findBuff[128];
    void updateFind() {
        if (finding) {
            console.color(0,7);
            printHorizenCenter("  查 找  (名字或学号)",width+1,console.width()-1,4);
            console.color(15,0);
            printBg(width+1,console.width()-1,5);
            console.gotoxy(width+1,5);

            setHandleKey(false);
            console.showCursor(true);
            findBuff[0]='\0';
            gets(findBuff);
            finding=false;
            find();
            console.showCursor(false);
            setHandleKey(true);
            console.color(0,15);
            printBg(width+1,console.width()-1,5);

        } else {
            console.color(0,15);
            printBg(width+1,console.width()-1,5);
        }



    }

    void find() {
        Student* result=NULL;
        int target=-1;
        int num=-1;
        if (findBuff[0]>='0'&&findBuff[0]<='9') {
            sscanf(findBuff,"%d",&num);
        }


        infoSystem.students.seekList( [&](int pos,Student*stu) {
            if (stu->id==num||strcmp(stu->name,findBuff)==0) {
                target=pos;
                result=stu;
                return true;
            }
            return false;
        } );

        if (target>=0&&target<infoSystem.students.length()) {
            setSelectedIndex(target);
            console.color(0,10);
            printHorizenCenter("找到学生:",width+1,console.width()-1,6);
            printHorizenCenter(findBuff,width+1,console.width()-1,7);
        } else {
            console.color(0,12);
            printHorizenCenter("未找到学生:",width+1,console.width()-1,6);
            printHorizenCenter(findBuff,width+1,console.width()-1,7);
        }
    }

    void setSelectedIndex(int sel) {
        selected=sel%height;
        page=sel/height;
        update();
    }
    void updateListItem(int index,Student* stu) {
        int wid=width/STUDENT_INFO_COUNT;
        int position=index;
        if (position>=height) {
            position=position%height;

        }
        if (selected==position) {
            console.color(0,14);
            printBg(0,width,position+3);
        } else {
            console.color(0,15);
            printBg(0,width,position+3);
            console.color(0,15);
        }


        printHorizenCenter(index+1,0,1*wid,position+3);
        printHorizenCenter(stu->id,1*wid,2*wid,position+3);
        printHorizenCenter(stu->name,2*wid,3*wid,position+3);
        printHorizenCenter(stu->male?"男":"女",3*wid,4*wid,position+3);
        printHorizenCenter(stu->age,4*wid,5*wid,position+3);
        printHorizenCenter(stu->room,5*wid,6*wid,position+3);
        printHorizenCenter(stu->phone,6*wid,7*wid,position+3);
    }
    int getPageCount() {
        return infoSystem.students.length()/height;
    }
    void onDraw() {

        console.color(0,7);
        printHorizenCenter(" 学 生 列 表 ",0,console.width(),0);
        int wid=width/STUDENT_INFO_COUNT;
        for (int row=0; row<STUDENT_INFO_COUNT; row++) {
            printHorizenCenter(studentInfoTitles[row],row*wid,(row+1)*wid,2);
        }
        char buff[24];
        sprintf(buff,"第 %d 页   共 %d 页",page+1,getPageCount()+1);
        printHorizenCenter(buff,0,console.width(),console.height());
        infoSystem.students.seekList([&](int position,Student* stu) {
            if (position<page*height) {
                return false;
            } else if (position>=(page+1)*height) {
                return true;
            } else {
                updateListItem(position,stu);
                return false;
            }
        });



    }




} studentListPage;
