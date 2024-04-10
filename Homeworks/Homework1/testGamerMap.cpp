//
//  testGamerMap.cpp
//  Project2V1
//
//  Created by Devansh Mishra on 22/01/24.
//

#include <stdio.h>
#include "GamerMap.h"
#include <iostream>
#include <cassert>

void test1() {
    GamerMap gamemap;
    assert(gamemap.addGamer("Devansh")==true);
    assert(gamemap.addGamer("Pranav")==true);
    assert(gamemap.play("Devansh", 10.0)==true);
    assert(gamemap.hoursSpent("Devansh") == 10.0);
    assert(gamemap.numGamers()==2);
    cout << "Passed all tests" << endl;
}
