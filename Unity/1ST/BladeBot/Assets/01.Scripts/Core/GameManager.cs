using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;
    private Transform _playerTrm;

    [FormerlySerializedAs("_initPollList")] [SerializeField] private PoolingListSO _initPoolList;
    
    public Transform PlayerTrm
    {
        get
        {
            if (_playerTrm == null)
                _playerTrm = GameObject.FindGameObjectWithTag("Player").transform;
            return _playerTrm;
        }
    }

    private void Awake()
    {
        if (Instance != null)
            Debug.LogError("Multiple GameManager is running");
        Instance = this;

        CreatePool();
    }

    private void CreatePool()
    {
        PoolManager.Instance = new PoolManager(transform);
        _initPoolList.PoolList.ForEach(p => 
        {
            PoolManager.Instance.CreatePool(p.Prefab, p.Count);
        });
    }
}
