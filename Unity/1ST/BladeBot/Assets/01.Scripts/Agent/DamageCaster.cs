using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DamageCaster : MonoBehaviour
{
    [SerializeField] [Range(0.5f, 4f)] private float _casterRadius = 1f;
    [SerializeField] private float _casterInterpolation = 0.5f; // 캐스트를 뒤쪽으로 뺴주는 정도
    [SerializeField] private LayerMask _targetLayer;

    private int _damage = 2;
    
    public void CastDamge()
    {
        Vector3 startPos = transform.position - transform.forward * _casterRadius;
        RaycastHit hit;
        bool isHit = Physics.SphereCast(startPos, _casterRadius, transform.forward, out hit,
            _casterRadius + _casterInterpolation, _targetLayer);

        if (isHit)
        {
            Debug.Log($"맞았습니다 : {hit.collider.name}");
            if (hit.collider.TryGetComponent<IDamageable>(out IDamageable health))
                health.OnDamage(2, hit.point, hit.normal);
        }
        else
            Debug.Log("안 맞았습니다");
    }
    
#if UNITY_EDITOR

    private void OnDrawGizmos()
    {
        if (UnityEditor.Selection.activeObject == gameObject)
        {
            Gizmos.color = Color.red;
            Gizmos.DrawWireSphere(transform.position, _casterRadius);
            Gizmos.color = Color.white;
        }
    }

#endif
}
