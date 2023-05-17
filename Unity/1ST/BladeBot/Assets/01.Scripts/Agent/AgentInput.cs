using System;
using UnityEngine;
using static Core.Define;

public class AgentInput : MonoBehaviour
{
    public event Action<Vector3> OnMovementKeyPress = null;
    public event Action OnAttackKeyPress = null; //1
    public event Action OnRollingKeyPress = null; //롤링키 눌렸을 때

    [SerializeField] private LayerMask _whatIsGround;

    private Vector3 _directionInput;

    void Update()
    {
        UpdateMoveInput();
        UpdateAttackInput(); //2
        UpdateRollingInput();
    }

    private void UpdateRollingInput()
    {
        if(Input.GetButtonDown("Jump"))
        {
            OnRollingKeyPress?.Invoke();
        }
    }

    private void UpdateAttackInput()  //3
    {
        if(Input.GetMouseButtonDown(0))
        {
            OnAttackKeyPress?.Invoke();
        }
    }

    private void UpdateMoveInput()
    {
        float horizontal = Input.GetAxisRaw("Horizontal"); //이게 Y축 움직임이 된다.
        float vertical = Input.GetAxisRaw("Vertical"); //이게 Z축움직임이 되고
        _directionInput = new Vector3(horizontal, 0, vertical);
        OnMovementKeyPress?.Invoke(_directionInput);
    }

    public Vector3 GetCurrentInputDirection()
    {
        Vector3 dir45 = Quaternion.Euler(0, -45f, 0) * _directionInput.normalized;
        return dir45;
    }

    public Vector3 GetMouseWorldPosition()
    {
        Ray ray = MainCam.ScreenPointToRay(Input.mousePosition);

        RaycastHit hit;

        bool result = Physics.Raycast(ray, out hit, MainCam.farClipPlane, _whatIsGround);
        if(result)
        {
            return hit.point;
        }else
        {
            return Vector3.zero;
        }
    }
}
