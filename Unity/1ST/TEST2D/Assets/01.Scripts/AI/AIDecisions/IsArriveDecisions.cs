using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsArriveDecisions : AIDecision
{
    public override bool MakeADecision()
    {
        _brain.StateInfoCompo.IsArrived = _brain.NavAgentCompo.IsArrived;
        return _brain.StateInfoCompo.IsArrived;
    }
}
