
#pragma once
#include"utils.cpp"
#include"lesson.cpp"
class LessonListActivity:public FrameActivity {

    int selected=0;
    const static int LESSON_INFO_COUNT=8;
    char* studentInfoTitles[LESSON_INFO_COUNT]= {
        "  序  号  ",
        "  编  号  ",
        "  名  称  ",
        "  考试成绩  ",
        "  平时成绩  ",
        "  综合成绩  ",
        "  学  分  ",
        "  重  修  "
    };
    int width=0,height=0;
    int page=0;
    Student *student;
public:
    void setStudent(Student *stu) {
        student=stu;
    }
    void onCreate()override {
        setBackColor(15);
        width=console.width()*0.8;
        height=console.height()-3;
        selected=0;
    }
    int toIndex(int pos) {
        return pos+height*page;
    }
    void onNavKeyClick(int key) {
        if (student->lessons.empty()) {
            return;
        }
        int old=selected;
        if (key==Key::DOWN) {
            if (toIndex(selected)< student->lessons.length()-1) {
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
            updateListItem(toIndex(old),student->lessons.get(toIndex(old)));
        }

        updateListItem(toIndex(selected),student->lessons.get(toIndex(selected)));
    }


    void onKeyClick(int key) {
        if (key==Key::ESC) {
            activityManager.finish();
        }

    }

    void updateListItem(int index,Lesson* les) {
        int wid=width/LESSON_INFO_COUNT;
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
        printHorizenCenter(les->id,1*wid,2*wid,position+3);
        printHorizenCenter(les->name,2*wid,3*wid,position+3);
        printHorizenCenter(les->ordinaryScore,3*wid,4*wid,position+3);
        printHorizenCenter(les->examScore,4*wid,5*wid,position+3);
        printHorizenCenter(les->syntheticalScore,5*wid,6*wid,position+3);
        printHorizenCenter(les->credits,6*wid,7*wid,position+3);
        printHorizenCenter(les->restudies.empty()?"否":"是",7*wid,8*wid,position+3);
        if (!les->restudies.empty()) {
            drawRestudy(les->restudies);
        } else {
            console.color(0,15);
            for (int i=0; i<paintH+2; i++) {

                printBg(width,console.width()-1,i+3);
            }
        }
    }
    int paintH=0;
    void drawRestudy(Linklist<Restudy>& ress) {
        console.color(0,11);
        printBg(width,console.width()-1,3);

        printHorizenCenter("重修情况",width,console.width(),3);
        int wid=(console.width()-1-width)/2;
        printBg(width,console.width()-1,4);
        printHorizenCenter("重修学期",width,width+wid,4);
        printHorizenCenter("重修分数",width+wid,width+wid*2,4);
        paintH=0;
        ress.seekList([&](int pos,Restudy* res) {

            printBg(width,console.width()-1,pos+5);
            paintH++;
            printHorizenCenter(res->term,width,width+ wid,pos+5);
            printHorizenCenter(res->score,width+wid,width+ wid*2,pos+5);
            return false;
        });
    }

    int getPageCount() {
        return student->lessons.length()/height;
    }
    void onDraw() {

        console.color(0,7);
        printHorizenCenter(" 课 程 列 表 ",0,console.width(),0);

        int wid=width/LESSON_INFO_COUNT;
        console.color(0,15);
        printHorizenCenter(" 学号: ",0,wid,1);
        printHorizenCenter(student->id,wid,2*wid,1);
        printHorizenCenter(" 姓名: ",3*wid,4*wid,1);
        printHorizenCenter(student->name,4*wid,5*wid,1);


        console.color(0,7);
        for (int row=0; row<LESSON_INFO_COUNT; row++) {
            printHorizenCenter(studentInfoTitles[row],row*wid,(row+1)*wid,2);
        }
        char buff[24];
        sprintf(buff,"第 %d 页   共 %d 页",page+1,getPageCount()+1);
        printHorizenCenter(buff,0,console.width(),console.height());
        student->lessons.seekList([&](int position,Lesson* les) {
            if (position<page*height) {
                return false;
            } else if (position>=(page+1)*height) {
                return true;
            } else {
                updateListItem(position,les);
                return false;
            }
        });
        if (!student->lessons.empty()&&!student->lessons.get(0)->restudies.empty()) {
            updateListItem(0,student->lessons.get(0));
        }


    }




} lessonListPage;
