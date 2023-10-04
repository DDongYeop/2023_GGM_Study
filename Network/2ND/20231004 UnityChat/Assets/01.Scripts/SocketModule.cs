using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;

public class SocketModule : MonoBehaviour
{
    public static SocketModule Instance;

    private TcpClient _clientSocket;
    private NetworkStream _serverStream = default;
    private string _nickName;
    private bool _isRunning = false;

    private void Awake()
    {
        if (Instance != null)
            Debug.LogError("Multiple SocketModule is running");
        Instance = this;
    }

    public void Login(string id)
    {
        if (!_isRunning)
        {
            _clientSocket = new TcpClient();
            IPAddress address = IPAddress.Parse("127.0.0.1"); //"localhost"
            _clientSocket.Connect(address, 8888);
            _serverStream = _clientSocket.GetStream();

            byte[] outStream = Encoding.UTF8.GetBytes(id + '$');
            _serverStream.Write(outStream, 0, outStream.Length);
            _serverStream.Flush();

            Thread ctThread = new Thread(GetMessage);
            ctThread.Start();
            _isRunning = true;
            _nickName = id;
        }
    }

    private void GetMessage()
    {
        byte[] inStream = new byte[1024];
        string retrunData = "";
        try
        {
            while (_isRunning)
            {
                _serverStream = _clientSocket.GetStream();
                int buffsize = _clientSocket.ReceiveTimeout;
                int numBytesRead;

                if (_serverStream.DataAvailable)
                {
                    while (_serverStream.DataAvailable)
                    {
                        numBytesRead = _serverStream.Read(inStream, 0, inStream.Length);
                        retrunData += Encoding.UTF8.GetString(inStream, 0, numBytesRead);
                    }
                }
            }
        }
        catch (Exception ex)
        {
            _isRunning = false;
        }
    }

    public void SendData(string str)
    {
        if (_isRunning && _serverStream != null)
        {
            byte[] outStream = Encoding.UTF8.GetBytes('$' + str);
            _serverStream.Write(outStream, 0, outStream.Length);
            _serverStream.Flush();
        }
    }

    public void LogOut()
    {
        if (_isRunning)
        {
            _isRunning = false;
            _nickName = "";
        }
        if (_serverStream != null)
        {
            _serverStream.Close();
            _serverStream = null;
        }
        _clientSocket.Close();
    }
}
