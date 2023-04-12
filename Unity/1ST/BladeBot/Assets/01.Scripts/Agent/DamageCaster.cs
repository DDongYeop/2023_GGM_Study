using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DamageCaster : MonoBehaviour
{
    [SerializeField] [Range(0.5f, 4f)] private float _casterRadius = 1f;
    [SerializeField] private float _casterInterpolation = 0.5f; // 캐스트를 뒤쪽으로 뺴주는 정도
    [SerializeField] private LayerMask _targetLayer;

    public void CastDamge()
    {
        
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
