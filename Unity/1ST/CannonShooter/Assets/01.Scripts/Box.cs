using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Box : MonoBehaviour
{
    [SerializeField]
    private BrokenEffect _effectPrefab;

    public void PlayExplosion(Vector2 direction)
    {
        BrokenEffect effect = Instantiate(_effectPrefab, transform.position, Quaternion.identity);
        effect.PlayEffect(direction);

        Destroy(gameObject);
    }
}
