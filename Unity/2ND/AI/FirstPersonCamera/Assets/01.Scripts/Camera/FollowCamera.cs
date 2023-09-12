using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowCamera : MonoBehaviour
{
    public Transform camTarget;

    public float camDistance = 10f;
    public float camAngle = 45f;
    public float targetHeight = 2f;

    private Vector3 refVelocity;
    public float camFlowTIme = .5f;

    public float camHeight = 5f; 
    
    public void TopDownFollowCamera()
    {
        if (!camTarget)
            return;

        Vector3 posCamTarget = camTarget.position;
        posCamTarget.y += targetHeight;
        Vector3 posCam = (Vector3.forward * -camDistance) + (Vector3.up * camHeight);
        Vector3 posRotated = Quaternion.AngleAxis(camAngle, Vector3.up) * posCam;
        Vector3 lastPosCam = posCamTarget + posRotated;
        
        transform.position = Vector3.SmoothDamp(transform.position, lastPosCam, ref refVelocity, camFlowTIme);
        transform.LookAt(camTarget.position);
    }

    private void LateUpdate()
    {
        TopDownFollowCamera();
    }
}
