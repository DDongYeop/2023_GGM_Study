using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class NavAgentMovement : MonoBehaviour
{
    private NavMeshAgent _navAgent;
    public NavMeshAgent NavAgent => _navAgent;

    private void Awake()
    {
        _navAgent = GetComponent<NavMeshAgent>();
    }

    public void MoveToTarget(Vector3 pos)
    {
        _navAgent.SetDestination(pos);
    }

    public bool CheckIsArrived()
    {
        if (_navAgent.pathPending == false && _navAgent.remainingDistance <= _navAgent.stoppingDistance)
            return true;
        return false;
    }

    public void StopImmediately()
    {
        _navAgent.SetDestination(transform.position); //자기자신을 목적지로 놓으면 바로 정지
    }
}
