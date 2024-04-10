//
//  GamerMap.cpp
//  Project2V1
//
//  Created by Devansh Mishra on 22/01/24.
//

#include <stdio.h>
#include "GamerMap.h"

bool GamerMap::addGamer(KeyType name) {
    
    if (m_gamermap.contains(name) or m_gamermap.size() >= DEFAULT_MAX_ITEMS) {
        return false;
    }
    m_gamermap.insert(name, 0);
    return true;
}

double GamerMap::hoursSpent(KeyType name) const {
    
    if (!m_gamermap.contains(name)) {
        return -1;
    }
    ValueType hours;
    m_gamermap.get(name,hours);
    return hours;
}

bool GamerMap::play(KeyType name, ValueType hours) {
    
    if (!m_gamermap.contains(name)) {
        return false;
    }
    ValueType hours_logged;
    m_gamermap.get(name,hours_logged);
    if (hours_logged < 0) {
        return false;
    }
    
    m_gamermap.update(name, hours);
    return true;
}

int GamerMap::numGamers() const {
    return m_gamermap.size();
}

void GamerMap::print() const {
    KeyType name;
    ValueType hours;
    for (int i = 0; i < m_gamermap.size(); i++) {
        m_gamermap.get(i, name, hours);
        cout << name << " " << hours << endl;
    }
}
