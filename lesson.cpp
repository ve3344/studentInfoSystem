

#pragma once
#include<string.h>
#include"utils.cpp"

class Restudy :public CounterClass{
    public:
    int term;
    int score;
public:
    Restudy(){}
    Restudy(int ter,int sco){
        term=ter;
        score=sco;
    }
    ~Restudy(){
    }
protected:
private:
};


class Lesson :public CounterClass{

public:
    Linklist<Restudy> restudies;
    int id;
    char name[64];
    int ordinaryScore,examScore,syntheticalScore;
    int credits;

    Lesson(){}
    Lesson(int i,const char* nam,int ord,int exa,int syn,int cre){
        id=i;
        strcpy(name,nam);
        ordinaryScore=ord;
        examScore=exa;
        syntheticalScore=syn;
        credits=cre;
    }
    ~Lesson(){
    //printf("d(lesson) ");
    }
protected:
private:
};

