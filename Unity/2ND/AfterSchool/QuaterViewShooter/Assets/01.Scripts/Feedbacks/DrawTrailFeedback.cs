using System.Collections;
using System.Collections.Generic;
using Unity.Mathematics;
using UnityEngine;

public class DrawTrailFeedback : Feedback
{
    [SerializeField] private Transform _firePos;
    [SerializeField] private BulletTrail _trailPrefab;
    [SerializeField] private PlayerAttack _playerAttack;
    [SerializeField] private float _trailTime = 0.03f;
    
    public override void CreateFeedback()
    {
        //생성하고 없애기
    }

    public override void CompletePreFeedback()
    {
        var trail = Instantiate(_trailPrefab, _firePos.position, quaternion.identity);
        trail.DrawTrail(_firePos.position, _playerAttack.HitPoint, _trailTime);
    }
}
