using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(PlayerFOV))]
public class FOVEditor : Editor
{
    //씬 그려질떄 동작하는 함수
    private void OnSceneGUI()
    {
        var pFov = target as PlayerFOV;
        var pos = pFov.transform.position;
        Handles.color = Color.white;
        Handles.DrawWireArc(pos, Vector3.up, Vector3.forward, 360f, pFov.viewRadius);

        Vector3 viewAngleA = pFov.DirFromAngle(-pFov.viewAngle * .5f, false);
        Vector3 viewAngleB = pFov.DirFromAngle(pFov.viewAngle * .5f, false);
        
        Handles.DrawLine(pos, pos + viewAngleA * pFov.viewRadius);
        Handles.DrawLine(pos, pos + viewAngleB * pFov.viewRadius);

        Handles.color = Color.red;

        foreach (var trm in pFov.visibleTargets)
            Handles.DrawLine(pos, trm.position);
    }
}
