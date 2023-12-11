using DG.Tweening;
using UnityEngine;
using Random = UnityEngine.Random;

public class CloneSkillController : MonoBehaviour
{
    [SerializeField] private int _attackCategoryCount = 3;
    private SpriteRenderer _spriteRenderer;
    private Animator _animator;

    private readonly int _comCounterHash = Animator.StringToHash("ComboCounter");
    private int _facingDirection = 1;

    private CloneSkill _skill;

    private void Awake()
    {
        _spriteRenderer = GetComponent<SpriteRenderer>();
        _animator = GetComponent<Animator>();
    }

    public void SetUpClone(CloneSkill skill, Transform originTrm, Vector3 offset)
    {
        _animator.SetInteger(_comCounterHash, Random.Range(0, _attackCategoryCount));
        _skill = skill;
        transform.position = originTrm.position + offset; 
        FacingClosestTarget();
        
        Sequence seq = DOTween.Sequence();
        seq.AppendInterval(_skill.cloneDuration);
        seq.Append(_spriteRenderer.DOFade(0, 0.4f));
        seq.AppendCallback(() => Destroy(gameObject));
    }

    private void FacingClosestTarget()
    {
        Transform target = _skill.FindClosestEnemy(transform, _skill.findEnemyRadius);
        
        //이게 널이 아니면
        if (target != null)
        {
            //잘 체크하고
            if (transform.position.x > target.position.x)
            {
                //방향 회전
                _facingDirection = -1;
                transform.Rotate(0, 180, 0);
            }
        }
    }

    private void AnimationFinishTrigger()
    {
        
    }
}
