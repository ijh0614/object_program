#pragma once
#include "IOInterface.h"
#include <iostream>
#include <string>

using namespace std;

class Subject:public IOInterface {
protected:
    string _name; // 과목이름
    int Hakjum;     // 과목학점
    string Grade="hi";   // 과목등급
    float GPA;      // 과목 평점


public:
    Subject();
    //과목명, 학점, 등급 
    void inputData();
    void calGPA();//평점 계산
    float getGPA();//평점 반환
    void printData() const;
    void modify();//수정함수.
    string getName();
};