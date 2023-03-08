using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AgentMovement : MonoBehaviour
{
    [SerializeField] private float _moveSpeed = 8f, _gravity = -9.8f;

    private CharacterController _characterController;

    private Vector3 _movementVelocity;
    
    public Vector3 MovementVelocity => _movementVelocity; //평면속도
    private float _verticalVelocity; //중력속도

    private void Awake()
    {
        _characterController = GetComponent<CharacterController>();
    }

    private void Update()
    {
        UpdateMovement();
    }

    private void UpdateMovement()
    {
        float horizontal = Input.GetAxisRaw("Horizontal");
        float vertical = Input.GetAxisRaw("Vertical");

        _movementVelocity = new Vector3(horizontal, 0, vertical);
    }

    private void CalculatePlayerMovement()
    {
        //여기가 핵심이다 
        _movementVelocity.Normalize(); //스택메모리와 힙메모리의 차이를 알아둬야한다. 

        _movementVelocity *= _moveSpeed * Time.fixedDeltaTime;
        _movementVelocity = Quaternion.Euler(0, -45f, 0) * _movementVelocity;
        if (_movementVelocity.sqrMagnitude > 0)
        {
            transform.rotation = Quaternion.LookRotation(_movementVelocity);
            //가야할 방향 보게 하기
        }
    }

    private void StopImmediately()
    {
        _movementVelocity = Vector3.zero;
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
    }
}
