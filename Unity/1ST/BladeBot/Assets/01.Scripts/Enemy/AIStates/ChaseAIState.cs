using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChaseAIState : CommonAIState
{
    public override void OnEnterState()
    {
        _enemyController.AgentAnimator.SetSpeed(0.2f);
        _enemyController.AgentAnimator.OnAnimationEventTrigger += FootSteopHandle;
    }

    public override void OnExitState()
    {
        _enemyController.AgentAnimator.SetSpeed(0);
        _enemyController.AgentAnimator.OnAnimationEventTrigger -= FootSteopHandle;
    }

    private void FootSteopHandle()
    {
        _enemyController.VfxManager.PlayerFootStep();   
    }

    public override bool UpdateState()
    {
        _enemyController.NavMovement.MoveToTarget(_aiActionData.LastSpotPoint);
        _aiActionData.IsArrived = _enemyController.NavMovement.CheckIsArrived(); //도착을 기록한다 
        
        return base.UpdateState();
    }
}