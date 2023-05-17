using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class EnemyController : PoolableMono
{
    [SerializeField]
    private EnemyDataSO _enemyData;
    public EnemyDataSO EnemyData => _enemyData;

    [SerializeField]
    private CommonAIState _currentState;
    public CommonAIState CurrentState => _currentState;

    private Transform _targetTrm;
    public Transform TargetTrm => _targetTrm;

    private NavAgentMovement _navMovement;
    public NavAgentMovement NavMovement => _navMovement;

    private AgentAnimator _agentAnimator;
    public AgentAnimator AgentAnimator => _agentAnimator;

    private EnemyVFXManager _vfxManager;
    public EnemyVFXManager VFXManager => _vfxManager;

    public EnemyHealth EnemyHealthCompo { get; private set; }

    public bool IsDead = false;

    private CommonAIState _initState;

    private List<AITransition> _anyTransitions = new List<AITransition>();
    public List<AITransition> AnyTransitions => _anyTransitions;

    private EnemyAttack _enemyAttack;

    protected virtual void Awake()
    {
        _vfxManager = GetComponent<EnemyVFXManager>();
        _navMovement = GetComponent<NavAgentMovement>();
        _agentAnimator = transform.Find("Visual").GetComponent<AgentAnimator>();
        EnemyHealthCompo = GetComponent<EnemyHealth>();
        EnemyHealthCompo.SetInit(this);


        List<CommonAIState> _states = new List<CommonAIState>();
        transform.Find("AI").GetComponentsInChildren<CommonAIState>(_states);

        _states.ForEach(s => s.SetUp(transform)); //여기서 셋업이 시작되는 거

        Transform anyTranTrm = transform.Find("AI/AnyTransitions");
        if(anyTranTrm != null)
        {
            anyTranTrm.GetComponentsInChildren<AITransition>(_anyTransitions);
            _anyTransitions.ForEach(t => t.SetUp(transform));
        }

        _enemyAttack = GetComponent<EnemyAttack>(); //공격 가져오기

        _initState = _currentState;
    }

    protected virtual void Start()
    {
        _targetTrm = GameManager.Instance.PlayerTrm;
        _navMovement.SetSpeed(_enemyData.MoveSpeed); //이동속도 설정
        EnemyHealthCompo.SetMaxHP(_enemyData.MaxHP); //체력설정
    }

    public void ChangeState(CommonAIState state)
    {
        _currentState?.OnExitState();
        _currentState = state;
        _currentState?.OnEnterState();
    }

    protected virtual void Update()
    {
        if (IsDead) return;
        _currentState?.UpdateState();
    }

    public UnityEvent OnAfterDeathTrigger = null; 
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
                OnAfterDeathTrigger?.Invoke();
            }, 1.5f); //1.5초후에 프드백 실행
        });
    }

    public override void Init()
    {
        IsDead = false;  //이거 추가 
        EnemyHealthCompo.SetMaxHP(EnemyData.MaxHP);
        _navMovement.ResetNavAgent();
        ChangeState(_initState);
    }

    public void GotoPool()
    {
        PoolManager.Instance.Push(this);
    }


    #region 공격관련 매서드
    public void AttackWeapon(int damage, Vector3 targetDir)
    {
        _enemyAttack.Attack(damage, targetDir);
    }

    public void PreAttack()
    {
        _enemyAttack.PreAttack();
    }

    public void CancelAttack()
    {
        _enemyAttack.CancelAttack();
    }
    #endregion

}
