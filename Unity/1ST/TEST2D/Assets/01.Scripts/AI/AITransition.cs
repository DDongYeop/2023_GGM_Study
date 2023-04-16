using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting.Dependencies.Sqlite;
using UnityEngine;

public class AITransition : MonoBehaviour
{
    public List<AIDecision> Decisions = null;
    public AIState NextState;

    public void SetUp(AIBrain brain)
    {
        Decisions = new List<AIDecision>();
        GetComponents<AIDecision>(Decisions);
        Decisions.ForEach(d => d.Setup(brain));
    }

    public bool CheckTransition()
    {
        bool result = false;

        foreach (AIDecision d in Decisions)
        {
            result = d.MakeADecision();
            if (d.IsReverse)
                result = !result;
            if (result == false)
                break;
        }
        
        return result;
    }
}
