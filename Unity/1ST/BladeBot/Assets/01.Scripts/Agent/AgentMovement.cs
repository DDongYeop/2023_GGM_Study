using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AgentMovement : MonoBehaviour
{
    public bool IsActiveMove = true; //키보드로 이동하냐? 아니냐

    [SerializeField]
    private float _gravity = -9.8f;

    private CharacterController _characterController;

    private Vector3 _movementVelocity;
    public Vector3 MovementVelocity => _movementVelocity; //평면속도
    private float _verticalVelocity; //중력속도

    private AgentAnimator _animator;

    private Vector3 _inputVelocity;
    private AgentController _controller;

    private void Awake()
    {
        _characterController = GetComponent<CharacterController>();
        _animator = transform.Find("Visual").GetComponent<AgentAnimator>();
    }

    public void SetInit(AgentController controller)
    {
        _controller = controller;
    }

    public void SetMovementVelocity(Vector3 value)
    {
        _inputVelocity = value;
        _movementVelocity = value;
    }

    private void CalculatePlayerMovement()
    {
        //여기가 핵심
        _animator?.SetSpeed(_inputVelocity.sqrMagnitude); //추가됨.

        _inputVelocity.Normalize();

        float moveSpeed = _controller.CharData.MoveSpeed;
        _movementVelocity = _inputVelocity * (moveSpeed * Time.fixedDeltaTime);
        _movementVelocity = Quaternion.Euler(0, -45f, 0) * _movementVelocity;

        if(_movementVelocity.sqrMagnitude > 0)
        {
            transform.rotation = Quaternion.LookRotation(_movementVelocity);
            //가야할 방향 보게 하기
        }
    }

    public void StopImmediately()
    {
        _movementVelocity = Vector3.zero;
        _animator?.SetSpeed(_movementVelocity.sqrMagnitude); //추가됨.
    }

    public void SetRotation(Vector3 targetPos)  //지점을 바라보는 코드
    {
        Vector3 dir = targetPos - transform.position;
        dir.y = 0;
        transform.rotation = Quaternion.LookRotation(dir);
    }

    private void FixedUpdate()
    {
        if(IsActiveMove)
            CalculatePlayerMovement(); //플레이어 이속 계산 (키보드 입력시에만 45도계산)

        if(_characterController.isGrounded == false)
        {
            _verticalVelocity = _gravity * Time.fixedDeltaTime;
        }
        else
        {
            //0.3은 하드코딩된 값
            _verticalVelocity = _gravity * 0.3f * Time.fixedDeltaTime;
        }

        Vector3 move = _movementVelocity + _verticalVelocity * Vector3.up;
        _characterController.Move(move);

        _animator?.SetAirbone(_characterController.isGrounded == false);
    }
}
