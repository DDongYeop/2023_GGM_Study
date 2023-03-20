using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RollingState : CommonState
{
    [SerializeField] private float _rollingSpeed = 0.4f;
    
    public override void OnEnterState()
    {
        //마우스 보고 
        /*_animator.OnAnimationEndTrigger += RollingEndHandle;
        _agentMovement.IsActiveMove = false;
        _animator.SetRollingState(true);
        //어느 방향을 보고 회전시킬지 결정해야함, 마우스 보도록 
        Vector3 mousePos = _agentInput.GetMouseWorldPosition();
        Vector3 dir = mousePos - _agentController.transform.position;
        dir.y = 0;
        //_agentMovement.SetRotation(dir);
        _agentMovement.SetMovementVelocity(dir.normalized * _rollingSpeed);*/
        
        //키보드 사용 
        _animator.OnAnimationEndTrigger += RollingEndHandle;
        _agentMovement.IsActiveMove = false; 
        _animator.SetRollingState(true);
        _agentMovement.StopImmediately();
        _agentMovement.SetMovementVelocity(transform.forward * _rollingSpeed);
    }

    public override void OnExitState()
    {
        _animator.OnAnimationEndTrigger -= RollingEndHandle;
        _agentMovement.IsActiveMove = true;
        _animator.SetRollingState(false);
    }

    private void RollingEndHandle()
    {
        _agentMovement.StopImmediately();
        _agentController.ChangeState(Core.StateType.Normal);
    }
    
    public override void UpdateState()
    {
        //do nothing
    }
}
