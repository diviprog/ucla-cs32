//
//  Map.cpp
//  Project2V1
//
//  Created by Devansh Mishra on 21/01/24.
//

#include <stdio.h>
#include "Map.h"

int getIndex(KeyType arr[], int size, KeyType target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

bool Map::empty() const {
    if (m_numitems == 0) {
        return true;
    }
    return false;
}

int Map::size() const {
    return m_numitems;
}

bool Map::insert(const KeyType &key, const ValueType &value) {
    
    if (m_numitems >= DEFAULT_MAX_ITEMS or contains(key)) {
        return false;
    }
 
    m_pairs[m_numitems].key = key;
    m_pairs[m_numitems].value = value;
    m_numitems++;
    return true;
}

bool Map::update(const KeyType &key, const ValueType &value) {
    
    for (int i = 0; i < m_numitems; i++) {
        if (key == m_pairs[i].key) {
            m_pairs[i].value = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value) {
    
    for (int i = 0; i < m_numitems; i++) {
        if (key == m_pairs[i].key) {
            m_pairs[i].value = value;
        }
    }
    
    if (m_numitems < DEFAULT_MAX_ITEMS) {
        m_pairs[m_numitems].key = key;
        m_pairs[m_numitems].value = value;
        m_numitems++;
        return true;
    }
    else {
        return false;
    }
}

bool Map::erase(const KeyType &key) {
    
    for (int i = 0; i < m_numitems; i++) {
        if (key == m_pairs[i].key) {
            for (int j = i; j < m_numitems-1; j++) {
                m_pairs[j].key = m_pairs[j+1].key;
                m_pairs[j].value = m_pairs[j+1].value;
            }
            m_numitems--;
            return true;
        }
    }
    return false;
}

bool Map::contains(const KeyType &key) const {
    
    for (int i = 0; i < m_numitems; i++) {
        if (key == m_pairs[i].key) {
            return true;
        }
    }
    return false;
}

bool Map::get(const KeyType &key, ValueType &value) const {
    
    for (int i = 0; i < m_numitems; i++) {
        if (key == m_pairs[i].key) {
            value = m_pairs[i].value;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType &key, ValueType &value) const {
    
    if (i < 0 or i >= m_numitems) {
        return false;
    }
    
    int count_greater = 0;
    for (int j = 0; j < m_numitems; j++) {
        for (int k = 0; k < m_numitems; k++) {
            if (m_pairs[j].key > m_pairs[k].key) {
                count_greater++;
            }
        }
        
        if (count_greater == i) {
            key = m_pairs[j].key;
            value = m_pairs[j].value;
            return true;
        }
        
        count_greater = 0;
    }
    return false;
}

void Map::swap(Map &other) {
    
    Map m = *this;
    *this = other;
    other = m;
}

