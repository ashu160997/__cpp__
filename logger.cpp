#include <iostream>
#include <thread>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <optional>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <memory>
#include <string>

using namespace std;

class logger
{
private:
    static logger *instance;
    static FILE *fp;

public:
    static logger *getinstance()
    {
        if (instance == NULL)
        {
            instance = new logger;
            fp = fopen("logfile.txt", "w");
        }
        return instance;
    }
    static void log(string st1)
    {
        std::time_t t1 = time(nullptr);
        tm *lmt = localtime(&t1);
        char buffer[80];

        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", lmt);

        string st2 = string(buffer);
        string res = '[' + st2;
        res = res + "]: " + st1;

        cout << res << endl;
        if (fp != NULL)
        {
            fprintf(fp, "%s\n", res.c_str());
            fflush(fp);
        }
    }
    ~logger()
    {
        fclose(fp);
    }
};

logger *logger::instance = NULL;
FILE *logger::fp = NULL;
int main()
{
    int count = 0;
    while (1)
    {
        logger::getinstance()->log("putting count number" + to_string(count));
        count++;
        sleep(2);
    }
}