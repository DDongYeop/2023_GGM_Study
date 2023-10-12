using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotator : MonoBehaviour
{
    public float rotateValue = 360f;

    private void Update()
    {
        transform.Rotate(rotateValue * Time.deltaTime, 0,0);
    }
}
