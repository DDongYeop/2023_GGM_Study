using UnityEngine;

public class RollingState : CommonState
{
    [SerializeField]
    private float _rollingSpeed = 0.4f, _animationThreshold = 0.1f;  //애니메이션 쓰레스홀드

    private float _timer = 0;
    public override void OnEnterState()
    {
        _animator.OnAnimationEndTrigger += RollingEndHandle;
        _animator.SetRollingState(true);
        _agentMovement.IsActiveMove = false;
        //여기서 어느 방향을 보고 회전시킬지 결정해야 한다. 지금은 마우스를 보도록 해본다.
        //Vector3 mousePos = _agentInput.GetMouseWorldPosition();
        //Vector3 dir = mousePos - _agentController.transform.position;

        //_agentMovement.SetRotation(mousePos);

        Vector3 keyDir = _agentInput.GetCurrentInputDirection();
        //여기서 받았는데 만약 키를 안누르고 있었다면 지금 바라보는 방향으로 롤링들어가자.
        if(keyDir.magnitude < 0.1f)
        {
            keyDir = _agentController.transform.forward;
        }
        _agentMovement.SetRotation(keyDir + _agentController.transform.position);
        _agentMovement.SetMovementVelocity(keyDir.normalized * _rollingSpeed);
        _timer = 0; //타이머 시작
    }
    
    public override void OnExitState()
    {
        _animator.OnAnimationEndTrigger -= RollingEndHandle;
        _agentMovement.IsActiveMove = true;
        _animator.SetRollingState(false);
    }
    private void RollingEndHandle()
    {
        if (_timer < _animationThreshold) return;

        _agentMovement.StopImmediately();
        _agentController.ChangeState(Core.StateType.Normal);
    }

    public override bool UpdateState()
    {
        _timer += Time.deltaTime;
        return true;
    }
}