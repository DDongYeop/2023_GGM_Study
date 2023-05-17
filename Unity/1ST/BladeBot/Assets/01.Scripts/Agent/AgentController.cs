using Core;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AgentController : MonoBehaviour
{
    [SerializeField]
    private CharacterDataSO _charDataSO;
    public CharacterDataSO CharData => _charDataSO;

    private Dictionary<StateType, IState> _stateDictionary = null;  //가지고 있는 상태들 저장
    private IState _currentState; //현재 상태 저장

    public String CurrentState;

    public AgentMovement AgentMovementCompo { get; private set; }
    public DamageCaster DamageCasterCompo { get; private set; }

    public bool isDead { get; private set; }
    public AgentHealth AgentHealthCompo { get; private set; }

    public void SetDead()
    {
        isDead = true;
    }
    
    private void Awake()
    {
        _stateDictionary = new Dictionary<StateType, IState>();
        Transform stateTrm = transform.Find("States");

        AgentHealthCompo = GetComponent<AgentHealth>();

        foreach( StateType state in Enum.GetValues(typeof (StateType)) )
        {
            IState stateScript = stateTrm.GetComponent($"{state}State") as IState;
            if(stateScript == null)
            {
                Debug.LogError($"There is no script : {state}");
                return;
            }
            stateScript.SetUp(transform);
            _stateDictionary.Add(state, stateScript);
        }

        AgentMovementCompo = GetComponent<AgentMovement>();
        AgentMovementCompo.SetInit(this);

        DamageCasterCompo = transform.Find("DamageCaster").GetComponent<DamageCaster>();
        DamageCasterCompo.SetInit(this);
    }


    private void Start()
    {
        ChangeState(StateType.Normal);
    }

    public void ChangeState(StateType type)
    {
        _currentState?.OnExitState(); //현재 상태 나가고
        _currentState = _stateDictionary[type];
        _currentState?.OnEnterState(); //다음상태 시작
    }

    private void Update()
    {
        if (isDead)
            return;
        _currentState?.UpdateState();
    }
}
