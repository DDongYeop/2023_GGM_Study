using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class EnemyAttack : MonoBehaviour
{
    private AIActionData _aiActionData;

    protected virtual void Awake()
    {
        _aiActionData = transform.Find("AI").GetComponent<AIActionData>();
    }

    public abstract void Attack(int damage, Vector3 targetVector);

    public abstract void PreAttack();

    public abstract void CancelAttack();
}
