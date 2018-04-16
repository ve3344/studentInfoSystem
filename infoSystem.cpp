#include "linklist.cpp"
#include "student.cpp"
#include "console.cpp"
#include<iostream>
using namespace std;
class InfoSystem {

public:
    Linklist<Student> students;
    InfoSystem():students() {
    }
    void init() {
        load();
    }
    void removeStudent( int pos) {
        if (students.empty()) {
            return;
        }
        Student *stu= students.remove(pos);
        if (stu) {
            stu->lessons.destroy([](int pos1,Lesson *les) {
                les->restudies.destroy([](int pos2,Restudy *res) {
                    delete res;
                });
                delete les;
            });
            delete stu;
        }
    }
    void removeLesson(Student *stu,int pos) {
        Lesson *les=stu->lessons.remove(pos);
        les->restudies.destroy([](int pos1,Restudy *res) {
            delete res;
        });
        delete les;

    }
    void removeRestudy(Lesson *les,int pos) {
        delete les->restudies.remove(pos);

    }
    void quit() {
        puts("ÊÍ·ÅÄÚ´æÖÐ...");
        students.destroy([](int pos,Student *stu) {
            stu->lessons.destroy([](int pos1,Lesson *les) {
                les->restudies.destroy([](int pos2,Restudy *res) {
                    delete res;
                });
                delete les;
            });
            delete stu;
        });
        console.clearScreen();
    }
    char *path="d:\\studentInfo.txt";
    void save() {
        FILE* f=fopen(path,"w");
        if (f==NULL) {
            puts(strerror(errno));
            getchar();
            return;
        }



        students.seekList([&](int pos,Student *stu) {
            fprintf(f,"Student:%d %s %d %d %d %s\n",stu->id,stu->name,stu->male,stu->age,stu->room,stu->phone);
            stu->lessons.seekList([&](int pos1,Lesson *les) {
                fprintf(f,"\tLesson:%d %s %d %d %d %d\n",les->id,les->name,les->ordinaryScore,les->examScore,les->syntheticalScore,les->credits);
                les->restudies.seekList([&](int pos2,Restudy *res) {
                    fprintf(f,"\t\tRestudy:%d %d\n",res->term,res->score);
                    return false;
                });
                return false;
            });
            return false;
        });

        fclose(f);
    }
    void load() {
        FILE* f=fopen(path,"r");
        if (f==NULL) {
            puts(strerror(errno));
            return;
        }
        char buff[128];
        Student *stu=NULL;
        Lesson *les=NULL;
        Restudy *res=NULL;
        while (!feof(f)) {
            buff[0]=0;
            buff[1]=0;
            buff[2]=0;
            fgets(buff,128,f);
            if (buff[2]=='R') {
                res=new Restudy();
                sscanf(buff,"\t\tRestudy:%d %d\n",&res->term,&res->score);
                les->restudies.pushBack(res);
            } else if (buff[1]=='L') {
                les=new Lesson();
                sscanf(buff,"\tLesson:%d %s %d %d %d %d\n",&les->id,les->name,&les->ordinaryScore,&les->examScore,&les->syntheticalScore,&les->credits);
                stu->lessons.pushBack(les);
            } else if (buff[0]=='S') {
                stu=new Student();
                sscanf(buff,"Student:%d %s %d %d %d %s\n",&stu->id,stu->name,&stu->male,&stu->age,&stu->room,stu->phone);
                students.pushBack(stu);

            }
        }

        fclose(f);
    }

} infoSystem;
