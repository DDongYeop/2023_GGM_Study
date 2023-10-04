using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
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
        
    }
}
