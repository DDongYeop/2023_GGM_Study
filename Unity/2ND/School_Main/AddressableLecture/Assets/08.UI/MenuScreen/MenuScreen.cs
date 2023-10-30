using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor.AddressableAssets.Build;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UIElements;

public class MenuScreen : MonoBehaviour
{
    private UIDocument _uiDocument;

    private void Awake()
    {
        _uiDocument = GetComponent<UIDocument>();
    }

    private void OnEnable()
    {
        var root = _uiDocument.rootVisualElement;
        root.Q<Button>("btn-start").RegisterCallback<ClickEvent>(HandleGameStart);
        root.Q<Button>("btn-exit").RegisterCallback<ClickEvent>(HandleExitStart);
    }

    private async void HandleGameStart(ClickEvent evt)
    {
        //오브젝트 풀링 시작 
        await AssetLoader.Instance.MakePooling();
        SceneManager.LoadScene(SceneList.Game);
    }

    private void HandleExitStart(ClickEvent evt)
    {
        Application.Quit();
    }
}
