using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    [SerializeField] private TMP_InputField _nickName;
    [SerializeField] private TMP_InputField _chat;
    private string _myId;

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

    public void SendCommand(string cmd)
    {
        SocketModule.Instance.SendMessage(cmd);
        Debug.Log($"cmd send: {cmd}");
    }
}
