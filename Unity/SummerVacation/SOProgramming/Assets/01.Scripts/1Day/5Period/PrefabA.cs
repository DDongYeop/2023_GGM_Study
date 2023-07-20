using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PrefabA : MonoBehaviour
{
    public ShareDB shareDB;

    private void Start()
    {
        shareDB = Resources.Load<ShareDB>("SharedDB");

        Debug.Log("Prefab A에서 공유 한 값 " + shareDB.SharedValue);
    }
}
