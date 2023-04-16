using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InnerDistanceDecisions : AIDecision
{
    [Range(0.1f, 30f)] [SerializeField] private float _distance = 5f;
    
    public override bool MakeADecision()
    {
        float calc = Vector2.Distance(_brain.PlayerTrm.position, transform.position);

        if (calc < _distance)
        {
            //라스트 포지션 갱신
            _brain.StateInfoCompo.LastEnemyPosition = _brain.PlayerTrm.position;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    #if UNITY_EDITOR

    private void OnDrawGizmos()
    {
        if (UnityEditor.Selection.activeObject == gameObject)
        {
            Gizmos.color = Color.red;
            Gizmos.DrawWireSphere(transform.position, _distance);
            Gizmos.color = Color.white;
        }
    }

#endif
}
