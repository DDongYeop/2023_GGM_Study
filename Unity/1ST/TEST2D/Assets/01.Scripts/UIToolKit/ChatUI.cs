using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class ChatUI : MonoBehaviour
{
    [SerializeField] private VisualTreeAsset _chatMsgTemplate;
    
    private UIDocument _uiDocument;
    private VisualElement _root;

    private List<VisualElement> _chatList;
    private int _index = 0;

    private TextField _txtChat;
    private Button _sendBtn;
    private ScrollView _chatScroll;
    
    private void Awake()
    {
        _uiDocument = GetComponent<UIDocument>();
    }

    private void OnEnable()
    {
        _root = _uiDocument.rootVisualElement;
        //_chatList = _root.Query<VisualElement>(className: "chat").ToList();

        _txtChat = _root.Q<TextField>("TextChat");
        _sendBtn = _root.Q<Button>("BtnSend");
        _chatScroll = _root.Q<ScrollView>("ChatContent");
        
        _sendBtn.RegisterCallback<ClickEvent>(SendClickHandle);
        
        _txtChat.RegisterCallback<KeyUpEvent>(e =>
        {
            if (e.keyCode == KeyCode.Return)
                SendProcess();
        });
    }

    private void SendClickHandle(ClickEvent e)
    {
        SendProcess();
    }

    private void SendProcess()
    {
        VisualElement chatXML = _chatMsgTemplate.Instantiate();
        VisualElement chat = chatXML.Q("ChatMsg");
        
        chat.AddToClassList("chat");
        _chatScroll.Add(chatXML);

        Label label = chatXML.Q<Label>("MsgLabel");
        label.text = _txtChat.value;
        
        Debug.Log(_txtChat.value);
        _txtChat.SetValueWithoutNotify("");
        StartCoroutine(DelayCorutine(0.01f, chat));

    }

    private IEnumerator DelayCorutine(float time, VisualElement chat)
    {
        yield return new WaitForSeconds(time);
        chat.AddToClassList("on");
        _chatScroll.verticalScroller.value = _chatScroll.verticalScroller.highValue > 0 ? _chatScroll.verticalScroller.highValue : 0;
    }

    private void Update()
    {
        /*if (Input.GetButtonDown("Jump"))
        {
            if (_index == _chatList.Count)
            {
                _chatList.ForEach(x => x.RemoveFromClassList("on"));
                _index = 0;
            }
            else
            {
                _chatList[_index].AddToClassList("on");
                _index++;
            }
        }*/
        
    }
}
