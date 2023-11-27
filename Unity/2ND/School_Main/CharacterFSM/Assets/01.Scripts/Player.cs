using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//상태를 기반으로 플레이어를 만들꺼니깐 PlayerState라는 클래스 하나 만들고 Move와 Idle을 만든다 
public class Player : MonoBehaviour
{
    [Header("Setting Values")] 
    public float moveSpeed = 12;
    public float jumpForce = 12;
    public float dashDuration = .2f;
    public float dashSpeed = 40f;

    [Header("Collision Info")] 
    [SerializeField] protected Transform _groundChecker;
    [SerializeField] protected float _groundCheckDistance;
    [SerializeField] protected LayerMask _whatIsGround;
    [SerializeField] protected Transform _wallChecker;
    [SerializeField] protected float _wallCheckDistance;
    
    public PlayerStateMachine StateMachine { get; private set; }

    [SerializeField] private InputReader _inputReader;
    public InputReader PlayerInput => _inputReader;
    
    #region 컴포넌트 영역

    public Animator AnimatorCompo { get; private set; }
    public Rigidbody2D RigidbodyCompo { get; private set; }
    public CapsuleCollider2D ColliderCompo { get; private set; }

    #endregion

    public int FacingDirection { get; private set; } = 1; //오: 1, 왼: -1
    protected bool _facingRight = true;

    public virtual void Awake()
    {
        Transform visualTrm = transform.Find("Visual");
        AnimatorCompo = visualTrm.GetComponent<Animator>();
        RigidbodyCompo = GetComponent<Rigidbody2D>();
        ColliderCompo = GetComponent<CapsuleCollider2D>();

        StateMachine = new PlayerStateMachine();

        foreach (PlayerStateEnum state in Enum.GetValues(typeof(PlayerStateEnum)))
        {
            string typeName = state.ToString(); //Idle, Move
            Type t = Type.GetType($"Player{typeName}State"); //PlayerIdleState

            PlayerState newState = Activator.CreateInstance(t, this, StateMachine, typeName) as PlayerState;
            StateMachine.AddState(state, newState);
        }
    }

    private void OnEnable()
    {
        PlayerInput.DashEvent += HandleDashInput;
    }

    private void OnDisable()
    {
        PlayerInput.DashEvent -= HandleDashInput;
    }

    #region 키입력 핸들러
    
    private void HandleDashInput()
    {
        //스킬싯템을 구현시에 쿨타임 채크해서 해당 스킬 사용가능할때 사용하도록 
        StateMachine.ChangeState(PlayerStateEnum.Dash);
    }

    #endregion

    private void Start()
    {
        StateMachine.Initialize(PlayerStateEnum.Idle, this);
    }

    protected void Update()
    {
        StateMachine.CurrentState.UpdateState();
    }

    #region 속도 제어

    public void SetVelocity(float x, float y, bool doNotFlip = false)
    {
        //넉백상태일 경우는 안해주지만
        RigidbodyCompo.velocity = new Vector2(x, y);
        if (!doNotFlip)
        {
            FlipController(x);
        }
    }

    public void StopImmediately(bool withYAxis)
    {
        if (withYAxis)
            RigidbodyCompo.velocity = Vector2.zero;
        else
            RigidbodyCompo.velocity = new Vector2(0, RigidbodyCompo.velocity.y);
    }

    #endregion
    
    #region 플립 제어

    public void FlipController(float x)
    {
        bool goToRight = x > 0 && !_facingRight;
        bool goToLeft = x < 0 && _facingRight;
        if (goToRight || goToLeft)
            Flip();
    }

    public void Flip()
    {
        FacingDirection = FacingDirection * -1; //반전
        _facingRight = !_facingRight;
        transform.Rotate(0, 180, 0);
    }
    
    #endregion

    #region 충돌 체크 부분

    public virtual bool IsGroundDetected() => Physics2D.Raycast(_groundChecker.position, Vector2.down, _groundCheckDistance, _whatIsGround);
    
    public virtual bool IsWallDetected() => Physics2D.Raycast(_wallChecker.position, Vector2.right * FacingDirection, _wallCheckDistance, _whatIsGround);

    #endregion
    
#if UNITY_EDITOR
    protected virtual void OnDrawGizmos()
    {
        Gizmos.color = Color.green;
        if (_groundChecker != null)
            Gizmos.DrawLine(_groundChecker.position, 
                _groundChecker.position + new Vector3(0, -_groundCheckDistance, 0));
        if (_wallChecker != null)
            Gizmos.DrawLine(_wallChecker.position, 
                _wallChecker.position + new Vector3(_wallCheckDistance, 0, 0));
        Gizmos.color = Color.white;
    }
#endif
}
