using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

[CreateAssetMenu(menuName ="SO/InputReader")]
public class InputReader : ScriptableObject, Controls.IPlayerActions
{
    public event Action<Vector2> MovementEvent;
    public event Action<bool> FireEvent;
    public Vector2 AimPosition { get; private set; }

    public event Action<bool> ArmedEvent;
    public event Action ReloadEvent;

    private Controls _controls;

    private void OnEnable()
    {
        if(_controls == null)
        {
            _controls = new Controls();
            _controls.Player.SetCallbacks(this);
        }
        _controls.Player.Enable();
    }

    public void OnAim(InputAction.CallbackContext context)
    {
        AimPosition = context.ReadValue<Vector2>();
    }

    public void OnFire(InputAction.CallbackContext context)
    {
        if(context.performed)
        {
            FireEvent?.Invoke(true);
        }else if(context.canceled)
        {
            FireEvent?.Invoke(false);
        }
    }

    public void OnMovement(InputAction.CallbackContext context)
    {
        Vector2 value = context.ReadValue<Vector2>();
        MovementEvent?.Invoke(value);
    }

    public void OnReload(InputAction.CallbackContext context)
    {
        if (context.performed)
            ReloadEvent?.Invoke();
    }

    public void OnArmed(InputAction.CallbackContext context)
    {
        if(context.performed)
            ArmedEvent?.Invoke(true);
        else if(context.canceled)
            ArmedEvent?.Invoke(false);
    }
}