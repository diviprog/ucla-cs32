//
//  testMap.cpp
//  Project2V2
//
//  Created by Devansh Mishra on 29/01/24.
//

#include "Map.h"
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

void basicInsert() {
    Map m;
    m.insert("Hi", 10);
    m.insert("Me", 5);
    assert(m.size() == 2);
    cout << "Passed all tests" << endl;
}

void testContains() {
    Map m;
    m.insert("Hi", 10);
    assert(m.contains("Hi") == true);
    assert(m.contains("Devansh") == false);
    cout << "Passed all tests" << endl;
}

void testEmpty() {
    Map m;
    assert(m.empty() == true);
    m.insert("Hi", 10);
    assert(m.empty() == false);
    cout << "Passed all tests" << endl;
}

void testErase() {
    Map m;
    m.insert("Hi", 10);
    assert(m.size() == 1 && m.contains("Hi"));
    m.erase("Hi");
    assert(m.empty());
    cout << "Passed all tests" << endl;
}

void testMerge() {
    Map m1;
    m1.insert("Fred", 123);
    m1.insert("Ethel", 456);
    m1.insert("Lucy", 789);
    Map m2;
    m2.insert("Lucy", 789);
    m2.insert("Ricky", 321);
    Map result;
    merge(m1, m2, result);
    assert(result.contains("Fred") && result.contains("Ricky") && result.contains("Lucy") && result.contains("Ethel") && result.size() == 4);
    result.insert("Little Ricky", 456);
    merge(m1, m2, result);
    assert(result.contains("Fred") && result.contains("Ricky") && result.contains("Lucy") && result.contains("Ethel") && result.size() == 4);
    m2.update("Lucy", 654);
    merge(m1, m2, result);
    assert(result.contains("Fred") && result.contains("Ricky") && !result.contains("Lucy") && result.contains("Ethel") && result.size() == 3);
    cout << "Passed all tests" << endl;
}

void testReassign() {
    Map m;
    Map result;
    m.insert("Fred", 123);
    m.insert("Ethel", 456);
    m.insert("Lucy", 789);
    m.insert("Ricky", 321);
    reassign(m, result);
    ValueType v1; ValueType v2; ValueType v3; ValueType v4;
    result.get("Fred", v1);
    result.get("Ethel", v2);
    result.get("Lucy", v3);
    result.get("Ricky", v4);
    assert(result.contains("Fred") && v1 != 123 && result.contains("Ethel") && v2 != 456 && result.contains("Lucy") && v3 != 789 && result.contains("Ricky") && v4 != 321 && result.size() == 4);
    result.insert("Little Ricky", 234);
    reassign(m, result);
    assert(result.contains("Fred") && v1 != 123 && result.contains("Ethel") && v2 != 456 && result.contains("Lucy") && v3 != 789 && result.contains("Ricky") && v4 != 321 && result.size() == 4);
    cout << "Passed all tests" << endl;
}

void testOperator() {
    Map m1;
    m1.insert("Fred", 10);
    Map m2;
    m2.insert("Ethel", 10);
    m2.insert("Ricky", 20);
    m1 = m2;
    assert(m1.contains("Ethel") && m1.contains("Ricky") && m1.size() == 2);
    cout << "Passed all tests" << endl;
}
