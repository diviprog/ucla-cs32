//
//  Map.cpp
//  Project2V2
//
//  Created by Devansh Mishra on 28/01/24.
//

#include "Map.h"

Map::Node* Map::findKey(const KeyType& key) const { // finding the pointer to the Node given a key
    Node* ptr = dummy.next;
    for (Node* ptr = dummy.next; ptr != &dummy; ptr = ptr->next) {
        if (ptr->key == key) return ptr;
    }
    ptr = dummy.next->prev;
    return ptr;
}


Map::Map() : dummy("", 0) { // constructor
    dummy.next = &dummy;
    dummy.prev = &dummy;
}

bool Map::empty() const {
    return (dummy.next == &dummy);
}

int Map::size() const {
    int count = 0;
    for (Node* ptr = dummy.next; ptr != &dummy; ptr = ptr->next) {
        count++;
    }
    return count;
}

bool Map::contains(const KeyType &key) const {
    Node* ptr = findKey(key);
    return (ptr != &dummy);
}

bool Map::erase(const KeyType &key) {
    if (!contains(key)) return false;
    Node* ptr = findKey(key);
    Node* ptrnext = ptr->next;
    Node* ptrprev = ptr->prev;
    ptrnext->prev = ptrprev;
    ptrprev->next = ptrnext;
    delete ptr;
    return true;
}

bool Map::insert(const KeyType &key, const ValueType &value) {
    if (contains(key)) return false;
 
    if (size() == 0) { // inserting into empty list
        insertWithPtrs(key, value, dummy.next, dummy.prev);
        return true;
    }
    
    for (Node* ptrnext = dummy.next; ptrnext != &dummy; ptrnext = ptrnext->next) {
        if (ptrnext->key > key) {
            insertWithPtrs(key, value, ptrnext, ptrnext->prev);
            return true;
        }
    }
    insertWithPtrs(key, value, dummy.prev->next, dummy.prev);
    return true;
}

bool Map::update(const KeyType &key, const ValueType &value) {
    Node* ptr = findKey(key);
    if (ptr == &dummy) return false;
    ptr->value = value;
    return true;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value) {
    if (contains(key)) update(key, value);
    else insert(key, value);
    return true;
}

bool Map::get(const KeyType &key, ValueType &value) const {
    Node* ptr = findKey(key);
    if (ptr == &dummy) return false;
    value = ptr->value;
    return true;
}

bool Map::get(int i, KeyType &key, ValueType &value) const {
    Node* ptr = dummy.next;
    for (int j = 0; j < i; j++) {
        ptr = ptr->next;
    }
    if (ptr == &dummy) return false;
    key = ptr->key;
    value = ptr->value;
    return true;
}

void Map::swap(Map &other) {
    Node* thisdummy = &dummy;
    Node* otherdummy = &other.dummy;
    
    dummy.next->prev = otherdummy; // switching the next and prev pointers of the first and last elements of this list to point to the other dummy
    dummy.prev->next = otherdummy;
    
    other.dummy.next->prev = thisdummy; // switching the next and prev pointers of the first and last elements of the other list to point to this dummy
    other.dummy.prev->next = thisdummy;
    
    Node* temp = dummy.next; // swapping the next pointers of the two dummies
    dummy.next = other.dummy.next;
    other.dummy.next = temp;
    
    Node* temp2 = dummy.prev; // swapping the prev pointers of the two dummies
    dummy.prev = other.dummy.prev;
    other.dummy.prev = temp2;
}

Map::~Map() {
    for (Node* ptr = dummy.next; ptr != &dummy;) {
        Node* ptr2 = ptr->next;
        delete ptr;
        ptr = ptr2;
    }
}

Map::Map(const Map& other) : dummy("", 0){
    for (Node* ptr = other.dummy.next; ptr != &other.dummy; ptr = ptr->next) {
        insert(ptr->key, ptr->value);
    }
}

Map& Map::operator=(const Map &rhs) {
    for (Node* ptr = dummy.next; ptr != &dummy;) {
        Node* ptr2 = ptr->next;
        erase(ptr->key);
        ptr = ptr2;
    }
    
    for (Node* ptr = rhs.dummy.next; ptr != &rhs.dummy; ptr = ptr->next) {
        insert(ptr->key, ptr->value);
    }
    return *this;
}

bool merge(const Map &m1, const Map &m2, Map &result) {
    
    for (int i = 0; i < result.size(); i++) {
        KeyType key; ValueType value;
        result.get(i, key, value);
        result.erase(key);
    }
    
    bool flag = true;
    for (int i = 0; i < m1.size(); i++) {
        KeyType key1; ValueType value1; ValueType value2;
        m1.get(i, key1, value1);
        if (m2.get(key1, value2)) {
            if (value1 != value2) {
                flag = false;
                continue;
            }
        }
        result.insert(key1, value1);
    }
    
    for (int i = 0; i < m2.size(); i++) {
        KeyType key; ValueType value;
        m2.get(i, key, value);
        if (!result.contains(key) && !m1.contains(key)) {
            result.insert(key, value);
        }
    }
    return flag;
}

void reassign(const Map &m, Map &result) {
    for (int i = 0; i < result.size(); i++) {
        KeyType key; ValueType value;
        result.get(i, key, value);
        result.erase(key);
    }
    
    ValueType firstvalue; KeyType key1; ValueType value1; KeyType key2; ValueType value2;
    m.get(0, key1, firstvalue);
    for (int i = 0; i < m.size()-1; i++) {
        m.get(i, key1, value1);
        m.get(i+1, key2, value2);
        result.insert(key1, value2);
    }
    m.get(m.size()-1, key2, value2);
    result.insert(key2, firstvalue);
}

void Map::dump() const {
    for (Node* ptr = dummy.next; ptr != &dummy; ptr = ptr->next) {
        cerr << ptr->key << " " << ptr->value << endl;
    }
    cerr << endl;
}

void Map::insertWithPtrs(const KeyType &key, const ValueType &value, Node *ptrnext, Node *ptrprev) {
    Node* ptr = new Node(key, value);
    ptr->next = ptrnext;
    ptr->prev = ptrprev;
    ptrnext->prev = ptr;
    ptrprev->next = ptr;
}
