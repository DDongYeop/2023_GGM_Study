using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class MainUI : MonoBehaviour
{
    private UIDocument _uiDocument;

    private void Awake()
    {
        _uiDocument = GetComponent<UIDocument>();
    }

    private void OnEnable()
    {
        VisualElement root = _uiDocument.rootVisualElement;
        // 이녀석은 UI Obj다. 모든 애들의 근간이 된다 

        Button btn = root.Q<Button>("BtnOpen");
        // Query => 질의, 질문
        btn.RegisterCallback<ClickEvent>(e =>
        {
            Debug.Log("버튼이 클릭됨");
        });
    }
}
