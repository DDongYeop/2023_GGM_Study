using System;
using UnityEngine;

public class AgentInput : MonoBehaviour
{
    public event Action<Vector3> OnMovementKeyPress = null;

    private void Update()
    {
        UPdateMoveInput();
    }

    private void UPdateMoveInput()
    {
        float horizontal = Input.GetAxisRaw("Horizontal");
        float vertical = Input.GetAxisRaw("Vertical");
        OnMovementKeyPress?.Invoke(new Vector3(horizontal, 0, vertical));
    }
}
