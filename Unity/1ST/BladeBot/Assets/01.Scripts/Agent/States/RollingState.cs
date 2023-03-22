using UnityEngine;

public class RollingState : CommonState
{
    [SerializeField] private float _rollingSpeed = 0.4f, _animationThreshold = 0.1f;
    private float _timer = 0;
    
    public override void OnEnterState()
    {
        //마우스 보고 
        /*_animator.OnAnimationEndTrigger += RollingEndHandle;
        _animator.SetRollingState(true);
        _agentMovement.IsActiveMove = false;
        //어느 방향을 보고 회전시킬지 결정해야함, 마우스 보도록 
        Vector3 mousePos = _agentInput.GetMouseWorldPosition();
        Vector3 dir = mousePos - _agentController.transform.position;
        dir.y = 0;
        //_agentMovement.SetRotation(dir);
        _agentMovement.SetMovementVelocity(dir.normalized * _rollingSpeed);*/
        
        //키보드 사용 
        _animator.OnAnimationEndTrigger += RollingEndHandle;
        _animator.SetRollingState(true);
        _agentMovement.IsActiveMove = false;
        Vector3 keyDir = _agentInput.GetCurrentInputDirection();
        // 바라보는 방향으로 
        if (keyDir.magnitude < .1f)
            keyDir = _agentController.transform.forward;
        _agentMovement.SetMovementVelocity(keyDir + _agentController.transform.position);
        _agentMovement.SetMovementVelocity(keyDir.normalized * _rollingSpeed);
        _timer = 0;
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
        _timer += Time.deltaTime;
    }
}
