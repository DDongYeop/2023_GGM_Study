using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HitAIState : CommonAIState
{
    public override void OnEnterState()
    {
        _enemyController.AgentAnimator.OnAnimationEndTrigger += AnimationEndHandle;
        _enemyController.AgentAnimator.SetHurtTrigger(true);
        
        _enemyController.transform.rotation = Quaternion.LookRotation(GameManager.Instance.PlayerTrm.position);
    }

    public override void OnExitState()
    {
        _enemyController.AgentAnimator.OnAnimationEndTrigger -= AnimationEndHandle;
        _enemyController.AgentAnimator.SetHurtTrigger(false);
    }

    private void AnimationEndHandle()
    {
        _aiActionData.IsHit = false;
    }

    private void FixedUpdate()
    {
        //이건 넉백처리 떄만 사용
    }
}
