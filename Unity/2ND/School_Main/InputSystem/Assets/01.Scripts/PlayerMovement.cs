using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private float _moveSpeed = 5f;
    [SerializeField] private float _gravity = -9.8f;
    [SerializeField] private float _jumpPower = 4f;

    private PlayerInput _playerInput;
    [SerializeField] private Transform _rootTrm; //방향측정을 위한 루트

    private float _gravityMultiplier = 1f;

    private CharacterController _characterController;
    public bool IsGround
    {
        get => _characterController.isGrounded;
    }

    private Vector2 _inputDirection;
    private Vector3 _movementVelocity;
    public Vector3 MovementVelocity => _movementVelocity;
    private float _verticalVelocity;

    //키보드로 움직이는 상태인가?
    private bool _activeMove = true;
    public bool ActiveMove
    {
        get => _activeMove;
        set => _activeMove = value;
    }

    private void Awake()
    {
        _characterController = GetComponent<CharacterController>();
        _playerInput = GetComponent<PlayerInput>();
        _playerInput.OnMovement += SetMovement;
        _playerInput.OnJump += Jump;
    }

    private void Jump()
    {
        if (!IsGround) return;
        _verticalVelocity += _jumpPower;
    }

    //요것은 PlayInput에서 구독처리 될것임.
    public void SetMovement(Vector2 value)
    {
        _inputDirection = value;
    }

    private void CalculatePlayerMovement()
    {
        _movementVelocity = (_rootTrm.forward * _inputDirection.y + _rootTrm.right * _inputDirection.x) * (_moveSpeed * Time.fixedDeltaTime);
    }

    //즉시 정지
    public void StopImmediately()
    {
        _movementVelocity = Vector3.zero;
    }

    //만약 다른 스크립트에서 이동을 건드리려 한다면 사용
    public void SetMovement(Vector3 value)
    {
        _movementVelocity = new Vector3(value.x, 0, value.z);
        _verticalVelocity = value.y;
    }

    private void ApplyGravity()
    {
        if (IsGround && _verticalVelocity < 0)  //땅에 착지 상태
        {
            _verticalVelocity = -1f;
        }
        else
        {
            _verticalVelocity += _gravity * _gravityMultiplier * Time.fixedDeltaTime;
        }

        _movementVelocity.y = _verticalVelocity;
    }

    private void Move()
    {
        _characterController.Move(_movementVelocity);
    }

    private void FixedUpdate()
    {
        //키보드로 움직일때만 이렇게 움직이고
        if (_activeMove)
        {
            CalculatePlayerMovement();
        }
        ApplyGravity(); //중력 적용
        Move();
    }

}
