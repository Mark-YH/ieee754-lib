//
// Created by Mark Hsu on 2020/11/3.
//
#include <iostream>
#include <iomanip>
#include "IEEE754.h"

using namespace std;

void exam1a() {
    IEEE754 max("0", "11111110", "11111111111111111111111");
    IEEE754 min("1", "11111110", "11111111111111111111111");
    cout << "vvv 1a answer vvv" << endl;
    cout << "max: " << max.getDecimal() << endl;
    cout << "min: " << min.getDecimal() << endl;
    cout << "^^^ 1a answer ^^^" << endl;
}

void exam1b() {
    IEEE754 p("0", "00000000", "00000000000000000000001");
    IEEE754 n("1", "00000000", "00000000000000000000001");
    cout << "vvv 1b answer vvv" << endl;
    cout << "0+: " << p.getDecimal() << endl;
    cout << "0-: " << n.getDecimal() << endl;
    cout << "^^^ 1b answer ^^^" << endl;
}

void exam1c() {
    IEEE754 p("0", "01111111", "00000000000000000000001");
    IEEE754 n("0", "01111110", "11111111111111111111111");
    cout << "vvv 1c answer vvv" << endl;
    if (p.getDecimal() - 1.0 > 1.0 - n.getDecimal()) {
        cout << "1-: " << n.getDecimal() << endl;
    } else if (p.getDecimal() - 1.0 < 1.0 - n.getDecimal()) {
        cout << "1+: " << p.getDecimal() << endl;
    } else {
        cout << "1+ = 1- = " << n.getDecimal() << endl;
    }
    cout << "^^^ 1c answer ^^^" << endl;
}

void exam1d() {
    float a = 16777216;
    float b = 1;
    cout << "vvv 1d answer vvv" << endl;
    cout << (float) a + b << endl;
    cout << (float) a - b << endl;
    cout << "^^^ 1d answer ^^^" << endl;
}

void exam1f() {
    IEEE754 p("0", "11111110", "11111111111111111111111");
    IEEE754 n("1", "11111110", "11111111111111111111111");
    cout << "vvv 1f answer vvv" << endl;
    cout << "real number: " << n.getDecimal() << " ~ " << p.getDecimal() << endl;
    n.setIEEE754("0", "00000000", "00000000000000000000001");
    cout << "positive real number: " << n.getDecimal() << " ~ " << p.getDecimal() << endl;
    cout << "^^^ 1f answer ^^^" << endl;
}

void exam1g() {
    IEEE754 a(0, 0, 1);
    cout << "vvv 1g answer vvv" << endl;
    cout << a.getDecimal() << endl;
    cout << "^^^ 1g answer ^^^" << endl;
}

void exam1h() {
    unsigned long long count = 0;
    IEEE754 a(powf(2.0, -149));

    // including 2^-149 and excluding 2^-125
    while (a.getDecimal() < powf(2.0, -125)) {
        a++;
        count++;
    }
    cout << "vvv 1h answer vvv" << endl;
    // considering negative numbers (*2) and zero (+1)
    cout << count * 2 + 1 << endl;
    cout << "^^^ 1h answer ^^^" << endl;
}

void exam1i() {
    unsigned long long count = 0;
    IEEE754 a("0", "11111110", "00000000000000000000000");
    IEEE754 b("0", "11111110", "00000000000000000000001");
    cout << "vvv 1i answer vvv" << endl;
    cout << b.getDecimal() - a.getDecimal() << endl;
    cout << "^^^ 1i answer ^^^" << endl;
}

void exam1j() {
    unsigned long long count = 0;
    IEEE754 a("0", "11111110", "00000000000000000000000");

    while (a.getDecimal() < powf(2.0, 128) - powf(2.0, 104)) {
        a++;
        count++;
    }
    cout << "vvv 1j answer vvv" << endl;
    // excluding 2^127 and 2^128 - 2^104 (-1)and considering negative numbers (*2)
    cout << (count - 1) * 2 << endl;
    cout << "^^^ 1j answer ^^^" << endl;
}


int main() {
    cout << setprecision(50);// << fixed;
    exam1a();
    exam1b();
    exam1c();
    exam1d();
    exam1f();
    exam1g();
    exam1h();
    exam1i();
    exam1j();
    return 0;
}
