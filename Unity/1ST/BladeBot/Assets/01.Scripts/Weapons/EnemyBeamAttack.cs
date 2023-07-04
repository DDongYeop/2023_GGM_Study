using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBeamAttack : EnemyAttack
{
    [SerializeField]
    private LayerMask _whatIsEnemy;

    [SerializeField]
    private Beam _beamPrefab;
    [SerializeField]
    private Transform _atkPosTrm;

    private Beam _currentBeam;

    public override void Attack(int damage, Vector3 targetVector)
    {
        _currentBeam.FireBeam(damage, targetVector);
        _currentBeam = null; //쏘고나면 자동으로 풀로 들어갈꺼니까 이건 null로 만든다.
    }

    public override void CancelAttack()
    {
        if(_currentBeam != null)
            _currentBeam.StopBeam();
        _currentBeam = null;
    }

    public override void PreAttack()
    {
        _currentBeam = PoolManager.Instance.Pop(_beamPrefab.gameObject.name) as Beam;
        _currentBeam.transform.position = _atkPosTrm.position;
        _currentBeam.SetUpLayerMask(_whatIsEnemy);
        _currentBeam.PreCharging(); //프리챠징
    }

    private void OnDisable()
    {
        CancelAttack();
    }
}
