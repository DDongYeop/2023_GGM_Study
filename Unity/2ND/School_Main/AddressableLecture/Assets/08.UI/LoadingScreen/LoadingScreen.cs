using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
using UnityEngine.UIElements;

public class LoadingScreen : MonoBehaviour
{
    private UIDocument _uiDocument;
    private Label _titleLabel;
    private Label _descLabel;
    private VisualElement _loadingComplete;

    private bool _isComplete = false;

    private void Awake()
    {
        _uiDocument = GetComponent<UIDocument>();
    }

    private void OnEnable()
    {
        var root = _uiDocument.rootVisualElement;
        _titleLabel = root.Q<Label>("title-label");
        _descLabel = root.Q<Label>("desc-label");
        _loadingComplete = root.Q<VisualElement>("load-complete");
        _loadingComplete.style.visibility = Visibility.Hidden;
        _isComplete = false;

        AssetLoader.OnCategoryMessage += HandleCategoryMsg;
        AssetLoader.OnDescMessage += HandleDescMsg;
        AssetLoader.OnLoadComplete += HandleLoadComplete;
    }

    private void OnDisable()
    {
        AssetLoader.OnCategoryMessage -= HandleCategoryMsg;
        AssetLoader.OnDescMessage -= HandleDescMsg;
        AssetLoader.OnLoadComplete -= HandleLoadComplete;
    }

    private void HandleCategoryMsg(string msg)
    {
        _titleLabel.text = msg;
    }

    private void HandleDescMsg(string msg)
    {
        _descLabel.text = msg;
    }

    private void HandleLoadComplete()
    {
        _titleLabel.text = "Loading Complete";
        _descLabel.text = "게임을 시작하다";
        _isComplete = true;
        _loadingComplete.style.visibility = Visibility.Visible;
    }

    private void Update()
    {
        if (_isComplete)
        {
            if (Keyboard.current.anyKey.wasPressedThisFrame)
            {
                SceneManager.LoadScene(SceneList.Menu);
            }
        }
    }
}
