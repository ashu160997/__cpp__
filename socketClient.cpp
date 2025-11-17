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

using namespace std;

struct sockaddr_in srv;

#define MAX 80

enum class message_type
{
    registration = 1,
    message = 2,

};

struct message_rec
{
    message_type m1;
    char u_mob[10];
    // string s_mob;
    char message[1000];
};

void tcpClient()
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

    memset((sockaddr *)&srv, 0, sizeof(srv));
    int port;
    cout << "enter port number" << endl;
    cin >> port;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    srv.sin_addr.s_addr = inet_addr("192.168.1.4");
    memset(&srv.sin_zero, 0, 8);

    int co = connect(nSocket, (sockaddr *)&srv, sizeof(srv));
    if (co < 0)
    {
        cout << "failed in connection" << endl;
    }
    else
    {
        cout << "connected successfully" << endl;
    }

    cout << "going to register, please enter your number" << endl;
    string ph;
    cin >> ph;
    message_rec m_inst;
    m_inst.m1 = message_type::registration;
    memcpy(m_inst.u_mob, ph.c_str(), strlen(ph.c_str()));
    char buffer[1024];
    bzero(buffer, 1024);
    memcpy(buffer, &m_inst, 1024);
    cout << buffer << endl;
    send(nSocket, buffer, 1024, 0);
    auto t1 = thread([&]()
                     {

                        while(1)
                        {
        //cout << "please insert your message" << endl;
        //char mess[200];
        //cin.getline(mess, 200);
        //string mess_s(mess);
        cout<<"please enter dest mobile number: "<<endl;
        string dest_ph;
        cin>>dest_ph;

        cout<<"please enter message to be sent: "<<endl;
        string dest_m;
        cin>>dest_m;

        message_rec mr;
        mr.m1=message_type::message;
        memcpy(mr.u_mob,dest_ph.c_str(),100);
        memcpy(mr.message,dest_m.c_str(),1000);

        char buff[1024];
        memcpy(buff,&mr,sizeof(mr));

        cout<<"message to be sent: "<<buff<<endl;

        //cout << "sending message: 7321923882HithereRamthere" << endl;
        send(nSocket, buff, 1024, 0);
        sleep(5);
 } });

    auto t2 = thread([&]()
                     {
                         while (1)
                         {
                             char buff[1024];
                             memset(&buff, 0, 200);
                             recv(nSocket, buff, sizeof(buff), 0);
                             cout << "message received:" << buff << endl;
                             sleep(5);
                         } });

    t1.join();
    t2.join();

    while (1)
    {
        sleep(1);
    }

    close(nSocket);
}

int main()
{
    tcpClient();

    return 0;
}
