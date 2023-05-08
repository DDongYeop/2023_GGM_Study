using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class EnemyController : PoolableMono
{
    [SerializeField] private EnemyDataSO _enemyData;
    public EnemyDataSO EnemyData => _enemyData;
    
    [SerializeField] private CommonAIState _currentState;

    private Transform _targetTrm;
    public Transform TargetTrm => _targetTrm;

    private NavAgentMovement _navMovement;
    public NavAgentMovement NavMovement => _navMovement;

    private AgentAnimator _agentAnimator;
    public AgentAnimator AgentAnimator => _agentAnimator;

    private EnemyVFXManager _vfxManager;
    public EnemyVFXManager VfxManager => _vfxManager;
    
    public EnemyHealth EnemyHealthCompo { get; private set; }

    public bool IsDead = false;
    
    public UnityEvent OnAfterDeadthTrigger = null;
    
    private CommonAIState _initState;

    protected virtual void Awake()
    {
        _vfxManager = GetComponent<EnemyVFXManager>();
        _navMovement = GetComponent<NavAgentMovement>();
        _agentAnimator = transform.Find("Visual").GetComponent<AgentAnimator>();
        EnemyHealthCompo = GetComponent<EnemyHealth>();
        EnemyHealthCompo.SetInit(this);
        
        List<CommonAIState> _states = new List<CommonAIState>();
        transform.Find("AI").GetComponentsInChildren<CommonAIState>(_states);
        
        _states.ForEach((s => s.SetUp(transform))); //여기서 셋업이 시작되는거 
        
        _initState = _currentState;
    }

    protected virtual void Start()
    {
        _targetTrm = GameManager.Instance.PlayerTrm;
        _navMovement.SetSpeed(_enemyData.MoveSpeed); //이속 설정
        EnemyHealthCompo.SetMaxHP(_enemyData.MaxHP); //체력 설정
    }

    public void ChangeState(CommonAIState state)
    {
        _currentState?.OnExitState();
        _currentState = state;
        _currentState?.OnEnterState();
    }

    protected virtual void Update()
    {
        if (IsDead)
            return;
        _currentState?.UpdateState();
    }

    public void SetDead()
    {
        IsDead = true;
        _navMovement.StopNavigation();
        _agentAnimator.StopAnimation(true); //애니메이션 정지
        _navMovement.KnockBack(() =>
        {
            _agentAnimator.StopAnimation(false); //애니메이션 재생 다시 시작
            _agentAnimator.SetDead(); //사망애니메이션 처리
            
            MonoFunction.Instance.AddCoroutine(() =>
            {
                OnAfterDeadthTrigger?.Invoke();
            }, 1.5f);
        });
    }

    public override void Init()
    {
        IsDead = false;
        EnemyHealthCompo.SetMaxHP(EnemyData.MaxHP);
        _navMovement.ResetNavAgent();
        ChangeState(_initState);
    }

    public void GotoPool()
    {
        PoolManager.Instance.Push(this);
    }
}
