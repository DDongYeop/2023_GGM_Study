using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class AIBrain : MonoBehaviour
{
    [SerializeField] private AIState _aiState;
    [SerializeField] private Transform _targetTrm;

    public Transform TargetTrm => _targetTrm;
    
    private NavMeshAgent _navAgent;

    private void Awake()
    {
        _navAgent = GetComponent<NavMeshAgent>();
    }

    public void SetDestination(Vector3 pos)
    {
        // 뭔가 일어나는 일 
        _navAgent.SetDestination(pos);
    }

    public void ChangeState(AIState nextState)
    {
        _aiState = nextState;
    }

    private void Update()
    {
        _aiState?.UpdateState();
    }
}
