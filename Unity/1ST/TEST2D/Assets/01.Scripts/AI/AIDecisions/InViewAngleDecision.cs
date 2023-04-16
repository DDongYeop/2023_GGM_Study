using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InViewAngleDecision : AIDecision
{
    public override bool MakeADecision()
    {
        Vector3 right = _brain.transform.right;
        Vector3 direction = (_brain.PlayerTrm.position - _brain.transform.position).normalized;

        float degreeAngle = Vector3.Angle(right, direction);

        return degreeAngle < _brain.ViewAngle * .5f;
    }
}
