using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckStateDecision : AIDecision
{
    [SerializeField]
    private CommonAIState _baseState;

    public override bool MakeADecision()
    {
        return _enemyController.CurrentState == _baseState;    
    }
}
