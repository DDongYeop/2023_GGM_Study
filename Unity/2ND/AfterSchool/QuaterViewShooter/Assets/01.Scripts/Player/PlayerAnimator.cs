using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimator : MonoBehaviour
{
    [Header("참조 변수")]
    [SerializeField] private Animator _animator;
    [SerializeField] private Animator _rigAnimator;

    private readonly int _moveXHash = Animator.StringToHash("move_x");
    private readonly int _moveYHash = Animator.StringToHash("move_y");
    private readonly int _isMoveHash = Animator.StringToHash("is_move");
    private readonly int _isReloadHash = Animator.StringToHash("is_reload");

    private readonly int _isArmedHash = Animator.StringToHash("is_armed");

    private void Awake()
    { 
        _rigAnimator.enabled = true; //명시적으로 동작하게 
    }

    public void SetMove(bool value)
    {
        _animator.SetBool(_isMoveHash, value);
    }
    
    public void SetAnimationDirection(Vector2 dir)
    {
        _animator.SetFloat(_moveXHash, dir.x);
        _animator.SetFloat(_moveYHash, dir.y);
    }

    public void SetArmed(bool value)
    {
        _rigAnimator.SetBool(_isArmedHash, value);
    }
    
    public void SetReload(bool value)
    {
        _animator.SetBool(_isReloadHash, value);
        _rigAnimator.SetBool(_isReloadHash, value);
        //나중에 리깅부분 추가 
    }
}
