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

        VisualElement popupWindow = root.Q("PopupWindow");

        Button openBtn = root.Q<Button>("BtnOpen");
        // Query => 질의, 질문
        openBtn.RegisterCallback<ClickEvent>(e =>
        {
            Time.timeScale = 0;
            popupWindow.AddToClassList("open");
        });
        Button closeBtn = root.Q<Button>("BtnClose");
        closeBtn.RegisterCallback<ClickEvent>(e =>
        {
            Time.timeScale = 1;
            popupWindow.RemoveFromClassList("open");
        });
    }
}
