using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DistanceDecitions : AIDecision
{
    public Transform PlayerTrm;
    public float Distance = 5f;
    
    public override bool MakeDecision()
    {
        return Vector3.Distance(PlayerTrm.position, transform.position) < Distance;
    }
    
    #if UNITY_EDITOR
    private void OnDrawGizmos()
    {
        if (UnityEditor.Selection.activeObject == gameObject)
        {
            Gizmos.color = Color.green;
            Gizmos.DrawWireSphere(transform.position, Distance);
            Gizmos.color = Color.white;
        }
    }
    #endif
}
