using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MeleeAttackAction : AIAction
{
    public override void TakeAction()
    {
        if (_brain.StateInfoCompo.IsAttack == false && _brain.StateInfoCompo.MeleeCool <= 0)
        {
            _brain.Attack(true);
        }
    }
}
