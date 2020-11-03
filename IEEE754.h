//
// Created by Mark Hsu on 2020/11/3.
// IEEE 754 floating number (32-bit) library

#ifndef IEEE754_IEEE754_H
#define IEEE754_IEEE754_H

#include <bitset>
#include <string>

using std::string;
using std::bitset;

class IEEE754 {
public:
    IEEE754();

    explicit IEEE754(float num);

    IEEE754(string _s, string _e, string _m);

    IEEE754(int _s, int _e, int _m);

    void setNum(float num);

    void setIEEE754(int _s, int _e, int _m);

    void setIEEE754(string _s, string _e, string _m);

    float getDecimal();

    string getBinary();

    IEEE754 operator+(const IEEE754 &_num);

    IEEE754 operator-(const IEEE754 &_num);

    IEEE754 operator*(const IEEE754 &_num);

    IEEE754 operator/(const IEEE754 &_num);

    IEEE754 operator++(int);

    IEEE754 operator--(int);

private:
    bitset<1> s;
    bitset<8> e;
    bitset<23> m;
    float number{};

    void swap(char *a, char *b);

    void reverse(string &str);

    void calcDecimal();
};


#endif //IEEE754_IEEE754_H
