﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Collections;
using System.Runtime.InteropServices;

namespace _20230918_ChatServerCS
{
    internal class Program
    {
        //사용자 관리 해시테이블
        public static Hashtable clientsList = new Hashtable();
        private static int userCount = 0; //고유ID
        private static Mutex mut = new Mutex(); 

        static void Main(string[] args)
        {
            try
            {
                //Socket() Bind()
                TcpListener serverSocket = new TcpListener(IPAddress.Any, 8888);
                TcpClient clientSocket = default;
                int counter = 0;
                byte[] bytesFrom = new byte[1024];

                //Listen()
                serverSocket.Start();
                Console.WriteLine("C# Server Started");

                while (true)
                {
                    //Accept()
                    clientSocket = serverSocket.AcceptTcpClient();
                    NetworkStream networkStream = clientSocket.GetStream();

                    counter = userCount;
                    userCount++;

                    //Accept한 클라이언트 처리
                    HandleClient client = new HandleClient();
                    clientsList.Add(counter, client);
                    client.StartClinet(clientSocket, clientsList, counter);
                }//end while
                //사실 여기 아래론 실행 안됨
                clientSocket.Close();
                serverSocket.Stop();
                Console.WriteLine("exit");
                Console.ReadLine();
            }
            catch (Exception ex)
            { 
                Console.WriteLine(ex.ToString());
            }
        }// end Main

        //id값으로 해시테이블에서 해당 소켓 찾기
        public static TcpClient GetSocket(int id)
        {
            TcpClient socket = null;
            if (clientsList.ContainsKey(id))
            {
                HandleClient hc = (HandleClient)clientsList[id];
                socket = hc.clientSocket;
            }
            return socket;
        }

        //접속 중인 모든 클라이언트한테 메세지 뿌리기
        public static void Broadcast(string msg, string uName, bool flag)
        {
            mut.WaitOne();
            byte[] broadcastBytes;
            //1. 클라이언트가 보내는 메세지
            if (flag)
            {
                broadcastBytes = Encoding.UTF8.GetBytes(uName + "$" + msg);
                //ex 경동엽$안녕하세요
            }
            //2. 서버가 보내는 메세지 
            else
            {
                broadcastBytes = Encoding.UTF8.GetBytes(msg);
            }
            
            foreach(DictionaryEntry Item in clientsList)
            {
                TcpClient broadcastSocket;
                HandleClient hc = (HandleClient)Item.Value;
                broadcastSocket = hc.clientSocket;
                NetworkStream broadcastStream = broadcastSocket.GetStream();
                //Write=() send()
                broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
                broadcastStream.Flush();
            }
            mut.ReleaseMutex();
        } //end broadcast function

        public static void UserAdd(string clientName)
        {

        }
    }

    class HandleClient
    {
        public TcpClient clientSocket;
        public int userID;
        public string userName;

        public Hashtable clientsList;
        private bool noConnection = false;

        public void StartClinet(TcpClient inClientSocket, Hashtable cList, int userSerial)
        {
            userID = userSerial;
            this.clientSocket = inClientSocket;
            this.clientsList = cList;

            //쓰레드한테 채팅 일 시키기
            Thread ctThread = new Thread(DoChat);
            ctThread.Start();
        }

        private void DoChat()
        {

        }
    }
}
