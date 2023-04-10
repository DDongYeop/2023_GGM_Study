using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChaseAIState : CommonAIState
{
    public override void OnEnterState()
    {
        
    }

    public override void OnExitState()
    {
        
    }

    public override void UpdateState()
    {
        _enemyController.NavMovement.MoveToTarget(_aiActionData.LastSpotPoint);
        _aiActionData.IsArrived = _enemyController.NavMovement.CheckIsArrived(); //도착을 기록한다 
        
        base.UpdateState();
    }
}