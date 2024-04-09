//
//  Map.h
//  Project2V1
//
//  Created by Devansh Mishra on 25/01/24.
//

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <string>
#include <iostream>
using namespace std;

using KeyType = string;
using ValueType = double;

class Node {
  public:
    Node(KeyType key, ValueType value) : key(key), value(value) {};
    KeyType key;
    ValueType value;
    Node* next;
    Node* prev;
};

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
  private:
    Node* head;
    Node* tail;
    Node* findKey(const KeyType& key) const;
};

#endif /* Map_h */
