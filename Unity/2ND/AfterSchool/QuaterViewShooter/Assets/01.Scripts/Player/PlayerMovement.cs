using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.NetworkInformation;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerMovement : MonoBehaviour
{
    [Header("참조값들")]
    [SerializeField] private InputReader _inputReader;
    [SerializeField] private CharacterController _characterController;
    [SerializeField] private PlayerAnimator _playerAnimator;
    
    [Header("설정 값들")]
    [SerializeField] private float _moveSpeed = 5f;
    [SerializeField] private float _gravity = -9.8f;
    [SerializeField] private float _gravityMultiplier = 1f;

    public bool IsGround
    {
        get => _characterController.isGrounded;
    }

    private Vector2 _inputDirection;
    private Vector3 _moveVelocity;
    public Vector3 MoveVelocity => _moveVelocity;
    private float _verticalVelocity;
    private Quaternion _rotate45;

    private void Awake()
    {
        _rotate45 = Quaternion.AngleAxis(45f, Vector3.up);
        _inputReader.MovementEvent += SetMovement;
    }

    private void OnDestroy()
    {
        _inputReader.MovementEvent -= SetMovement;
    }

    private void SetMovement(Vector2 value)
    {
        _inputDirection = value;
    }
    
    private void CalculateMovement()
    {
        Vector3 move = _rotate45 * new Vector3(_inputDirection.x, 0, _inputDirection.y);
        _moveVelocity = move * (_moveSpeed * Time.fixedDeltaTime);
    }

    private void ApplyGravity()
    {
        if (IsGround && _verticalVelocity < 0)
        {
            _verticalVelocity = -1f;
        }
        else
        {
            _verticalVelocity = _gravity * _gravityMultiplier * Time.fixedDeltaTime;
        }
        _moveVelocity.y = _verticalVelocity;
    }

    private void Move()
    {
        _characterController.Move(_moveVelocity);
        _playerAnimator.SetMove(_inputDirection.sqrMagnitude > 0.1f);
    }

    private void FixedUpdate()
    {
        CalculateMovement();
        ApplyGravity();
        Move();
    }
}
