using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyRenderer : MonoBehaviour
{
    private NavAgent _navAgent;

    private void Awake()
    {
        _navAgent = GetComponent<NavAgent>();
    }

    private void Update()
    {
        Vector3 worldPos = TileMapManager.Instance.GetTilePos(_navAgent.Destination);

        /*if (worldPos.x < transform.position.x)
            transform.localScale = new Vector3(-.5f, .5f, .5f);
        else
            transform.localScale = new Vector3(.5f, .5f, .5f);*/

        Vector3 dir = worldPos - transform.position;
        float degree = Mathf.Atan2(dir.y, dir.x) * Mathf.Rad2Deg;
        Quaternion targetRot =  Quaternion.Euler(0,0,degree);
        transform.rotation = Quaternion.Lerp(transform.rotation, targetRot, Time.deltaTime * 4f);
    }
}
