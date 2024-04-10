//
//  testnewMap.cpp
//  Project2V1
//
//  Created by Devansh Mishra on 23/01/24.
//

#include <stdio.h>
#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

void testForSizeAndEmpty() {
    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
    cout << "Passed all tests" << endl;
}

void testForInsert() {
    Map mm;
    mm.insert("Little Ricky", 3.206);
    mm.insert("Ethel", 3.538);
    mm.insert("Ricky", 3.350);
    mm.insert("Lucy", 2.956);
    mm.insert("Ethel", 3.539);
    mm.insert("Fred", 2.956);
    mm.insert("Lucy", 2.956);
    assert(mm.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
    string x;
    double y;
    mm.get(0, x, y);
    assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
    mm.get(4, x, y);
    assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
    mm.get(2, x, y);
    assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
    assert(y == 3.206);  // the value corresponding to the key "Little Ricky"
    cout << "Passed all tests" << endl;
}

void testForSwap() {
    Map m1;
    m1.insert("Fred", 2.956);
    assert(m1.size() == 1);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
            m2.size() == 1  &&  m2.contains("Fred"));
    cout << "Passed all tests" << endl;
}

void emptyStringTest() {
    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
                gpas.contains(""));
    string k;
    double v;
    assert(gpas.get(1, k, v)  &&  k == "Ethel");
    assert(gpas.get(0, k, v)  &&  k == "");
    cout << "Passed all tests" << endl;
}

void test()
        {
            Map m;
            assert(m.insert("Fred", 2.956));
            assert(m.insert("Ethel", 3.538));
            assert(m.size() == 2);
            ValueType v = 42;
            assert(!m.get("Lucy", v)  &&  v == 42);
            assert(m.get("Fred", v)  &&  v == 2.956);
            v = 42;
            KeyType x = "Lucy";
            assert(m.get(0, x, v)  &&
                   ((x == "Fred"  &&  v == 2.956)  ||  (x == "Ethel"  &&  v == 3.538)));
            KeyType x2 = "Ricky";
            assert(m.get(1, x2, v)  &&
                   ((x2 == "Fred"  &&  v == 2.956)  ||  (x2 == "Ethel"  &&  v == 3.538))  &&
                   x != x2);
    cout << "Passed all tests" << endl;
        }

