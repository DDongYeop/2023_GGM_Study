using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyAttack : MonoBehaviour
{
    [SerializeField] private Bullet _prefab;
    [SerializeField] private Transform _firePos;
    [SerializeField] private float _firePower;
    
    public void Attack()
    {
        var bullet = Instantiate(_prefab, _firePos.position, Quaternion.identity);
        bullet.Fire(_firePos.forward * _firePower);
    }
}
