
#include <iostream>
#include "CLinkedList_2.h"

using namespace std;


int main()
{
    CLinkedList_2<int> listInt;
    CLinkedList_2<float> listFloat;

    for (int i = 0; i < 100; ++i)
    {
        listInt.push_back(i);
    }

    cout << listInt.front() << endl;
    cout << listInt.back() << endl;

    listInt.pop_back();
    cout << listInt.back() << endl;

    listInt.pop_front();
    cout << listInt.front() << endl;
    
    return 0;
}

