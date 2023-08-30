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

struct client_type { //클라이언트 정보
    int id;
    SOCKET socket;
};

int process_client(client_type& new_client,
    vector<client_type>& client_array, thread& thread);
int main();

//클라이언트 처리(send, recv)
int process_client(client_type& new_client, vector<client_type>& client_array, thread& thread) {
    string msg = ""; //보낼 메세지
    char tempmsg[DEFAULT_BUFLEN] = ""; //받을 버퍼

    while (1) {
        memset(tempmsg, 0, DEFAULT_BUFLEN);
        if (new_client.socket != 0) {
            int iResult = recv(new_client.socket, tempmsg, DEFAULT_BUFLEN, 0);
            if (iResult != SOCKET_ERROR) { //데이터 수신 성공
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
            else { //클라이언트가 접속 종료
                msg = "Client #" + to_string(new_client.id) + " Disconnected";
                cout << msg << endl;
                //접속 종료한 소켓 닫기
                closesocket(new_client.socket);
                //배열 빈자리 만들기
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
    thread.detach();//할 일 다한 스레드 죽이기
    return 0;
}

int __cdecl main(void)
{
    // 윈속 초기화 --> 소켓 생성 --> 네트워크 통신 --> 소켓 닫기 --> 윈속 종료
    WSADATA wsaData; //윈속 데이터 구조체
    int iResult;

    SOCKET ServerSocket = INVALID_SOCKET; //클라이언트의 요청을 받는 소켓
    //SOCKET ClientSocket = INVALID_SOCKET; //데이터를 주고 받는 소켓

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    string msg = "";
    vector<client_type> client(MAX_CLIENTS);
    int num_clients = 0; //접속 중 클라이언트 수
    int temp_id = -1;
    thread my_thread[MAX_CLIENTS]; //1클라 1스레드

    // Initialize Winsock
    // 윈속 초기화
    cout << "Initializing Winsock..." << endl;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype = SOCK_STREAM; //TCP 통신의 소켓(스트림) UDP(데이터그램)
    hints.ai_protocol = IPPROTO_TCP; //TCP 프로토콜
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
    // 소켓 생성
    cout << "Creating Server Socket..." << endl;
    ServerSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ServerSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    //소켓 옵션 설정
    //사용 중이거나 사용한지 얼마 안 된 포트면 포트 재지정
    //(비정상적인 종료로 아직 bind 정보를 유지하고 있을 때 생기는 문제 해결
    setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR, "1", sizeof(int));
    //불필요한 빈번한 전송(ACK 등)을 줄여서 좀 더 빠른 TCP 전송 세팅
    setsockopt(ServerSocket, IPPROTO_TCP, TCP_NODELAY, "1", sizeof(int));


    // Setup the TCP listening socket
    // IP주소, 포트 번호 바인딩
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

    // 바인드 후 클라이언트 요청 가능하게 리스닝
    cout << "Listening..." << endl;
    iResult = listen(ServerSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ServerSocket);
        WSACleanup();
        return 1;
    }

    //클라이언트 구조체 id, socket 초기화
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

        //서버 빈자리 찾기(최대 5개)
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
        //서버에 자리가 있어서 접속 성공
        if (temp_id != -1) {
            //Client 번호랑 같이 연결이 허가 되었다고 알려주기
            cout << "Client #" << client[temp_id].id << " Accepted" << endl;
            //클라이언트에게 처음 보내는 메세지(접속번호)
            msg = to_string(client[temp_id].id);
            send(client[temp_id].socket, msg.c_str(), strlen(msg.c_str()), 0);

            //스레드에게 클라이언트 채팅 일 맡김
            my_thread[temp_id] = thread(process_client, ref(client[temp_id]), ref(client),
                ref(my_thread[temp_id]));
        }
        else { //자리가 없어서 접속 실패
            msg = "Server is Full";
            send(incoming, msg.c_str(), strlen(msg.c_str()), 0);
            cout << msg << endl;
        }
    }//end while

    //서버 종료 시 서버 소켓 닫기
    closesocket(ServerSocket);
    //클라이언트 소켓 닫기, 스레드 닫기
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