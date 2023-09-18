using UnityEngine;

public interface IDamageable
{
    public void OnDamage(int damage, Vector3 point, Vector3 normal);
}
