using UnityEngine;
using UnityEngine.Events;

public class AgentInput : MonoBehaviour
{
    [SerializeField] private LayerMask _whatIsGround;

    public UnityEvent<Vector3> OnMovementKeyPress = null;

    private void Update()
    {
        UpdateMoveInput();
    }

    private void UpdateMoveInput()
    {
        float horizontal = Input.GetAxisRaw("Horizontal");
        float vertical = Input.GetAxisRaw("Vertical");
        OnMovementKeyPress?.Invoke(new Vector3(horizontal, 0, vertical));
    }
}
