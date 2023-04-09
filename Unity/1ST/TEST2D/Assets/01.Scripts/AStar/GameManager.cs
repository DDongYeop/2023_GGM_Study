using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;
    
    [SerializeField] private Transform _playerTrm;
    public Transform PlayerTrm => _playerTrm;

    [SerializeField] private Transform _tileMapParent;

    private void Awake()
    {
        if (Instance != null)
            Debug.LogError("Multiple GameMamager is running");
        Instance = this;

        TileMapManager.Instance = new TileMapManager(_tileMapParent);
    }
}
