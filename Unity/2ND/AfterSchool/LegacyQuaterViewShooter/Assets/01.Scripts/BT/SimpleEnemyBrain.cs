using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SimpleEnemyBrain : EnemyBrain
{
    public override void Attack()
    {
        Debug.Log("공격 개시");
    }
}
