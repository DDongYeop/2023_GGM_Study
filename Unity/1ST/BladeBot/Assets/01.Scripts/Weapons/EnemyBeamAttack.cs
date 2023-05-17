using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBeamAttack : EnemyAttack
{
    [SerializeField]
    private Beam _beamPrefab;
    [SerializeField]
    private Transform _atkPosTrm;

    private Beam _currentBeam;

    public override void Attack(int damage, Vector3 targetVector)
    {
        _currentBeam.FireBeam(damage, targetVector);
        _currentBeam = null; //����� �ڵ����� Ǯ�� �����ϱ� �̰� null�� �����.
    }

    public override void CancelAttack()
    {
        if (_currentBeam != null)
            _currentBeam?.StopBeam();
        _currentBeam = null;
    }

    public override void PreAttack()
    {
        _currentBeam = PoolManager.Instance.Pop(_beamPrefab.gameObject.name) as Beam;
        _currentBeam.transform.position = _atkPosTrm.position;
        _currentBeam.PreCharging(); //����í¡
    }

    private void OnDisable()
    {
        CancelAttack();
    }
}
