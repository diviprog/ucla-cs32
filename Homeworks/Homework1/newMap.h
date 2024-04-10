//
//  newMap.h
//  Project2V1
//
//  Created by Devansh Mishra on 23/01/24.
//

#ifndef NEWMAP_INCLUDED
#define NEWMAP_INCLUDED

#include <iostream>
using namespace std;

using KeyType = string;
using ValueType = double;

 // global constants
const int DEFAULT_MAX_ITEMS = 150;


 // class definition
struct KeyValue
{
    KeyType key;
    ValueType value;
};

class Map
{
  public:
    Map();         // Create an empty map (i.e., one whose size() is 0).
    Map(int size); // Create an empty map with defined size
    Map(const Map& other); // copy constructor
    ~Map(); // destructor
    Map& operator=(const Map& rhs); // assignment

    bool empty() const;  // Return true if the map is empty, otherwise false.

    int size() const;    // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
      // If key is not equal to any key currently in the map and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that either the key is already in the map, or the map has a fixed
      // capacity and is full).

    bool update(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value that it currently maps to, but instead map to
      // the value of the second parameter; in this case, return true.
      // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value that it currently maps to, but instead map to
      // the value of the second parameter; in this case, return true.
      // If key is not equal to any key currently in the map, and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that the key is not already in the map and the map has a fixed
      // capacity and is full).

    bool erase(const KeyType& key);
      // If key is equal to a key currently in the map, remove the key/value
      // pair with that key from the map and return true.  Otherwise, make
      // no change to the map and return false.
     
    bool contains(const KeyType& key) const;
      // Return true if key is equal to a key currently in the map, otherwise
      // false.
     
    bool get(const KeyType& key, ValueType& value) const;
      // If key is equal to a key currently in the map, set value to the
      // value in the map which the key maps to, and return true.  Otherwise,
      // make no change to the value parameter of this function and return
      // false.
     
    bool get(int i, KeyType& key, ValueType& value) const;
      // If 0 <= i < size(), copy into the key and value parameters the
      // key and value of the key/value pair in the map whose key is strictly
      // greater than exactly i keys in the map and return true.  Otherwise,
      // leave the key and value parameters unchanged and return false.

    void swap(Map& other);
      // Exchange the contents of this map with the other one.
    
  private:
    KeyValue* m_pairs;
    int m_maxitems;
    int m_numitems;
};

void testForSizeAndEmpty();
void testForInsert();
void testForSwap();
void emptyStringTest();
void test();

#endif
