#pragma once
#include <string>
#include <iostream>

using namespace std;

class IOInterface {
protected:
    string _name;
    virtual string getName() = 0;
    inline void inputValue(int& num);
    inline void inputValue(string& str);
};

inline void IOInterface::inputValue(int& num) {
    cin >> num;
    cin.ignore();
};
inline void IOInterface::inputValue(string& str) {
    getline(cin, str);
};