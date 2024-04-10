//
//  Map.h
//  Project2V2
//
//  Created by Devansh Mishra on 28/01/24.
//

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <string>
#include <iostream>
using namespace std;

//////////////////////////////////
/// Type aliasing
//////////////////////////////////

using KeyType = string;
using ValueType = double;

//////////////////////////////////
/// Map declaration
//////////////////////////////////

class Map
{
  public:
    Map();
    ~Map();
    Map(const Map& other);
    Map& operator=(const Map& rhs);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump() const;
    
    
  private:
    
    //////////////////////////////////
    /// Node declaration
    //////////////////////////////////
    struct Node {
        Node(KeyType key, ValueType value) : key(key), value(value) {};
        KeyType key;
        ValueType value;
        Node* next;
        Node* prev;
    };
    
    Node dummy;
    Node* findKey(const KeyType& key) const;
    void insertWithPtrs(const KeyType& key, const ValueType& value, Node* ptrnext, Node* ptrprev);
};

//////////////////////////////////
/// Additional functions
//////////////////////////////////

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

////////////////////////////////////
///// Test functions
////////////////////////////////////
//
//void testForSizeAndEmpty();
//void testForInsert();
//void testForSwap();
//void emptyStringTest();
//void test();
//void basicInsert();
//void testContains();
//void testEmpty();
//void testErase();
//void testMerge();
//void testReassign();
//void testOperator();

#endif /* Map_h */
