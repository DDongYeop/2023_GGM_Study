using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SecondCamera : MonoBehaviour
{
    public Transform target = null;

    public float spdR;

    private void LateUpdate()
    {
        transform.RotateAround(target.position,Vector3.up, spdR * Time.deltaTime);
        transform.LookAt(target);
    }
}
