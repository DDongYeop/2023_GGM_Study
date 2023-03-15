using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Attack : MonoBehaviour
{
    [SerializeField] private float _maxDistance = 5f;
    private bool isOn = false;
    
    private void OnDrawGizmos()
    {
        RaycastHit hit;
        bool isHit = Physics.BoxCast(transform.position, transform.lossyScale * 0.5f, transform.forward, out hit, transform.rotation, _maxDistance);
        
        if (isHit)
        {
            Gizmos.color = Color.red;
            Gizmos.DrawRay(transform.position, transform.forward * hit.distance);
            Gizmos.DrawWireCube(transform.position + transform.forward * hit.distance, transform.lossyScale);
            if (Input.GetKeyDown(KeyCode.Space) || Input.GetButton("Fire1"))
            {
                hit.collider.GetComponent<Rigidbody>().AddForce(transform.forward * 500f);
            }
        }
        else
        {
            Gizmos.color = Color.green;
            Gizmos.DrawRay(transform.position, transform.forward * _maxDistance);
        }
    }
}
