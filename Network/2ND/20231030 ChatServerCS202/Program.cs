using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Collections;

namespace chatServerCS202
{
    class Program
    {   //사용자 관리 해시테이블
        const char CHAR_TERMINATOR = ';'; 
        const char CHAR_NAME = '$'; //닉넴 구분

        public static Hashtable clientsList = new Hashtable();
        private static int userCount = 0; //고유 ID
        private static Mutex mut = new Mutex();

        static void Main(string[] args)
        {
            try
            {
                //Socket(), Bind()
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
                    client.StartClient(clientSocket, clientsList, counter);
                }//end while

                clientSocket.Close();
                serverSocket.Stop();
                Console.WriteLine("exit");
                Console.ReadLine();
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }//end Main

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
        //응용) 닉네임, id 번호로 검색 해당 클라 메세지 보내기
        public static void Broadcast(string msg, string uName, bool flag)
        {
            byte[] broadcastBytes;
            List<object> deletedClients = new List<object>(); //오류 클라이언트 리스트

            //1. 클라이언트가 보내는 메세지
            if(flag == true)
            {
                broadcastBytes = Encoding.UTF8.GetBytes($"{uName}{CHAR_NAME}{msg}{CHAR_TERMINATOR}");
                //ex) 경동엽$안녕하세요
            }
            //2. 서버가 보내는 메세지
            else
            {
                broadcastBytes = Encoding.UTF8.GetBytes($"{msg}{CHAR_TERMINATOR}");
            }

            mut.WaitOne();
            foreach(DictionaryEntry Item in clientsList)
            {
                TcpClient broadcastSocket;
                HandleClient hc = (HandleClient)Item.Value;
                broadcastSocket = hc.clientSocket;
                NetworkStream broadcastStream = broadcastSocket.GetStream();
                try
                {
                    //Write() send()
                    broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
                    broadcastStream.Flush();
                }
                catch(Exception ex)
                {
                    deletedClients.Add(Item.Key);
                }
            }
            mut.ReleaseMutex();
            foreach(DictionaryEntry item in deletedClients)
            {
                TcpClient socket;
                HandleClient hc = (HandleClient)clientsList[item];
                socket = hc.clientSocket;
                socket.Close();
                clientsList.Remove(item);
            }
        }//end broadcast function

        public static void UserAdd(string userName)
        {
            //서버에서 보내는 브로드캐스트 메세지
            Broadcast($"{userName}{CHAR_NAME}#Enter#", "", false);
            Console.WriteLine(userName + " Joined Chat room");
        }

        public static void UserLeft(string userName, int userID)
        {
            if (clientsList.ContainsKey(userID)){
                Broadcast($"{userName}{CHAR_NAME}#Left#", "", false);
                Console.WriteLine(userName + " Left Chat room");
                //소켓 닫기
                TcpClient clientSocket = GetSocket(userID);
                clientSocket.Close();
                clientsList.Remove(userID);
            }
        }
    }//end Main class

    class HandleClient
    {
        const string COMMAND_MOVE = "#Move#";
        const char CHAR_TERMINATOR = ';';

        public float posX;
        public float posY;

        public TcpClient clientSocket;
        public int userID;
        public string userName;

        public Hashtable clientsList;
        private bool noConnection = false;

        public void StartClient(TcpClient inClientSocket, Hashtable cList, int userSerial)
        {
            userID = userSerial;
            this.clientSocket = inClientSocket;
            this.clientsList = cList;

            //스레드한테 채팅 일 시키기
            Thread ctThread = new Thread(DoChat);
            ctThread.Start();
        }

        //소켓 연결 상태 확인
        bool SocketConnected(Socket s)
        {
            bool part1 = s.Poll(1000, SelectMode.SelectRead);
            bool part2 = (s.Available == 0); //읽을 데이터가 없으면 part2 true
            if (part1 && part2)
            {
                return false;
            }
            else return true;
        }

        //스레드. 해당 클라한테 메세지를 받음
        private void DoChat()
        {
            byte[] bytesFrom = new byte[1024];
            string dataFromClient;
            NetworkStream networkStream = clientSocket.GetStream();

            while (!noConnection)
            {
                try
                {
                    int numBytesRead;
                    if (!SocketConnected(clientSocket.Client))
                    {
                        noConnection = true;
                    }
                    else
                    {
                        if (networkStream.DataAvailable)
                        {
                            dataFromClient = "";
                            while (networkStream.DataAvailable)
                            {
                                //Recv()
                                numBytesRead = networkStream.Read(bytesFrom, 0, bytesFrom.Length);
                                dataFromClient = Encoding.UTF8.GetString(bytesFrom, 0, numBytesRead);
                            }//end while
                            int idx = dataFromClient.IndexOf('$');

                            //처음 접속. 닉네임 전달
                            if(userName==null && idx > 0)
                            {
                                userName = dataFromClient.Substring(0, idx);
                                Program.UserAdd(userName);
                            }
                            //채팅 내용 전달
                            else if(idx+1 < dataFromClient.Length)
                            {
                                int pos = idx + 1;
                                dataFromClient = dataFromClient.Substring(pos, dataFromClient.Length-pos);
                                ProcessCommand(userName, dataFromClient);
                                Console.WriteLine(userName + ": " + dataFromClient);
                                Program.Broadcast(dataFromClient, userName, true);
                                //경동엽: 안녕하세요
                            }
                            else
                            {
                                dataFromClient = "";
                            }
                        }
                    }
                }
                catch(Exception ex)
                {
                    noConnection = true;
                    Console.WriteLine("Error: " + ex.ToString());
                }
            }//end while
            Program.UserLeft(userName, userID);
        }

        private string DelectTerminator(string remain)
        {
            int idx = remain.IndexOf(CHAR_TERMINATOR);
            if (idx >= 0)
            {
                remain = remain.Substring(0, idx);
            }
            return remain;
        }

        private void ProcessMove(string clientName, string remain)
        {
            var strs = remain.Split(',');
            posX = float.Parse(strs[0]);
            posY = float.Parse(strs[1]);
            Console.WriteLine($"User Move-{clientName} to {posX}, {posY}");
        }

        private void ProcessCommand(string clientName, string dataFromClient)
        {
            if (dataFromClient[0] == '#')
            {
                string command;
                string remain;
                int idx = dataFromClient.IndexOf('#', 1);
                if (idx > 1)
                {
                    //#move#1.4545,3.5687
                    command = dataFromClient.Substring(0, idx + 1);
                    if (command == COMMAND_MOVE)
                    {
                        remain = DelectTerminator(dataFromClient.Substring(idx + 1));
                        ProcessMove(clientName, remain);
                    }
                }
            }
        }
    }
}
