using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySmashAttack : EnemyAttack
{
    [SerializeField]
    private Transform _atkPosTrm;

    [SerializeField]
    private float _atkRadius = 3f;
    [SerializeField]
    private int _damage = 10;

    [SerializeField]
    private LayerMask _whatIsEnemy;

    public override void Attack(int damage, Vector3 targetVector)
    {
        Collider[] cols = Physics.OverlapSphere(_atkPosTrm.position, _atkRadius, _whatIsEnemy);

        foreach(Collider c in cols)
        {
            if(c.TryGetComponent<IDamageable>(out IDamageable health))
            {
                Vector3 normal = _atkPosTrm.position - c.transform.position;
                normal.y = 0;
                health.OnDamage(_damage, c.transform.position, normal);
            }
        }
    }

    public override void CancelAttack()
    {
        //do nothing
    }

    public override void PreAttack()
    {
        //do nothing
    }
}
