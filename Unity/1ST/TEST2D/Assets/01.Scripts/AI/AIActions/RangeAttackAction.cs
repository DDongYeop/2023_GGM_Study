using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RangeAttackAction : AIAction
{
    public override void TakeAction()
    {
        if (_brain.StateInfoCompo.IsAttack == false && _brain.StateInfoCompo.RangeCool <= 0)
        {
            _brain.Attack(true);
        }
    }
}
