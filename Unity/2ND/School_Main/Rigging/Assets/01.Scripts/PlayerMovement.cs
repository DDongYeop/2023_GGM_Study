using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private InputReader _inputReader;

    [SerializeField] private float _moveSpeed = 5f;
    [SerializeField] private float _gravity = -9.8f;
    [SerializeField] private float _jumpPower = 3f;
    [SerializeField] private float _desiredRotationSpeed = 0.3f;
    [SerializeField] private float _allowPlayerRotation = 0.1f;
    [SerializeField] private Transform _targetTrm;

    private CharacterController _characterController;
    private float _verticalVelocity;
    private Vector3 _movementVelocity;
    private Vector2 _inputDirection;
    private Vector3 _desireMovement;
    public bool blockRotationPlayer = false; //사격중일때는 플레이어 회전하지 안흔ㄴ다.
    private PlayerAnimator _animator;

    private Camera _mainCam;

    private void Awake()
    {
        _mainCam = Camera.main;
        _characterController = GetComponent<CharacterController>();
        _animator = GetComponent<PlayerAnimator>();
        _inputReader.MovementEvent += SetMovement;
        _inputReader.JumpEvent += Jump;
    }

    private void OnDestroy()
    {
        _inputReader.MovementEvent -= SetMovement;
        _inputReader.JumpEvent -= Jump;
    }

    private void Jump()
    {
        if (!_characterController.isGrounded)
            return;
        _verticalVelocity += _jumpPower;
    }
    //키보드 입력을 받아서 inputDirection에 넣었다.
    private void SetMovement(Vector2 value)
    {
        _inputDirection = value;
    }

    private void CalculatePlayerMovement()
    {
        var forward = _mainCam.transform.forward;
        var right = _mainCam.transform.right;
        forward.y = 0;
        right.y = 0;

        _desireMovement = forward.normalized * _inputDirection.y + right.normalized * _inputDirection.x;

        if(blockRotationPlayer == false && _inputDirection.sqrMagnitude > _allowPlayerRotation)
        {
            //발사중이 아니라면 천천히 진행방향으로 회전한다.
            _targetTrm.rotation = Quaternion.Slerp(_targetTrm.rotation,
                                    Quaternion.LookRotation(_desireMovement), 
                                    _desiredRotationSpeed);
        }

        _movementVelocity = _desireMovement * (_moveSpeed * Time.fixedDeltaTime);
    }

    public void RotateToCamera(Transform target) //카메라를 향해서 돌아야해
    {
        var forward = _mainCam.transform.forward;

        var rot = _targetTrm.rotation;
        _desireMovement = forward;
        Quaternion lookRot = Quaternion.LookRotation(_desireMovement);
        Quaternion lookRotOnlyY = Quaternion.Euler(rot.eulerAngles.x, lookRot.eulerAngles.y, rot.eulerAngles.z);

        target.rotation = Quaternion.Slerp(rot, lookRotOnlyY, _desiredRotationSpeed);
        //이거 설명은 내일 이어서 한다.
    }

    private void ApplyGravity()
    {
        if(_characterController.isGrounded && _verticalVelocity < 0)
        {
            _verticalVelocity = -1f;
        }
        else
        {
            _verticalVelocity += _gravity * Time.fixedDeltaTime;
        }

        _movementVelocity.y = _verticalVelocity;
    }

    private void Move()
    {
        _characterController.Move(_movementVelocity);
    }

    public void ApplyAnimation()
    {
        _animator.SetShooting(blockRotationPlayer);
        float speed = _inputDirection.sqrMagnitude;
        _animator.SetBlendValue(speed);
        _animator.SetXY(_inputDirection);
    }
    
    private void FixedUpdate()
    {
        ApplyAnimation();
        CalculatePlayerMovement();
        ApplyGravity();
        Move();
    }
}