#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define MAX_CLIENTS 5

struct client_type { //Ŭ���̾�Ʈ ����
    int id;
    SOCKET socket;
};

int process_client(client_type& new_client,
    vector<client_type>& client_array, thread& thread);
int main();

//Ŭ���̾�Ʈ ó��(send, recv)
int process_client(client_type& new_client, vector<client_type>& client_array, thread& thread) {
    string msg = ""; //���� �޼���
    char tempmsg[DEFAULT_BUFLEN] = ""; //���� ����

    while (1) {
        memset(tempmsg, 0, DEFAULT_BUFLEN);
        if (new_client.socket != 0) {
            int iResult = recv(new_client.socket, tempmsg, DEFAULT_BUFLEN, 0);
            if (iResult != SOCKET_ERROR) { //������ ���� ����
                if (strcmp("", tempmsg)) {
                    msg = "Client #" + to_string(new_client.id) + ": " + tempmsg;
                    cout << msg.c_str() << endl;

                    //BroadCast
                    for (int i = 0; i < MAX_CLIENTS; i++)
                    {
                        if (client_array[i].socket != INVALID_SOCKET) {
                            if (new_client.id != i) {
                                iResult = send(client_array[i].socket, msg.c_str(),
                                    strlen(msg.c_str()), 0);
                            }
                        }
                    }
                }
            }
            else { //Ŭ���̾�Ʈ�� ���� ����
                msg = "Client #" + to_string(new_client.id) + " Disconnected";
                cout << msg << endl;
                //���� ������ ���� �ݱ�
                closesocket(new_client.socket);
                //�迭 ���ڸ� �����
                client_array[new_client.id].socket = INVALID_SOCKET;
                for (int i = 0; i < MAX_CLIENTS; i++)
                {
                    if (client_array[i].socket != INVALID_SOCKET) {
                        iResult = send(client_array[i].socket, msg.c_str(), strlen(msg.c_str()), 0);
                    }
                }
                break;
            }
        }
    }//end while
    thread.detach();//�� �� ���� ������ ���̱�
    return 0;
}

int __cdecl main(void)
{
    // ���� �ʱ�ȭ --> ���� ���� --> ��Ʈ��ũ ��� --> ���� �ݱ� --> ���� ����
    WSADATA wsaData; //���� ������ ����ü
    int iResult;

    SOCKET ServerSocket = INVALID_SOCKET; //Ŭ���̾�Ʈ�� ��û�� �޴� ����
    //SOCKET ClientSocket = INVALID_SOCKET; //�����͸� �ְ� �޴� ����

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    string msg = "";
    vector<client_type> client(MAX_CLIENTS);
    int num_clients = 0; //���� �� Ŭ���̾�Ʈ ��
    int temp_id = -1;
    thread my_thread[MAX_CLIENTS]; //1Ŭ�� 1������

    // Initialize Winsock
    // ���� �ʱ�ȭ
    cout << "Initializing Winsock..." << endl;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype = SOCK_STREAM; //TCP ����� ����(��Ʈ��) UDP(�����ͱ׷�)
    hints.ai_protocol = IPPROTO_TCP; //TCP ��������
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    cout << "Setting up Server..." << endl;
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    // ���� ����
    cout << "Creating Server Socket..." << endl;
    ServerSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ServerSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    //���� �ɼ� ����
    //��� ���̰ų� ������� �� �� �� ��Ʈ�� ��Ʈ ������
    //(���������� ����� ���� bind ������ �����ϰ� ���� �� ����� ���� �ذ�
    setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR, "1", sizeof(int));
    //���ʿ��� ����� ����(ACK ��)�� �ٿ��� �� �� ���� TCP ���� ����
    setsockopt(ServerSocket, IPPROTO_TCP, TCP_NODELAY, "1", sizeof(int));


    // Setup the TCP listening socket
    // IP�ּ�, ��Ʈ ��ȣ ���ε�
    cout << "Binding socket..." << endl;
    iResult = bind(ServerSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ServerSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    // ���ε� �� Ŭ���̾�Ʈ ��û �����ϰ� ������
    cout << "Listening..." << endl;
    iResult = listen(ServerSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ServerSocket);
        WSACleanup();
        return 1;
    }

    //Ŭ���̾�Ʈ ����ü id, socket �ʱ�ȭ
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        client[i] = { -1, INVALID_SOCKET };
    }

    while (1) {
        SOCKET incoming = INVALID_SOCKET;
        incoming = accept(ServerSocket, NULL, NULL);
        if (incoming == INVALID_SOCKET) continue;

        num_clients = -1;
        temp_id = -1;

        //���� ���ڸ� ã��(�ִ� 5��)
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            if (client[i].socket == INVALID_SOCKET && temp_id == -1) {
                client[i].socket = incoming;
                client[i].id = i;
                temp_id = i;
            }

            if (client[i].socket != INVALID_SOCKET) {
                num_clients++;
            }
        }
        //������ �ڸ��� �־ ���� ����
        if (temp_id != -1) {
            //Client ��ȣ�� ���� ������ �㰡 �Ǿ��ٰ� �˷��ֱ�
            cout << "Client #" << client[temp_id].id << " Accepted" << endl;
            //Ŭ���̾�Ʈ���� ó�� ������ �޼���(���ӹ�ȣ)
            msg = to_string(client[temp_id].id);
            send(client[temp_id].socket, msg.c_str(), strlen(msg.c_str()), 0);

            //�����忡�� Ŭ���̾�Ʈ ä�� �� �ñ�
            my_thread[temp_id] = thread(process_client, ref(client[temp_id]), ref(client),
                ref(my_thread[temp_id]));
        }
        else { //�ڸ��� ��� ���� ����
            msg = "Server is Full";
            send(incoming, msg.c_str(), strlen(msg.c_str()), 0);
            cout << msg << endl;
        }
    }//end while

    //���� ���� �� ���� ���� �ݱ�
    closesocket(ServerSocket);
    //Ŭ���̾�Ʈ ���� �ݱ�, ������ �ݱ�
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        my_thread[i].detach();
        closesocket(client[i].socket);
    }

    WSACleanup();
    cout << "Program has ended." << endl;

    system("pause");
    return 0;
}