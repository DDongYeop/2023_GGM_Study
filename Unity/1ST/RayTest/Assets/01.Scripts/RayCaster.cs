using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RayCaster : MonoBehaviour
{
    [SerializeField] private float _maxDistance = 5f;
    
    private void OnDrawGizmos()
    {
        RaycastHit hit;

        //bool isHit = Physics.Raycast(transform.position, transform.forward, out hit, _maxDistance, 1 << LayerMask.NameToLayer("Enemy"));
        bool isHit = Physics.BoxCast(transform.position, transform.lossyScale * 0.5f, transform.forward, out hit, transform.rotation, _maxDistance);
        
        if (isHit)
        {
            Gizmos.color = Color.red;
            Gizmos.DrawRay(transform.position, transform.forward * hit.distance);
        }
        else
        {
            Gizmos.color = Color.green;
            Gizmos.DrawRay(transform.position, transform.forward * _maxDistance);
        }
    }
}
