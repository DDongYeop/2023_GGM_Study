using UnityEngine;

public class DrawTrailFeedback : Feedback
{
    [SerializeField] private Transform _firePos;
    [SerializeField] private BulletTrail _trailPrefab; //�̰� ���߿� AssetReference �� ����ȴ�.
    [SerializeField] private PlayerAttack _playerAttack;
    [SerializeField] private float _trailTime = 0.03f;

    public override void CompletePrevFeedback()
    {
        //�����ϰ� ���ָ� �׸��̶� ���ø�Ʈ 
    }

    public override void CreateFeedback()
    {
        var trail = Instantiate(_trailPrefab, _firePos.position, Quaternion.identity);
        trail.DrawTrail(_firePos.position, _playerAttack.HitPoint, _trailTime);
    }
}
