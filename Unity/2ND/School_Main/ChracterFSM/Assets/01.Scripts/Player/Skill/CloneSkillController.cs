using DG.Tweening;
using UnityEngine;

public class CloneSkillController : MonoBehaviour
{
    [SerializeField] private int _attackCategoryCount = 3;
    private SpriteRenderer _spriteRenderer;
    private Animator _animator;


    private readonly int _comboCounterHash = Animator.StringToHash("ComboCounter");
    private int _facingDirection = 1;

    private CloneSkill _skill;

    private void Awake()
    {
        _spriteRenderer = GetComponent<SpriteRenderer>();
        _animator = GetComponent<Animator>();
    }

    public void SetUpClone(CloneSkill skill, Transform originTrm, Vector3 offset)
    {
        _animator.SetInteger(_comboCounterHash, Random.Range(0, _attackCategoryCount));
        _skill = skill;
        transform.position = originTrm.position + offset;

        //가장 근거리 적을 바라보도록 함수를 하나 만들자
        FacingClosestTarget();

        //그리고 끝나면 삭제되도록 만든다.
        Sequence seq = DOTween.Sequence();
        seq.AppendInterval(_skill.cloneDuration);
        seq.Append(_spriteRenderer.DOFade(0, 0.4f));
        seq.AppendCallback(() =>
        {
            Destroy(gameObject);
        });
    }

    private void FacingClosestTarget()
    {
        Transform target = _skill.FindClosestEnemy(transform, _skill.findEnemyRadius);

        if(target != null)
        {
            if(transform.position.x > target.position.x)
            {
                _facingDirection = -1; //나중에 공격까지 되게하기 위해서
                transform.Rotate(0, 180, 0);
            }
        }
        //이게 만약 널이 아니면
        // 잘 체크해서
        // 알맞은 방향으로 회전하게 해야한다.
    }

    private void AnimationFinishTrigger()
    {

    }
}
