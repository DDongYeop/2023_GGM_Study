using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu (fileName = "SharedDB")]
public class ShareDB : ScriptableObject
{
    [SerializeField] private int _sharedValue;

    public int SharedValue
    {
        get { return _sharedValue; }
        set { _sharedValue = value; }
    }
}
