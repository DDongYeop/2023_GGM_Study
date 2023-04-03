using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class OffMeshClimb : MonoBehaviour
{
    [SerializeField] private int _offMeshAreaNumber = 4;
    [SerializeField] private float _climbSpeed = 1.5f;
    private NavMeshAgent _navAgent;

    private void Awake()
    {
        _navAgent = GetComponent<NavMeshAgent>();
    }

    private IEnumerator Start()
    {
        while (true)
        {
            yield return new WaitUntil(() => IsOnClimb());
            yield return StartCoroutine(ClimbOrDescend());
        }
    }

    //고박사의 유니티 네비게이션, 베르, 브레키스
    private IEnumerator ClimbOrDescend()
    {
        _navAgent.isStopped = true; //네비게이션 멈춤 
        OffMeshLinkData linkData = _navAgent.currentOffMeshLinkData;
        Vector3 start = linkData.startPos;
        Vector3 end = linkData.endPos;
        yield return null;
    }

    private bool IsOnClimb()
    {
        if (_navAgent.isOnOffMeshLink)
        {
            OffMeshLinkData linkData = _navAgent.currentOffMeshLinkData;

            if (linkData.offMeshLink != null && linkData.offMeshLink.area == _offMeshAreaNumber)
                return true;
        }

        return false;
    }
}
