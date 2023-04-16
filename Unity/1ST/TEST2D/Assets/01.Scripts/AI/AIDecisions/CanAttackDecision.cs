using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CanAttackDecision : AIDecision
{
    public bool IsMelee;
    
    public override bool MakeADecision()
    {
        if (IsMelee)
        {
            float cool = _brain.StateInfoCompo.MeleeCool;

            return _brain.StateInfoCompo.IsAttack == false && cool <= 0;
        }
        else
        {
            float cool = _brain.StateInfoCompo.RangeCool;

            return _brain.StateInfoCompo.IsAttack == false && cool <= 0;
        }
    }
}
