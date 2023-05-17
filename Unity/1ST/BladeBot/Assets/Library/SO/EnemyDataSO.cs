using UnityEngine;

[CreateAssetMenu (menuName = "SO/EnemyData")]
public class EnemyDataSO : ScriptableObject
{
    public int MaxHP;
    public float MoveSpeed;
    public float RotateSpeed;
    public int AtkDamage;
    public float AtkCoolTime;
}
