using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{
    [SerializeField] private CommonAIState _currentState;

    private Transform _targetTrm;
    public Transform TargetTrm => _targetTrm;

    protected virtual void Awake()
    {
        List<CommonAIState> _states = new List<CommonAIState>();
        transform.Find("AI").GetComponentsInChildren<CommonAIState>(_states);
        
        _states.ForEach((s => s.SetUp(transform))); //여기서 셋업이 시작되는거 
    }

    protected virtual void Start()
    {
        _targetTrm = GameManager.Instance.PlayerTrm;
    }

    public void ChangeState(CommonAIState state)
    {
        _currentState?.OnExitState();
        _currentState = state;
        _currentState?.OnEnterState();
    }

    protected virtual void Update()
    {
        _currentState?.UpdateState();
    }
}
