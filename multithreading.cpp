#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <algorithm>
#include <unistd.h>

using namespace std;

int x = 100;
mutex m;

void fn1()
{
    cout << "locking thread" << endl;
    m.lock();
    for (int i = 0; i < 100; i++)
    {
        x++;
        cout << x << endl;
    }
    m.unlock();
    cout << "unlocking thread" << endl;
}

int main()
{

    auto fun = [](int n)
    {
        while (n-- > 0)
        {
            cout << n << endl;
        }
    };
    // thread t1(fun,500);

    thread t1(fn1);

    thread t2(fn1);

    auto t1=chrono::steady_clock::now() ;
    cout<<t1<<endl;

    t1.join();
    t2.join();
    return 0;
}