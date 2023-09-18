using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimator : MonoBehaviour
{
    [Header("참조 변수")]
    [SerializeField] private Animator _animator;

    private readonly int _moveXHash = Animator.StringToHash("move_x");
    private readonly int _moveYHash = Animator.StringToHash("move_y");
    private readonly int _isMoveHash = Animator.StringToHash("is_move");

    public void SetMove(bool value)
    {
        _animator.SetBool(_isMoveHash, value);
    }
    
    public void SetAnimationDirection(Vector2 dir)
    {
        _animator.SetFloat(_moveXHash, dir.x);
        _animator.SetFloat(_moveYHash, dir.y);
    }
}
