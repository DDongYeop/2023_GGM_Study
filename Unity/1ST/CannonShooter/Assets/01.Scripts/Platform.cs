using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;
using Random = UnityEngine.Random;

public class Platform : MonoBehaviour
{
    [SerializeField] private float _delDistance;
    private Transform _cannonBallTrm;
    [HideInInspector] public PlatformManager PlatformManager;
    
    private void Update()
    {
        if (_cannonBallTrm.position.y - transform.position.y > _delDistance)
            PlatformManager.PlatformReset(this);
    }

    public void ResetPlatform(float y)
    {
        Vector2 bound = CameraManager.Instance.CamWidthBound();
        float x = Random.Range(bound.x, bound.y);
        Vector3 pos = new Vector3(x, y, 0);
        transform.position = pos;
        _cannonBallTrm = GameObject.Find("CannonBall").transform;
    }
}