using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public abstract class EnemyBrain : MonoBehaviour
{
    public Transform targetTrm;
    //기타 등등 브레인에서 필요한 것들을 여기 넣어라
    
    public NavMeshAgent NavAgent { get; private set; }

    
    public int MaxMagazine;
    public int CurrentMagazine;

    private void Awake()
    {
        NavAgent = GetComponent<NavMeshAgent>();
    }

    public abstract void Attack();
}
