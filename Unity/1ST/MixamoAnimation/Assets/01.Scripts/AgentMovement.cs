using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class AgentMovement : MonoBehaviour
{
    [SerializeField] private float _moveSpeed = 8f, _gravity = -9.8f;

    private CharacterController _characterController;

    private Vector3 _movementVelocity;
    private float _verticalVelocity;
    private Vector3 _inputVelocity;

    private AgentAnimator _agentAnimator;

    private void Awake()
    {
        _characterController = GetComponent<CharacterController>();
        _agentAnimator = transform.Find("Visual").GetComponent<AgentAnimator>();
    }

    public void SetInputVelocity(Vector3 value)
    {
        _inputVelocity = value;
        _agentAnimator.SetDirection(new Vector2(value.x, value.z));
    }

    private void CalculatePlayerMovement()
    {
        _movementVelocity = _inputVelocity.normalized * (_moveSpeed * Time.fixedDeltaTime);
        _agentAnimator?.SetMoving(_movementVelocity.sqrMagnitude > 0);
    }

    private void FixedUpdate()
    {
        CalculatePlayerMovement();

        _verticalVelocity = _gravity * .3f * Time.fixedDeltaTime;

        Vector3 move = _movementVelocity + _verticalVelocity * Vector3.up;
        _characterController.Move(move);
    }
}
