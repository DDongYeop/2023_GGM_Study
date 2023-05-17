using Core;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;

    [SerializeField]
    private PoolingListSO _initPoolList;

    private Transform _playerTrm;
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
        if(Instance != null)
        {
            Debug.LogError("Multiple GameManager is running");
        }
        Instance = this;

        CreatePool();
        CreateTimeController();
    }

    private void CreateTimeController()
    {
        TimeController.Instance = gameObject.AddComponent<TimeController>();
    }

    private void CreatePool()
    {
        PoolManager.Instance = new PoolManager(transform);
        _initPoolList.PoolList.ForEach(p =>
        {
            PoolManager.Instance.CreatePool(p.Prefab, p.Count);
        });
    }


    //디버그 코드
    //[SerializeField]
    //private LayerMask _whatIsGround;
    //private void Update()
    //{
    //    if(Input.GetKeyDown(KeyCode.Q))
    //    {
    //        Ray ray = Define.MainCam.ScreenPointToRay(Input.mousePosition);
    //        RaycastHit hit;

    //        bool result = Physics.Raycast(ray, out hit, Define.MainCam.farClipPlane, _whatIsGround);
            
    //        if(result)
    //        {
    //            PoolableMono mono = PoolManager.Instance.Pop("HammerEnemy");

    //            mono.transform.SetPositionAndRotation(hit.point, Quaternion.identity);
    //        }
    //    }
    //}
}
