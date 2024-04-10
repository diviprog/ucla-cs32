//
//  main.cpp
//  Homework4P2V1
//
//  Created by Devansh Mishra on 04/03/24.
//

#include <iostream>
using namespace std;

void removeOdd(vector<int>& v)
{
    for (vector<int>::iterator p = v.begin();p != v.end(); p++) {
        if (*p % 2 == 1) {
            p = v.erase(p);
            p--;
        }
    }
}

void test()
{
    int a[9] = { 5, 2, 8, 9, 6, 7, 3, 4, 1 };
    vector<int> x(a, a+9);  // construct x from the array
    assert(x.size() == 9 && x.front() == 5 && x.back() == 1);
    removeOdd(x);
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
}

int main()
{
    test();
    cout << "Passed" << endl;
}
