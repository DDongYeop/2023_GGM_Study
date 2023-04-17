using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu (menuName = "SO/EnemtData")]
public class EnemyDataSO : ScriptableObject
{
    public int MaxHP;
    public float MoveSpeed;
    public float RotateSpeed;
    public int AtkDamage;
    public float AtkCoolTime;
}
