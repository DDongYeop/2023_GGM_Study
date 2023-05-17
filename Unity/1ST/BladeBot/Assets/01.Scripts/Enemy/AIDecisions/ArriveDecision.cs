using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArriveDecision : AIDecision
{
    public override bool MakeADecision()
    {
        return _aiActionData.IsArrived;
    }
}
