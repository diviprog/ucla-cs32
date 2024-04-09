//
//  Map.cpp
//  Project2V1
//
//  Created by Devansh Mishra on 25/01/24.
//

#include <stdio.h>
#include "Map.h"

///////////////////////////////////////
/// Map implementation
///////////////////////////////////////

Node* Map::findKey(const KeyType &key) const {
    Node* ptr = nullptr;
    for (Node* ptr = head; ptr != nullptr && ptr->key != key; ptr = ptr->next) {;}
    return ptr;
}

Map::Map() {
    head = nullptr;
    tail = nullptr;
}

Map::~Map() {
    Node* ptrprev = head->next;
    for (Node* ptrnext = head->next->next; ptrnext != nullptr; ptrnext = ptrnext->next) {
        delete ptrprev;
        ptrprev = ptrnext;
    }
    delete ptrprev;
}

bool Map::empty() const {
    return (head == nullptr);
}

int Map::size() const {
    int count = 0;
    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
        count++;
    }
    return count;
}

bool Map::contains(const KeyType &key) const {
    Node* ptr = findKey(key);
    if (ptr == nullptr) return false;
    return true;
}

bool Map::erase(const KeyType &key) {
    Node* ptr = findKey(key);
    if (ptr == nullptr) return false;
    
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    delete ptr;
    return true;
}

bool Map::insert(const KeyType &key, const ValueType &value) {
    if (contains(key)) {
        return false;
    }
    
    Node* ptr = new Node(key, value);
    ptr->next = head;
    ptr->prev = nullptr;
    head->prev = ptr;
    head = ptr;
    return true;
}

bool Map::update(const KeyType &key, const ValueType &value) {
    Node* ptr = findKey(key);
    if (ptr == nullptr) return false;
    ptr->value = value;
    return true;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value) {
    if (contains(key)) return update(key, value);
    else return insert(key, value);
}

bool Map::get(const KeyType &key, ValueType &value) const {
    Node* ptr = findKey(key);
    if (ptr == nullptr) return false;
    value = ptr->value;
    return true;
}

bool Map::get(int i, KeyType &key, ValueType &value) const {
    for (Node* ptr1 = head; ptr1 != nullptr; ptr1 = ptr1->next) {
        int count = 0;
        for (Node* ptr2 = head; ptr2 != nullptr; ptr2 = ptr2->next) {
            if (ptr1->key > ptr2->key) {
                count++;
            }
        }
        if (count == i) {
            key = ptr1->key;
            value = ptr1->value;
            return true;
        }
    }
    return false;
}

void Map::swap(Map &other) {
    Node* ptr1 = head;
    head = other.head;
    other.head = ptr1;
    
    Node* ptr2 = tail;
    tail = other.tail;
    other.tail = ptr2;
}
