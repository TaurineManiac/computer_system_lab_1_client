#include <iostream>
#include "inputCheck.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#pragma warning(disable:4996)
#include <chrono>
#include <thread>
#include <windows.h>

using namespace std;

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout << "13.Осуществить взаимодействие клиента и сервера на основе протокола TCP/IP. \n"
            "Функционирование клиента и сервера реализовать следующим образом: клиент посылает серверу координаты точки Х и У в "
            "декартовой системе координат.\n "
            "Определить в какой координатной четверти находится данная точка.\n" << endl;
    WSAData wSAData;
    WORD wVersion = MAKEWORD(2, 2);

    if (WSAStartup(wVersion, &wSAData)!=0) {
        cout << "WSAStartup failed with error: " << WSAGetLastError() << endl;
        return 1;
    }

    SOCKADDR_IN addr;
    int size = sizeof(addr);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    SOCKET sock;
    int counter=0;
    while (true) {

        cout << "Попытка " << counter+1 << endl;
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (connect(sock, (SOCKADDR*)&addr, sizeof(addr))!=0) {
            cout << "connect() failed with error: " << endl;
            counter++;
            cout << "Ждём 5 секунд и проббуем ещё раз" << endl;
            this_thread::sleep_for(chrono::seconds(5));
            if (counter==50) {
                return 0;
            }
        }
        else {
            cout << "connect() succeeded." << endl;
            break;
        }
    }



    char message[256];
    recv(sock,message,sizeof(message),0);
    cout << message << endl;
    double x = mylib::checkTryToInputDouble();
    double y = mylib::checkTryToInputDouble();
    string strX = to_string(x);
    string strY = to_string(y);

    send(sock, strX.c_str(),sizeof(strX), 0);
    send(sock, strY.c_str(),sizeof(strY), 0);

    recv(sock,message,sizeof(message),0);
    cout << message << endl;



}