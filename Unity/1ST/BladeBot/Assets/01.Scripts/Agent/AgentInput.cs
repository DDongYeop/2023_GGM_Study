using System;
using UnityEngine;

public class AgentInput : MonoBehaviour
{
    public event Action<Vector3> OnMovementKeyPress = null;
    public event Action OnAttackKeyPress = null;
    
    private void Update()
    {
        UpdateMoveInput();
        UpdateAttackInput();
    }

    private void UpdateAttackInput()
    {
        if (Input.GetMouseButtonDown(0))
            OnAttackKeyPress?.Invoke();
    }

    private void UpdateMoveInput()
    {
        float horizontal = Input.GetAxisRaw("Horizontal");
        float vertical = Input.GetAxisRaw("Vertical");
        OnMovementKeyPress?.Invoke(new Vector3(horizontal, 0, vertical));
    }
}
