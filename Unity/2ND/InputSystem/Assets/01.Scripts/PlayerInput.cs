using System;
using System.Collections;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerInput : MonoBehaviour
{
    private UserInputAction _inputAction;

    public Action<Vector2> OnMovement;
    public Action OnJump;

    private bool _uiMode = false;

    private void Awake()
    {
        _inputAction = new UserInputAction();
        _inputAction.Player.Enable();
        _inputAction.Player.Jump.performed += Jump;

        _inputAction.UI.Submit.performed += UIPerformPress;

        #region 키변경
        
        
        _inputAction.Player.Disable();
        _inputAction.Player.Jump.PerformInteractiveRebinding()
            .WithControlsExcluding("Mouse") // 마우스 제외
            .WithCancelingThrough("<keyboard>/escape") //esc제외
            .OnComplete(op =>
            {
                Debug.Log(op.selectedControl.name);
                op.Dispose();
                _inputAction.Player.Enable();
                
                //저장 
                var json = _inputAction.SaveBindingOverridesAsJson(); 
                Debug.Log(json);
                //로드 / 어디든 저장을 해두면 된다 
                _inputAction.LoadBindingOverridesFromJson(json);
            })
            .OnCancel(op =>
            {
                Debug.Log("취소되었습니다");
                op.Dispose();
                _inputAction.Player.Enable();
            })
            .Start();
        
        
        // 여러개 있는 Movement 같은경우 Index 사용
        // .WithTargetBinding(Index)

        #endregion
    }

    private void Update()
    {
        Vector2 inputDir = _inputAction.Player.Movement.ReadValue<Vector2>();
        OnMovement?.Invoke(inputDir);

        if (Keyboard.current.escapeKey.wasPressedThisFrame)
        {
            _inputAction.Disable();
            if (_uiMode)
                _inputAction.UI.Enable();
            else
                _inputAction.Player.Enable();
            _uiMode = !_uiMode;
        }
    }
    
    private void UIPerformPress(InputAction.CallbackContext context)
    {
        Debug.Log("UI상태");
    }

    public void Jump(InputAction.CallbackContext context)
    {
        OnJump?.Invoke();
    }
}