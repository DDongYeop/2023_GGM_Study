using Core;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OnHitState : CommonState
{
    [SerializeField]
    private float _recoverTime = 0.3f; //0.3초 리커버리 타임
    private float _hitTimer; 

    public override void OnEnterState()
    {
        _agentController.AgentMovementCompo.StopImmediately();
        _agentController.AgentHealthCompo.OnHitTriggered.AddListener(HandleHit);
    }

    public override void OnExitState()
    {
        _agentController.AgentHealthCompo.OnHitTriggered.RemoveListener(HandleHit);
        _animator.SetIsHit(false);
        _animator.SetHurtTrigger(false); 
    }

    public override bool UpdateState()
    {
        //피격시간만큼 넉백당하면서 애니메이션이 재생되어야 해
        _hitTimer += Time.deltaTime;
        //_agentController.AgentMovementCompo.IsActiveMove = fal
        if(_hitTimer >= _recoverTime)
        {
            _agentController.ChangeState(StateType.Normal); //노말상태로 전환
            return true;
        }
        return false;
    }
    private void HandleHit(int damage, Vector3 point, Vector3 normal)
    {
        normal.y = 0;
        _hitTimer = 0; //시작
        _animator.SetIsHit(true);
        _animator.SetHurtTrigger(true);
        _agentController.transform.rotation = Quaternion.LookRotation(normal);
    }
}
