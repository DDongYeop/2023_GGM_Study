using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackAIState : CommonAIState
{
    [SerializeField] private float _rotateSpeed = 720f;

    protected Vector3 _targetVector; //적을 바라보는 벡터
    
    
    public override void OnEnterState()
    {
        _enemyController.NavMovement.StopImmediately();
        _enemyController.AgentAnimator.OnAnimationEventTrigger += AttackCollisionHandle;
        _enemyController.AgentAnimator.OnAnimationEndTrigger += AttackAnimationEndHandle;
        _aiActionData.IsAttacking = false;
    }

    public override void OnExitState()
    {
        _enemyController.AgentAnimator.OnAnimationEventTrigger -= AttackCollisionHandle;
        _enemyController.AgentAnimator.OnAnimationEndTrigger -= AttackAnimationEndHandle;

        _enemyController.AgentAnimator.SetAttackState(false); //애니메이션 리셋
        _enemyController.AgentAnimator.SetAttackTrigger(false);
    }

    //공격 애니메이션 끝났을때 처리
    private void AttackCollisionHandle()
    {
        _enemyController.AgentAnimator.SetAttackState(false);
        _aiActionData.IsAttacking = false;
    }

    private void AttackAnimationEndHandle()
    {
        //아직 플레이어 채력 없어서 공격 안됨
    }

    public override void UpdateState()
    {
        base.UpdateState(); // 먼저 공격 가능한 거리인지 체그하고

        if (_aiActionData.IsAttacking == false)
        {
            SetTarget(); //타겟을 향하도록 벡터를 만들고
            Quaternion rot = Quaternion.LookRotation(_targetVector);
            transform.rotation = rot;

            _aiActionData.IsAttacking = true;
            _enemyController.AgentAnimator.SetAttackState(true);
            _enemyController.AgentAnimator.SetAttackTrigger(true); //공격모션 재생 
        }
    }

    private void SetTarget()
    {
        _targetVector = _enemyController.TargetTrm.position - transform.position;
        _targetVector.y = 0;
    }
}
