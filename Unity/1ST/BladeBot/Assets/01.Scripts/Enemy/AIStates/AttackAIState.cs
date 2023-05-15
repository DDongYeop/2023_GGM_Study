using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackAIState : CommonAIState
{
    [SerializeField] private float _rotateSpeed = 720f;

    protected Vector3 _targetVector; //적을 바라보는 벡터

    private bool isActive;

    private int _atkDamage = 1;
    private float _atkMotionDelay = 0.2f;

    [SerializeField] private float _atkCoolTime = 1f;
    private float _lastAtkTime;
    
    public override void SetUp(Transform agentRoot)
    {
        base.SetUp(agentRoot);
        _rotateSpeed = _enemyController.EnemyData.RotateSpeed;
        _atkDamage = _enemyController.EnemyData.AtkDamage;
        _atkMotionDelay = _enemyController.EnemyData.AtkCoolTime;
    }

    public override void OnEnterState()
    {
        _enemyController.NavMovement.StopImmediately();
        _enemyController.AgentAnimator.OnAnimationEventTrigger += AttackCollisionHandle;
        _enemyController.AgentAnimator.OnAnimationEndTrigger += AttackAnimationEndHandle;
        _enemyController.AgentAnimator.OnPreAnimationEventTrigger += PreAttackHandle;
        _aiActionData.IsAttacking = false;

        isActive = true;
    }

    public override void OnExitState()
    {
        _enemyController.AgentAnimator.OnAnimationEventTrigger -= AttackCollisionHandle;
        _enemyController.AgentAnimator.OnAnimationEndTrigger -= AttackAnimationEndHandle;
        _enemyController.AgentAnimator.OnPreAnimationEventTrigger -= PreAttackHandle;

        _enemyController.AgentAnimator.SetAttackState(false); //애니메이션 리셋
        _enemyController.AgentAnimator.SetAttackTrigger(false);

        _enemyController.CancelAttack(); //나갈떄 취소
        
        isActive = false;
    }

    private void PreAttackHandle()
    {
        _enemyController.PreAttack();
    }

    //공격 애니메이션 끝났을때 처리
    private void AttackCollisionHandle()
    {
        //_aiActionData.IsAttacking = false;
        _enemyController.AgentAnimator.SetAttackState(false);
        
        _lastAtkTime = Time.time;

        MonoFunction.Instance.AddCoroutine(() => 
        {
            _aiActionData.IsAttacking = false;
        }, _atkMotionDelay);
    }
    
    private void AttackAnimationEndHandle()
    {
        _enemyController.AttackWeapon(_atkDamage, _targetVector);
    }

    public override bool UpdateState()
    {
        if (base.UpdateState()) // 먼저 공격 가능한 거리인지 체그하고
            return true;
        
        if (_aiActionData.IsAttacking == false && isActive)
        {
            SetTarget(); //타겟을 향하도록 벡터를 만들고

            Vector3 currentFrontVector = transform.forward; //캐릭터 전방으로
            float angle = Vector3.Angle(currentFrontVector, _targetVector);

            if (angle >= 10f)
            {
                Vector3 result = Vector3.Cross(currentFrontVector, _targetVector);

                float sign = result.y > 0 ? 1 : -1;
                _enemyController.transform.rotation = Quaternion.Euler(0, sign *_rotateSpeed * Time.deltaTime, 0) * _enemyController.transform.rotation;
            }
            else if (_lastAtkTime + _atkCoolTime < Time.time)
            {
                _aiActionData.IsAttacking = true;
                _enemyController.AgentAnimator.SetAttackState(true);
                _enemyController.AgentAnimator.SetAttackTrigger(true); //공격모션 재생 
            }
        }

        return false;
    }

    private void SetTarget()
    {
        _targetVector = _enemyController.TargetTrm.position - transform.position;
        _targetVector.y = 0;
    }
}
