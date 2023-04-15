using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform : MonoBehaviour
{
    public void ResetPlatform(float y)
    {
        Vector2 bound = CameraManager.Instance.CamWidthBound();
        float x = Random.Range(bound.x, bound.y);
        Vector3 pos = new Vector3(x, y, 0);
        transform.position = pos;
    }
}
