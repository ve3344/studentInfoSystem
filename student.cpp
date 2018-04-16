#include "lesson.cpp"
#include <string.h>

using namespace std;
class Student :public CounterClass{
    public:
    int id;
    char name[24];
    bool male;
    int age;
    int room;
    char phone[12+10];
    Linklist<Lesson> lessons;
public:

    Student() {

    }
    Student(int i,const char *nam,bool gen,int ag,int roo,const char *pho) {
        id=i;
        strcpy(name,nam);
        male=gen;
        age=ag;
        room=roo;
        strcpy(phone,pho);
    }

    ~Student() {
    //printf("d(student) ");
    }
protected:
private:
};

