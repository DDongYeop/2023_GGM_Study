using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AIBrain : MonoBehaviour
{
    public float ViewAngle;
    public float ViewRange;

    public Transform PlayerTrm;

    [SerializeField] private AIState _currentState; //현재 내 상태

    public NavAgent NavAgentCompo { get; private set; }
    public AIStateInfo StateInfoCompo { get; private set;  }
    
    private void Awake()
    {
        NavAgentCompo = GetComponent<NavAgent>();
        StateInfoCompo = transform.Find("AI").GetComponent<AIStateInfo>();
    }

    private void Update()
    {
        _currentState.UpdateState();
    }

    public void ChangeState(AIState nextState)
    {
        _currentState = nextState;
    }

    public void Attack(bool isMelee)
    {
        NavAgentCompo.StopImmediately();
        StateInfoCompo.IsAttack = true;
        
        if (isMelee)
        {
            StateInfoCompo.IsMelee = true;
            StateInfoCompo.MeleeCool = 1f;
            Debug.Log("밀리 공격");
            StartCoroutine(DelayCo(0.3f, () => StateInfoCompo.IsMelee = false));
        }
        else
        {
            StateInfoCompo.IsRange = true;
            StateInfoCompo.MeleeCool = 3f;
            Debug.Log("원거리 공격");
            StartCoroutine(DelayCo(0.8f, () => StateInfoCompo.IsRange = false));
        }
    }

    private IEnumerator DelayCo(float time, Action Callback)
    {
        yield return new WaitForSeconds(time);
        StateInfoCompo.IsAttack = false;
        Callback?.Invoke();
    }
}
