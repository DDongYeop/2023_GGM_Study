using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class SimpleEnemyBrain : EnemyBrain
{
    [SerializeField] private Bullet _bullet;
    [SerializeField] private Transform _firePos;

    private void Start()
    {
        CurrentMagazine = MaxMagazine;
    }

    public override void Attack()
    {
        CurrentMagazine--;
        Bullet bullet = Instantiate(_bullet, _firePos.position, transform.rotation);
    }
}
