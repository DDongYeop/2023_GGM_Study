using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;

    private Cannon _player;
    public Cannon Player => _player;
    
    private void Awake()
    {
        if (Instance != null)
            Debug.Log("Multiple GameManager is running");
        Instance = this;

        FindPlayer();
        CreateUIManager();
    }

    private void FindPlayer()
    {
        _player = FindObjectOfType<Cannon>();
    }

    private void CreateUIManager()
    {
        Canvas mainCanvas = FindObjectOfType<Canvas>();
        UIManager.Instance = mainCanvas.gameObject.AddComponent<UIManager>();
        UIManager.Instance.Init();
        UIManager.Instance.AddEvent(_player);
    }
}
