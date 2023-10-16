using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    [SerializeField] private TMP_InputField _nickName;
    [SerializeField] private TMP_InputField _chat;
    private string _myId;

    private const char _char_terminator = ';';
    private const char _char_comma = ',';
    private const char _char_name = '$';
    private const char _char_command = '#';

    private Queue<string> _commandQueue;

    private void Start()
    {
        _commandQueue = new Queue<string>();
    }

    private void Update()
    {
        ProcessQueue();
    }

    public void OnLogin()
    {
        _myId = _nickName.text;
        if (_myId.Length > 0)
        {
            SocketModule.Instance.Login(_myId);
        }
    }

    public void OnLogout()
    {
        SocketModule.Instance.LogOut();
        //유저 프리팹 삭제
    }

    public void OnMessage()
    {
        if (_myId != null)
        {
            SocketModule.Instance.SendMessage(_chat.text);
        }
    }

    public void OnRevive()
    {
        //회복
        string data = "#Heal#";
        SendCommand(data);
    }

    //스트링 패킷 서버
    public void SendCommand(string cmd)
    {
        SocketModule.Instance.SendMessage(cmd);
        Debug.Log($"cmd send: {cmd}");
    }

    public void QueueCommand(string cmd)
    {
        _commandQueue.Enqueue(cmd);
    }

    public void ProcessQueue()
    {
        while (_commandQueue.Count > 0)
        {
            string nextCommand = _commandQueue.Dequeue();
            ProcessCommand(nextCommand);
        }
    }
    
    //스트링 파싱
    public void ProcessCommand(string cmd)
    {
        bool isMore = true;

        while (isMore)
        {
            Debug.Log($"Process cmd = {cmd}");
            
            //닉네임
            int nameIdx = cmd.IndexOf(_char_name);
            string id = "";
            if (nameIdx > 0)
                id = cmd.Substring(0, nameIdx);
            
            //Command #MOVE#
            int cmdIdx1 = cmd.IndexOf(_char_command);
            if (cmdIdx1 > nameIdx)
            {
                int cmdIdx2 = cmd.IndexOf(_char_command, cmdIdx1+1);
                if (cmdIdx2 > cmdIdx1)
                {
                    string command = cmd.Substring(++cmdIdx1, cmdIdx2);

                    string remain = "";
                    string nextCommand;
                    int endIdx = cmd.IndexOf(_char_terminator, cmdIdx2 + 1);
                    if (endIdx > cmdIdx2)
                    {
                        remain = cmd.Substring(cmdIdx2 + 1, endIdx - cmdIdx2 - 1);
                        nextCommand = cmd.Substring(endIdx + 1);
                    }
                    else
                        nextCommand = cmd.Substring(cmdIdx2 + 1);

                    Debug.Log($"command = {command}, id={id}, remain={remain}, next={nextCommand}");

                    if (_myId.CompareTo(id) != 0)
                    {
                        switch (command)
                        {
                            case "Enter":
                                break;
                            case "Move":
                                break;
                            case "Left":
                                break;
                            case "Heal":
                                break;
                        }
                    }
                    else
                    {
                        Debug.Log("Skip");
                    }

                    cmd = nextCommand;
                    if (cmd.Length <= 0)
                    {
                        isMore = false;
                    }
                } //end if
                else 
                    isMore = false;
            } //end if
            else 
                isMore = false;
        }
    }
}
