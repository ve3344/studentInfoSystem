#pragma once
#include<stdio.h>
#include<stdlib.h>
char *toString(int num) {
    char buff[16];
    printf(buff,"%d",num);
    return buff;
}
int strwid(const char *text) {
    int en=0,cn=0;
    while(*text) {
        if (*text<0) {
            cn++;
        } else {
            en++;
        }
        text++;
    }
    return en+2.0*cn/2;
}
int strwid(int num) {
    int len=0;
    while(num>=1) {
        num/=10;
        len++;
    }
    return len;
}
class CounterClass{
public:
    static int count;
CounterClass(){
    count++;
}
~CounterClass(){
    count--;
}

};
int CounterClass::count=0;
