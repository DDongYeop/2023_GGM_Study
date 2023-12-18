using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public delegate void CooldownNotifier(float current, float total);

public abstract class Skill : MonoBehaviour
{
    public bool skillEnabled; //이 스킬이 활성화되었는가?

    [SerializeField] protected LayerMask _whatIsEnemy;
    [SerializeField] protected float _cooldown;
    protected float _cooldownTimer;
    protected Player _player;

    [SerializeField] protected PlayerSkill _skillType;

    public event CooldownNotifier OnCooldown; //쿨타임이 돌아갈 때 발행되는 메시지

    protected virtual void Start()
    {
        _player = GameManager.Instance.Player;
    }

    protected virtual void Update()
    {
        if(_cooldownTimer > 0)
        {
            _cooldownTimer -= Time.deltaTime;
            if(_cooldownTimer <= 0)
            {
                _cooldownTimer = 0;
            }

            OnCooldown?.Invoke(current: _cooldownTimer, total: _cooldown);
        }
    }

    public virtual bool AttemptUseSkill()
    {
        if(_cooldownTimer <= 0 && skillEnabled)
        {
            _cooldownTimer = _cooldown;
            UseSkill();
            return true;
        }

        Debug.Log("Skill cooldown or not unlocked!");
        return false;
    }

    public virtual void UseSkill()
    {
        //나 이 스킬 썼어. 피드백해줘
        SkillManager.Instance.UseSkillFeedback(_skillType);
    }

    public virtual Transform FindClosestEnemy(Transform checkTrm, float radius)
    {
        Transform target = null;

        Collider2D[] colliders = Physics2D.OverlapCircleAll(
                            checkTrm.position, radius, _whatIsEnemy);

        float closestDistance = Mathf.Infinity;

        foreach(Collider2D collider in colliders)
        {
            float distance = Vector2.Distance(checkTrm.position, collider.transform.position);
            if(distance < closestDistance)
            {
                closestDistance = distance;
                target = collider.transform;
            }
        }
        return target;
    }
}
