//
// Created by Mark Hsu on 2020/11/3.
//

#include <cmath>
#include <string>
#include "IEEE754.h"

using std::to_string;

IEEE754::IEEE754() {
    setNum(0);
}

IEEE754::IEEE754(float num) {
    setNum(num);
}

IEEE754::IEEE754(string _s, string _e, string _m) {
    setIEEE754(move(_s), move(_e), move(_m));
}

IEEE754::IEEE754(int _s, int _e, int _m) {
    setIEEE754(_s, _e, _m);
}

void IEEE754::setNum(float num) {
    this->number = num;
    if (num == 0) {
        this->s = bitset<1>(0);
        this->e = bitset<8>(0);
        this->m = bitset<23>(0);
        return;
    }

    // convert sign
    if (num < 0) {
        this->s = bitset<1>(1);
        num = fabs(num);
    } else
        this->s = bitset<1>(0);

    if (num < pow(2.0, -126)) { // denormalized
        this->e = bitset<8>(0);
        num *= pow(2.0, 126);

        string fracStr;
        while (num != 0) {
            float intTemp;
            num = modf(num * 2.0, &intTemp);
            fracStr += to_string((int) intTemp);
            if (num > 1)
                num -= 1;
        }
        if (fracStr.empty())
            fracStr = "0";
        while (fracStr.size() < 23)
            fracStr.push_back('0');
        this->m = bitset<23>(fracStr);
    } else {
        float intPart;
        float fracPart = modf(num, &intPart);

        // convert integer part to binary format
        string intStr;
        while (intPart / 2.0 >= 1) {
            intStr += to_string((int) intPart % 2);
            intPart = floor(intPart / 2.0);
        }
        intStr += to_string((int) intPart % 2);
        reverse(intStr);

        // convert fraction part to binary format
        string fracStr;
        while (fracPart != 0) {
            float intTemp;
            fracPart = modf(fracPart * 2.0, &intTemp);
            fracStr += to_string((int) intTemp);
            if (fracPart > 1)
                fracPart -= 1;
        }
        if (fracStr.empty())
            fracStr = "0";

        string result;
        for (int i = 1; i < intStr.size(); i++)
            result += intStr[i];
        for (int i = 0; i < fracStr.size(); i++) {
            if (result.size() > 23)
                break;
            result += fracStr[i];
        }
        while (result.size() < 23)
            result.push_back('0');
        this->m = bitset<23>(result);
        this->e = intStr.size() - 1 + 127;
    }
}


void IEEE754::setIEEE754(int _s, int _e, int _m) {
    this->s = bitset<1>(_s);
    this->e = bitset<8>(_e);
    this->m = bitset<23>(_m);
    this->calcDecimal();
}

void IEEE754::setIEEE754(string _s, string _e, string _m) {
    this->s = bitset<1>(_s);
    this->e = bitset<8>(_e);
    this->m = bitset<23>(_m);
    this->calcDecimal();
}

float IEEE754::getDecimal() {
    return this->number;
}

string IEEE754::getBinary() {
    return this->s.to_string() + " " + this->e.to_string() + " " + this->m.to_string();
}

IEEE754 IEEE754::operator+(const IEEE754 &_num) {
    this->number += _num.number;
    this->setNum(number);
    return *this;
}

IEEE754 IEEE754::operator-(const IEEE754 &_num) {
    this->number -= _num.number;
    this->setNum(number);
    return *this;
}

IEEE754 IEEE754::operator*(const IEEE754 &_num) {
    this->number *= _num.number;
    this->setNum(number);
    return *this;
}

IEEE754 IEEE754::operator/(const IEEE754 &_num) {
    this->number /= _num.number;
    this->setNum(number);
    return *this;
}

IEEE754 IEEE754::operator++(int) {
    if (this->m.to_string() == "11111111111111111111111") {
        this->e = this->e.to_ulong() + 1;
    }
    this->m = this->m.to_ulong() + 1;
    this->setIEEE754(this->s.to_string(), this->e.to_string(), this->m.to_string());
    return *this;
}

IEEE754 IEEE754::operator--(int) {
    if (this->m.to_ulong() == 0) {
        this->e = this->e.to_ulong() - 1;
    }
    this->m = this->m.to_ulong() - 1;
    this->setIEEE754(this->s.to_string(), this->e.to_string(), this->m.to_string());
    return *this;
}


void IEEE754::swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void IEEE754::reverse(string &str) {
    for (int i = 0, n = str.size() - 1; i < str.size() / 2; i++, n--)
        swap(&str[i], &str[n]);
}

void IEEE754::calcDecimal() {
    if (this->e.to_ulong() == 0) { // denormalized
        this->number = (int) this->m.to_ulong() / pow(2.0, 23) * pow(2.0, -126);
    } else {
        this->number = 1.0 * pow(2.0, (int) this->e.to_ulong() - 127) +
                       (int) this->m.to_ulong() / pow(2.0, 23) * pow(2.0, (int) this->e.to_ulong() - 127);
    }
    if (this->s.to_ulong())
        this->number *= -1;
}
