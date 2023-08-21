using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UIElements;

public class UIController : MonoBehaviour
{
    private UIDocument _uiDocument;
    private VisualElement _menu;

    [SerializeField] private PlayerInput _playerInput;
    private Dictionary<string, InputAction> _inputMap;

    private void Awake()
    {
        _uiDocument = GetComponent<UIDocument>();
    }

    private void Start()
    {
        _inputMap = new Dictionary<string, InputAction>();
        _inputMap.Add("Fire", _playerInput.InputAction.Player.Fire);
        _inputMap.Add("Jump", _playerInput.InputAction.Player.Jump);
        _inputMap.Add("Movement", _playerInput.InputAction.Player.Movement);
    }

    private void OnEnable()
    {
        _menu = _uiDocument.rootVisualElement.Q("MenuBox");
        
        _menu.RegisterCallback<ClickEvent>(HandleKeyBindClick);
        
        _menu.Q<Button>("BtnCancel").RegisterCallback<ClickEvent>(evt => CloseWindow());
        
        //var json = _playerInput?.InputAction.SaveBindingOverridesAsJson(); 
        //_playerInput.InputAction.LoadBindingOverridesFromJson(json);
        
        CloseWindow();
    }

    private void Update()
    {
        if (Keyboard.current.escapeKey.wasPressedThisFrame)
            OpenWindow();
    }

    private void HandleKeyBindClick(ClickEvent evt)
    {
        var label = evt.target as UILabelWithData;
        if (label == null)
            return;

        var oldText = label.text;
        label.text = "listening . . ";

        if (_inputMap.TryGetValue(label.KeyData, out InputAction action))
        {
            var queue = action.PerformInteractiveRebinding();
            if (label.KeyData != "Fire")
                queue.WithControlsExcluding("Mouse");
            queue.WithTargetBinding(label.IndexData)
                .WithCancelingThrough("<keyboard>/escape")
                .OnComplete(op =>
                {
                    label.text = op.selectedControl.name;
                    op.Dispose();
                    var json = _playerInput.InputAction.SaveBindingOverridesAsJson(); 
                })
                .OnCancel(op =>
                {
                    label.text = oldText;
                })
                .Start();
        }
        else
            label.text = oldText;
    }

    private void OpenWindow()
    {
        _menu.AddToClassList("open");
        _playerInput.InputAction.Player.Disable();
    }
    
    private void CloseWindow()
    {
        _menu.RemoveFromClassList("open");
        _playerInput.InputAction?.Player.Enable();
    }
}
