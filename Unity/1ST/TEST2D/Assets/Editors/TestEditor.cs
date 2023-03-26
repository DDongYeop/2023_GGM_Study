using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(Test))]
public class TestEditor : Editor
{
    public override void OnInspectorGUI()
    {
        base.OnInspectorGUI();
        
        Test t = target as Test;
        
        
        GUILayout.BeginHorizontal();
        if (GUILayout.Button("TEST"))
        {
            t.PrintMsg();
        }
        GUILayout.EndHorizontal();
    }
}
