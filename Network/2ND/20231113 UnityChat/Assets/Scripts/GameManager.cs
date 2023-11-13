using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using TMPro;

public class GameManager : Singleton<GameManager>
{
    const float ATTACK_RADIUS = 3.5f;
    const char CHAR_TERMINATOR = ';';
    const char CHAR_COMMA = ',';

    private UserControl userControl;

    [SerializeField] private TMP_InputField nickName;
    [SerializeField] private TMP_InputField Chat;
    string myID;

    public GameObject prefabUser; //타 클라
    public GameObject User; //나
    public TextMeshProUGUI textBox;

    Dictionary<string, UserControl> remoteUsers;
    Queue<string> commandQueue;

    private void Start()
    {
        userControl = User.GetComponent<UserControl>();
        remoteUsers = new Dictionary<string, UserControl>();
        commandQueue = new Queue<string>();
    }

    private void Update()
    {
        ProcessQueue();
    }

    public void Attack()
    {
        Collider2D[] damageUsers = Physics2D.OverlapCircleAll(User.transform.position, ATTACK_RADIUS);
        System.Text.StringBuilder damageString = new System.Text.StringBuilder();

        for (int i = 0; i < damageUsers.Length; i++)
        {
            UserControl userControl = damageUsers[i].GetComponent<UserControl>();
            foreach (var item in remoteUsers)
            {
                if (item.Value == userControl)
                {
                    damageString.Append(item.Key);
                    damageString.Append(',');
                }
            }
        }
        SendCommand($"#Attack#{damageString}");
    }

    public void SendCommand(string cmd)
    {
        SocketModule.Instance.SendData(cmd);
        Debug.Log("cmd send: " + cmd);
    }

    public void QueueCommand(string cmd)
    {
        commandQueue.Enqueue(cmd);
    }

    public void ProcessQueue()
    {
        while (commandQueue.Count > 0)
        {
            string nextCommand = commandQueue.Dequeue();
            ProcessCommand(nextCommand);
        }
    }

    public void ProcessCommand(string cmd)
    {
        bool isMore = true;
        while (isMore)
        {
            Debug.Log("Process cmd = " + cmd);
            //ID
            int nameIdx = cmd.IndexOf("$");
            string id = "";
            if (nameIdx > 0)
            {
                id = cmd.Substring(0, nameIdx);
            }
            //Command
            int cmdIdx1 = cmd.IndexOf("#");
            //if(cmdIdx1 > nameIdx)
            //{
            int cmdIdx2 = cmd.IndexOf("#", cmdIdx1 + 1);
            if (cmdIdx2 > cmdIdx1)
            {
                string command = cmd.Substring(cmdIdx1 + 1, cmdIdx2 - cmdIdx1 - 1);
                //End
                string remain = "";
                string nextCommand;
                int endIdx = cmd.IndexOf(CHAR_TERMINATOR, cmdIdx2 + 1);
                if (endIdx > cmdIdx2)
                {
                    remain = cmd.Substring(cmdIdx2 + 1, endIdx - cmdIdx2 - 1);
                    nextCommand = cmd.Substring(endIdx + 1);
                }
                else
                {
                    nextCommand = cmd.Substring(cmdIdx2 + 1);
                }
                
                Debug.Log($"command={command} id={id} remain={remain} next={nextCommand}");

                if (command == "Attack")
                {
                    TakeDamage(remain);
                }
                if (myID.CompareTo(id) != 0)
                {
                    TextboxMessage(id, command);
                    switch (command)
                    {
                        case "Enter":
                            AddUser(id);
                            break;
                        case "Move":
                            SetMove(id, remain);
                            break;
                        case "Left":
                            UserLeft(id);
                            break;
                        case "Heal":
                            UserHeal(id);
                            break;
                    }
                }

                else
                {
                    TextboxMessage(id, command);
                    Debug.Log("Skip");
                }
                cmd = nextCommand;
                if (cmd.Length <= 0)
                {
                    isMore = false;
                }
            }
            else
            {
                TextboxMessage(id, cmd.Substring(nameIdx+1));
                isMore = false;
            }
            //}
            //else
            //{
            //isMore = false;
            //}
        }

    }

    public void OnLogin()
    {
        myID = nickName.text;
        if (myID.Length > 0)
        {
            SocketModule.Instance.Login(myID);
            User.transform.position = Vector3.zero;
        }
    }
    public void OnLogOut()
    {
        SocketModule.Instance.Logout();
        foreach (var user in remoteUsers)
        {
            Destroy(user.Value.gameObject);
        }
        remoteUsers.Clear();
    }
    public void OnRevive()
    {
        userControl.Revive();
        string data = "#Heal#";
        SendCommand(data);
    }
    public void OnMessage()
    {
        if (myID != null)
        {
            SocketModule.Instance.SendData(Chat.text);
        }
    }

    public void AddUser(string id)
    {
        UserControl uc = null;
        if (!remoteUsers.ContainsKey(id))
        {
            GameObject newUser = Instantiate(prefabUser);
            uc = newUser.GetComponent<UserControl>();
            uc.isRemote = true;
            remoteUsers.Add(id, uc);
        }
    }

    public void UserLeft(string id)
    {
        if (remoteUsers.ContainsKey(id))
        {
            UserControl uc = remoteUsers[id];
            Destroy(uc.gameObject);
            remoteUsers.Remove(id);
        }
    }

    public void UserHeal(string id)
    {
        if (remoteUsers.ContainsKey(id))
        {
            UserControl uc = remoteUsers[id];
            uc.Revive();
        }
    }

    public void SetMove(string id, string cmdMove)
    {
        if (remoteUsers.ContainsKey(id))
        {
            UserControl uc = remoteUsers[id];
            string[] strs = cmdMove.Split(CHAR_COMMA);
            Vector3 pos = new Vector3(float.Parse(strs[0]), float.Parse(strs[1]), 0);
            uc.targetPos = pos;
        }
    }

    public void TakeDamage(string remain)
    {
        var strs = remain.Split(CHAR_COMMA);
        Debug.Log(strs[0]);
        for (int i = 0; i < strs.Length; i++)
        {
            if (remoteUsers.ContainsKey(strs[i]))
            {
                Debug.Log(strs[i]);
                UserControl uc = remoteUsers[strs[i]];
                if (uc != null)
                {
                    uc.DropHP(10);
                }
            }
            else
            {
                if (myID.CompareTo(strs[i]) == 0)
                {
                    userControl.DropHP(10);
                }
            }
        }
    }

    public void TextboxMessage(string name, string content)
    {
        textBox.text += $"\n{name}:{content}";
    }
}
