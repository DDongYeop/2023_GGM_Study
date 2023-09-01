using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerFOV : MonoBehaviour
{
    [Range(0, 360)] public float viewAngle;
    public float viewRadius;

    public Vector3 DirFromAngle(float degree, bool angleIsGlobal)
    {
        if (!angleIsGlobal)
        {
            degree += transform.eulerAngles.y;
        }

        float rad = degree * Mathf.Deg2Rad;
        return new Vector3(Mathf.Sin(rad), 0, Mathf.Cos(rad));
    }
}
