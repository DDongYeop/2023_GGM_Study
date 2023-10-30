using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AddressableAssets;

public class DrawTrailFeedback : Feedback
{
    [SerializeField] private Transform _firePos;
    [SerializeField] private AssetReference _prefabRef;
    [SerializeField] private UziGun _playerGun;
    [SerializeField] private float _trailTime = 0.01f;
    
    public override void CompletePrevFeedback()
    {
        
    }
    
    public override void CreateFeedback()
    {
        var trail = PoolManager.Instance.Pop(_prefabRef) as BulletTrail;
        trail.DrawTrail(_firePos.position, _playerGun.HitPoint, _trailTime);
    }
}
