using System;
using UnityEngine;
using UnityEngine.Serialization;

[Serializable]
public class BlackBoard
{
    public Vector3 moveToPosition;
    public LayerMask whatIsEnemy;
    public Vector3 lastSpotPosition;
    public bool isHit;
}
