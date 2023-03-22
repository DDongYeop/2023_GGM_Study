using System;
using UnityEngine;
using Core;
using static Core.Define;

public class AgentInput : MonoBehaviour
{
    public event Action<Vector3> OnMovementKeyPress = null;
    public event Action OnAttackKeyPress = null;
    public event Action OnRollingKeyPress = null; //롤링키 눌렸을떄 

    [SerializeField] private LayerMask _whatIsGround;
    private Vector3 _directionInpit;
    
    private void Update()
    {
        UpdateMoveInput();
        UpdateAttackInput();
        UpdateRollingInput();
    }

    private void UpdateRollingInput()
    {
        if (Input.GetButtonDown("Jump"))
        {
            OnRollingKeyPress?.Invoke();
        }
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
        _directionInpit = new Vector3(horizontal, 0, vertical);
        OnMovementKeyPress?.Invoke(_directionInpit);
    }

    public Vector3 GetCurrentInputDirection()
    {
        Vector3 dir45 = Quaternion.Euler(0, -45, 0) * _directionInpit.normalized;
        return dir45;
    }

    public Vector3 GetMouseWorldPosition()
    {
        Ray ray = MainCam.ScreenPointToRay(Input.mousePosition);

        RaycastHit hit;
        bool result = Physics.Raycast(ray,  out hit, MainCam.farClipPlane, _whatIsGround);
        if (result)
            return hit.point;
        else 
            return Vector3.zero;
    }
}
