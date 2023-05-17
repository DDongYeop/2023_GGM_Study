using System.Collections;
using System.Collections.Generic;
using Core;
using UnityEngine;

public class OnHitState : CommonState
{
    [SerializeField] private float _recoverTime = 0.3f;
    private float _hitTimer;
    
    public override void OnEnterState()
    {
        _agentController.AgentMovementCompo.StopImmediately();
        _agentController.AgentHealthCompo.OnHitTriggered.AddListener(HandleHit);
    }

    public override void OnExitState()
    {
        _agentController.AgentHealthCompo.OnHitTriggered.RemoveListener(HandleHit);
        _animator.SetisHit(false);
        _animator.SetHurtTrigger(false);
    }

    public override bool UpdateState()
    {
        _hitTimer += Time.deltaTime;
        if (_hitTimer >= _recoverTime)
        {
            _agentController.ChangeState(StateType.Normal);
            return true;
        }
        return false;
    }

    private void HandleHit(int damage, Vector3 point, Vector3 normal)
    {
        CameraManager.Instance.CameraShake();
        normal.y = 0;
        _hitTimer = 0;
        _animator.SetisHit(true);
        _animator.SetHurtTrigger(true);
        _agentController.transform.rotation = Quaternion.LookRotation(normal);
    }
}
