using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public abstract class EnemyBrain : MonoBehaviour
{
    public Transform targetTrm;
    
    public NavMeshAgent NavAgent { get; private set; }

    protected virtual void Awake()
    {
        NavAgent = GetComponent<NavMeshAgent>();
    }

    public abstract void Attack();
}
