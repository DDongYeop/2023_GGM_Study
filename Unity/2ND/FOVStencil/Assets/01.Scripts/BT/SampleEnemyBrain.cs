using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SampleEnemyBrain : EnemyBrain
{
    public override void Attack()
    {
        Debug.Log("Attack");
    }
}
