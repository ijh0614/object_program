#pragma once
#include "subject.h"
#include <iomanip>


Subject::Subject() {
    _name = "Korean";
    Hakjum = 3;
    Grade = "A+";
}

void Subject::inputData() {
    cout << "교과목명 : ";
    inputValue(_name);//Sub[i]._name 으로는 접근할 수 없음!!

    cout << "과목 학점 : ";
    inputValue(Hakjum);

    //ABC같은 등급 입력
    cout << "과목 등급 : ";
    inputValue(Grade);
}

float Subject::getGPA() {
    if (Grade == "A+")
    {
        return 4.5 * Hakjum;
    }
    else if (Grade == "A0" || Grade == "A")
    {
        return 4.0 * Hakjum;
    }
    else if (Grade == "B+")
    {
        return 3.5 * Hakjum;
    }
    else if (Grade == "B0" || Grade == "B")
    {
        return 3.0 * Hakjum;
    }
    else if (Grade == "C+")
    {
        return 2.5 * Hakjum;
    }
    else if (Grade == "C0" || Grade == "C")
    {
        return 2.0 * Hakjum;
    }
    else if (Grade == "D+")
    {
        return 1.5 * Hakjum;
    }
    else if (Grade == "D0" || Grade == "D")
    {
        return 1.0 * Hakjum;
    }
    else if (Grade == "F")
    {
        return 0.0;
    }
    else
    {
        return -1;
    }
}

void Subject::calGPA() {
    GPA = getGPA();
    
    //GPA계산 후처리
    if (GPA < 0)
    {
        cout << "잘못된 형식의 등급입니다. 프로그램을 종료합니다.";
        exit(1);
    }
}

void Subject::printData() const {
    cout << right << setw(12) << _name << setw(12) << Hakjum << setw(12) << Grade << setw(12) << GPA << endl;
}

void Subject::modify(){
    cout << "*<" << _name << ", 학점 : " << Hakjum << ", 등급 : " << Grade << ">의 정보를 수정하세요" << endl;
    cout << "교과목명 : ";
    inputValue(_name);

    cout << "과목학점 : ";
    inputValue(Hakjum);

    cout << "과목등급 : ";
    inputValue(Grade);

    calGPA();
}

string Subject::getName(){
    return _name;
}