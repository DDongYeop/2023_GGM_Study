#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <thread>

using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define IP_ADDRESS "localhost"

struct client_type //Ŭ���̾�Ʈ ����ü
{
    SOCKET socket;
    int id;
    char received_msg[DEFAULT_BUFLEN];
};

//�����κ��� ������ �޴� �Լ� (recv)
int process_client(client_type& new_client)
{
    while (true)
    {
        memset(new_client.received_msg, 0, DEFAULT_BUFLEN);
        //���� ���� ����
        if (new_client.socket != 0)
        {
            int iResult = recv(new_client.socket, new_client.received_msg, DEFAULT_BUFLEN, 0);
            //���������� recv�� �Ϸ��ߴٸ� ���� �޼����� ���
            if (iResult != SOCKET_ERROR)
            {
                cout << new_client.received_msg << endl;
            }
            else
            {
                cout << "recv() failed: " << WSAGetLastError() << endl;
                break;
            }
        }
    } // end while
    //���� ���� �� ���� ���
    if (WSAGetLastError() == WSAECONNRESET)
    {
        cout << "The server has disconnected" << endl;
    }
    return 0;
}

int __cdecl main(int argc, char** argv)
{
    WSADATA wsaData;
    //SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL, *ptr = NULL, hints;
    string sent_msg = "";
    client_type client = { INVALID_SOCKET, -1, "" };
    int iResult = 0;
    string message;

    cout << "Starting Client..." << endl;

    // Validate the parameters;
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    cout << "Connecting..." << endl;

    // Resolve the server address and port
    iResult = getaddrinfo(static_cast<LPCSTR>(IP_ADDRESS), DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        client.socket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (client.socket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(client.socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(client.socket);
            client.socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (client.socket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    } //���� ���� �� �ϰ� �߰��� Ŭ���̾�Ʈ �� ���Ͽ� ���� �߻�

    //�ƴϸ� ������ ���������� ����
    cout << "Successfilly Connected" << endl;

    //�����κ��� id�� �޾Ƽ� ����ü�� ����
    //1. �ڸ��� ������ id�� ������
    //2. �ڸ��� ������ "Server is Full"
    recv(client.socket, client.received_msg, DEFAULT_BUFLEN, 0);

    if (message != "Server is Full")
    {
        client.id = atoi(client.received_msg);
        thread my_thread(process_client, ref(client));

        //�޼��� ������
        while (true)
        {
            getline(cin, sent_msg);
            iResult = send(client.socket, sent_msg.c_str(), strlen(sent_msg.c_str()), 0);
            if (iResult <= 0)
            {
                cout << "send() failed: " << WSAGetLastError() << endl;
                break;
            }
        }
        //������ �߻��߰ų�, �� �̻� ���� �����Ͱ� ���� ��
        my_thread.detach();
    }
    else //Server is full
    {
        cout << client.received_msg << endl;
        // shutdown the connection since no more data will be sent
        iResult = shutdown(client.socket, SD_SEND);
        if (iResult == SOCKET_ERROR) 
        {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(client.socket);
            WSACleanup();
            return 1;
        }
    }
    
    closesocket(client.socket);
    WSACleanup();

    return 0;
}