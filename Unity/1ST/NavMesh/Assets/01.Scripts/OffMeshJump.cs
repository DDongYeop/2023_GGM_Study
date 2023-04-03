using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class OffMeshJump : MonoBehaviour
{
    [SerializeField] private float _jumpSpeed = 10;
    [SerializeField] private float _gravity = -9.81f;
    [SerializeField] private int _offMeshAreaNumber = 2;
    
    private NavMeshAgent _navAgent;

    private void Awake()
    {
        _navAgent = GetComponent<NavMeshAgent>();
    }

    private IEnumerator Start()
    {
        while (true)
        {
            yield return new WaitUntil(() => IsOnJump());
            yield return StartCoroutine(JumpTo());
        }
    }

    private IEnumerator JumpTo()
    {
        _navAgent.isStopped = true;
        OffMeshLinkData linkData = _navAgent.currentOffMeshLinkData;
        Vector3 start = transform.position;
        Vector3 end = linkData.endPos;

        float jumpTime = Mathf.Max(0.3f, Vector3.Distance(start, end) / _jumpSpeed);
        float currentTime = 0;
        float percent = 0;

        float v0 = (end - start).y - _gravity;

        while (percent < 1)
        {
            //포물선 운동 : 시작위치 + 초기속도 * 시간 + 중력 * 시간의제곱
            currentTime += Time.deltaTime;
            percent = currentTime / jumpTime;

            Vector3 pos = Vector3.Lerp(start, end, percent);
            pos.y = start.y + (v0 * percent) + (_gravity * percent * percent);

            transform.position = pos;
            yield return null;
        }
        
        _navAgent.CompleteOffMeshLink();
        _navAgent.isStopped = false;
    }

    private bool IsOnJump()
    {
        print(_navAgent.isOnOffMeshLink);
        if(_navAgent.isOnOffMeshLink)
        {
            OffMeshLinkData linkData = _navAgent.currentOffMeshLinkData;

            if(linkData.offMeshLink != null && linkData.offMeshLink.area == _offMeshAreaNumber)
            {
                return true;
            }
        }
        return false;
    }
}
