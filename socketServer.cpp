#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <map>

using namespace std;

enum class message_type
{
    registration = 1,
    message = 2,

};

struct sockaddr_in srv;

static map<string, int> mp_number_id;

#define MAX 80
#define PORT 8080

struct messDetail
{
    sockaddr_in sockadd;
    int sd;
};
struct message_rec
{
    message_type m1;
    char u_mob[10];
    // string s_mob;
    char message[1000];
};
void send_message(int sd, char *resp)
{
    char buff[1024];
    memset(buff, 0, 1024);
    memcpy(buff, resp, 1024);
    cout << "message to be send: " << resp << endl;
    printf("message to be send %s\n", resp);
    send(sd, buff, 1024, 0);
}

void func1(void *context)
{
    cout << "entering thread" << endl;
    messDetail *det = (messDetail *)context;
    int sd = det->sd;
    sockaddr_in sockadd = det->sockadd;

    while (1)
    {
        char buff[1024];
        memset(buff, 0, sizeof(buff));
        cout << "waiting to receive message" << endl;
        recv(sd, buff, sizeof(buff), 0);
        // printf("message recived:%s\n", buff);
        cout << buff << endl;
        message_rec rec;
        memset(&rec, 0, sizeof(rec));
        memcpy(&rec, buff, sizeof(rec));

        string mob = string(rec.u_mob);
        mob = mob.substr(0, 10);
        string mess = string(rec.message);
        // string mess;
        // getline(rec.message, mess);

        cout << mob << endl;
        cout << mess << endl;

        if (rec.m1 == message_type::registration)
        {
            rec.m1 = message_type::registration;
            cout << "registering mobile to server with mobile number :" << endl;
            if (mp_number_id.find(mob) == mp_number_id.end())
            {
                cout << "inserting id in map" << endl;
                mp_number_id.insert({mob, sd});
            }
        }
        else if (rec.m1 == message_type::message)
        {
            rec.m1 = message_type::message;
            cout << "recieved message : " << mess << " for mobile : " << mob << endl;
            if (mp_number_id.find(mob) != mp_number_id.end())
            {
                cout << "sending message to destination : " << mob << endl;
                int sd_d = mp_number_id[mob];
                send_message(sd_d, rec.message);
            }
            else
            {
                cout << "destination is not connwcted" << endl;
            }
        }
        // rec.s_mob = st.substr(1, 10);
        // rec.u_mob = st.substr(11, 10);
        // rec.message = st.substr(21, n - 20);
        //  string st1(rec.u_mob);
        //  string st2(rec.s_mob);
        //  string st3(rec.message);
        // cout << rec.s_mob << endl;
        // cout << rec.u_mob << endl;
        // cout << rec.message << endl;
        /*if (mp_number_id.find(rec.u_mob) == mp_number_id.end())
        {
            cout << "inserting id in map" << endl;
            mp_number_id.insert({rec.u_mob, sd});
        }*/
    }
}

void tcpServer()
{
    int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int nRet = 0;

    if (nSocket < 0)
    {
        cout << "socket not opened" << endl;
    }
    else
    {
        cout << "socket opened successfully" << endl;
    }

    srv.sin_family = AF_INET;

    srv.sin_addr.s_addr = inet_addr("192.168.1.4");
    srv.sin_port = htons(8080);
    memset(&srv.sin_zero, 0, 8);
    auto status = bind(nSocket, (sockaddr *)&srv, sizeof(sockaddr));

    /*if (bind(nSocket, (sockaddr *)&srv, sizeof(sockaddr)) < 0)
    {
        cout << "failed to bind" << endl;
    }
    else
    {
        cout << "binding successful" << endl;
    }*/

    int ret = listen(nSocket, 5);
    if (ret < 0)
    {
        cout << "problem in listening" << endl;
        exit(0);
    }
    else
    {
        cout << "Listening" << endl;
    }
    while (1)
    {
        cout << "waiting for connection" << endl;
        sockaddr_in newSockadd;
        socklen_t s1 = sizeof(newSockadd);
        int newsd = accept(nSocket, (sockaddr *)&newSockadd, &s1);

        if (newsd < 0)
        {
            cout << "error in connecting with client" << endl;
            exit(0);
        }
        cout << "connected to a client" << endl;

        messDetail *det = new messDetail;
        det->sd = newsd;
        det->sockadd = newSockadd;

        send(newsd, "successfully connected", 255, 0);

        /*
        int count = 0;
        while (1)
        {
            char buff[200] = {0};
            memset(&buff, 0, 200);
            count = count + recv(newsd, buff, sizeof(buff), 0);
            string st1(buff);
            cout << st1 << endl;
            if (st1 == "exit")
            {
                cout << "exiting the chatbox" << endl;
                exit(0);
            }
            char response[200];
            cin.getline(response, 200);
            cout << endl;
            send(newsd, response, sizeof(response), 0);
            cout << buff << endl;
        }
        */
        thread t1(func1, (void *)det);
        t1.detach();
        sleep(5);
    }
}

int main()
{
    tcpServer();

    return 0;
}
