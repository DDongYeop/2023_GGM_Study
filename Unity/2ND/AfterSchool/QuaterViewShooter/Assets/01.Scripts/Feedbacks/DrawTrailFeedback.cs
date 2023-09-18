using UnityEngine;

public class DrawTrailFeedback : Feedback
{
    [SerializeField] private Transform _firePos;
    [SerializeField] private BulletTrail _trailPrefab; //이건 나중에 AssetReference 로 변경된다.
    [SerializeField] private PlayerAttack _playerAttack;
    [SerializeField] private float _trailTime = 0.03f;

    public override void CompletePrevFeedback()
    {
        //생성하고 없애면 그만이라 컴플리트 
    }

    public override void CreateFeedback()
    {
        var trail = Instantiate(_trailPrefab, _firePos.position, Quaternion.identity);
        trail.DrawTrail(_firePos.position, _playerAttack.HitPoint, _trailTime);
    }
}
