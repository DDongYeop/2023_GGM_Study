using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;
using Unity.Mathematics;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;

    private Cannon _player;
    public Cannon Player => _player;

    private void Awake()
    {
        if(Instance != null)
        {
            Debug.Log("Multiple GameManager is running");
        }
        Instance = this;

        FindPlayer();
        CreateUIManager();
        CreateCameraManager();
    }

    private void Start()
    {
        LoadStage(1);
    }

    [SerializeField] private Stage _stagePrefab;

    private int _currentBallCount = 0;

    public int CurrentBallCount
    {
        get => _currentBallCount;
        set
        {
            _currentBallCount = value;
            UpdateCountUI();
        }
    }
    
    public int _currentBoxCount = 0;
    public int CurrentBoxCount
    {
        get => _currentBoxCount;
        set
        {
            _currentBoxCount = value;
            UpdateCountUI();
        }
    }
    private int _maxBoxCount = 0;
    
    private void LoadStage(int number)
    {
        Stage s = Instantiate(_stagePrefab, Vector3.zero, quaternion.identity);
        _player.transform.position = s.PlayerPosition;
        _player.SetXBound(s.StartPos.x, s.EndPos.x);

        CurrentBoxCount = _maxBoxCount = s.BoxCount;
        CurrentBoxCount = s.BallCount;
        
        UpdateCountUI();
    }

    private void UpdateCountUI()
    {
        UIManager.Instance.BoxCount = $"{CurrentBoxCount} / {_maxBoxCount}";
        UIManager.Instance.BallCount = $"{_currentBallCount}";
    }

    private void FindPlayer()
    {
        _player = FindObjectOfType<Cannon>(); //2�ο����� �ٲٸ� �̰� �����ؾ� �Ѵ�.
    }

    private void CreateCameraManager()
    {
        GameObject obj = GameObject.Find("CameraManager");
        CameraManager.Instance = obj.AddComponent<CameraManager>();
        CameraManager.Instance.Init(obj.transform);
    }

    private void CreateUIManager()
    {
        Canvas mainCanvas = FindObjectOfType<Canvas>();
        UIManager.Instance = mainCanvas.gameObject.AddComponent<UIManager>();
        //�̱���
        UIManager.Instance.Init();
        UIManager.Instance.AddEvent(_player); //�÷��̾�� ����ǰ���.
    }
}
