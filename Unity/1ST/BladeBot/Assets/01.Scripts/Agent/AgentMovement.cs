using UnityEngine;

public class AgentMovement : MonoBehaviour
{
    [SerializeField] private float _moveSpeed = 8f, _gravity = -9.8f;

    private CharacterController _characterController;

    private Vector3 _movementVelocity;
    public Vector3 MovementVelocity => _movementVelocity; //평면속도
    private float _verticalVelocity; //중력속도

    private AgentAnimator _animator;
    
    private void Awake()
    {
        _characterController = GetComponent<CharacterController>();
        _animator = transform.Find("Visual").GetComponent<AgentAnimator>();
    }

    public void SetMovementVelocity(Vector3 value)
    {
        _movementVelocity = value;
    }

    private void CalculatePlayerMovement()
    {
        //여기가 핵심이다 
        _animator?.SetSpeed(_movementVelocity.sqrMagnitude); //추가됨
        
        _movementVelocity.Normalize(); //스택메모리와 힙메모리의 차이를 알아둬야한다. 

        _movementVelocity *= _moveSpeed * Time.fixedDeltaTime;
        _movementVelocity = Quaternion.Euler(0, -45f, 0) * _movementVelocity;
        
        if (_movementVelocity.sqrMagnitude > 0)
        {
            transform.rotation = Quaternion.LookRotation(_movementVelocity);
            //가야할 방향 보게 하기
        }
    }

    public void StopImmediately()
    {
        _movementVelocity = Vector3.zero;
        _animator?.SetSpeed(_movementVelocity.sqrMagnitude); //추가됨
    }

    private void FixedUpdate()
    {
        CalculatePlayerMovement(); //플레이어 이속 계산 

        if (_characterController.isGrounded == false) // 땅에 있을때
        {
            _verticalVelocity = _gravity * Time.fixedDeltaTime;
        }
        else //중력에 가중치 넣어서 
        {
            // 0.3f는 하드코딩 값
            _verticalVelocity = _gravity * 0.3f * Time.fixedDeltaTime;
        }

        Vector3 move = _movementVelocity + _verticalVelocity * Vector3.up;
        _characterController.Move(move);
        
        _animator.SetAirbone(_characterController.isGrounded == false); //추가됨
    }
}
