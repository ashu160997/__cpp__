#include <iostream>
#include <semaphore>
#include <chrono>
#include <thread>
using namespace std;

static binary_semaphore s_p{1};
static binary_semaphore s_c{0};

static int buffer[10];

static int l = 0;

void func_produce()
{
    while (1)
    {
        s_p.acquire();
        cout << "producing ";
        for (int i = 0; i < 10; i++)
        {
            cout << l << " ";
            buffer[i] = l;
            l++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        cout << "\n";
        s_c.release();
    }
}
void func_consume()
{
    while (1)
    {
        s_c.acquire();
        cout << "consuming ";
        for (int i = 0; i < 10; i++)
        {
            cout << buffer[i] << " ";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        cout << "\n";
        s_p.release();
    }
}

int main()
{
    cout << "entering main thread \n";
    std::thread t1(func_produce);
    std::thread t2(func_consume);

    t1.join();
    t2.join();
}
