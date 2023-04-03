using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class ChaseNavAgent : MonoBehaviour
{
    [SerializeField] private Transform _targetTrm;

    private NavMeshAgent _agent;

    private void Awake()
    {
        _agent = GetComponent<NavMeshAgent>();
    }

    private void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            /*Vector3 pos = _targetTrm.position;
            pos.y = transform.position.y;
            _agent.SetDestination(pos);*/

            Vector3 pos;
            if (GameManager.Instance.GetMouseWorldPosition(out pos))
            {
                _agent.SetDestination(pos);
            }
        }
    }
}
