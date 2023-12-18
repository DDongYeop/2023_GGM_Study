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

        //���� �ٰŸ� ���� �ٶ󺸵��� �Լ��� �ϳ� ������
        FacingClosestTarget();

        //�׸��� ������ �����ǵ��� �����.
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
                _facingDirection = -1; //���߿� ���ݱ��� �ǰ��ϱ� ���ؼ�
                transform.Rotate(0, 180, 0);
            }
        }
        //�̰� ���� ���� �ƴϸ�
        // �� üũ�ؼ�
        // �˸��� �������� ȸ���ϰ� �ؾ��Ѵ�.
    }

    private void AnimationFinishTrigger()
    {

    }
}
