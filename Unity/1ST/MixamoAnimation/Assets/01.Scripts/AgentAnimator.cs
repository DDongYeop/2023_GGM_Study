using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AgentAnimator : MonoBehaviour
{
    private readonly int _hashMoveX = Animator.StringToHash("move_x");
    private readonly int _hashMoveY = Animator.StringToHash("move_y");
    private readonly int _hashIsMoving = Animator.StringToHash("is_moving");

    private Animator _animator;

    private void Awake()
    {
        _animator = GetComponent<Animator>();
    }

    public void SetMoving(bool value)
    {
        _animator.SetBool(_hashIsMoving, value);
    }

    public void SetDirection(Vector2 dir)
    {
        _animator.SetFloat(_hashMoveX, dir.x);
        _animator.SetFloat(_hashMoveY, dir.y);
    }
}
