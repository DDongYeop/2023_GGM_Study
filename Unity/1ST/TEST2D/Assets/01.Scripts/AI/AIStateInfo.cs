using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AIStateInfo : MonoBehaviour
{
    public Vector3 LastEnemyPosition;
    public float MeleeCool = 0f;
    public float RangeCool = 0f;

    public bool IsAttack;
    public bool IsRange;
    public bool IsMelee;

    public bool IsArrived; //목적지 도착 여부
    
}
