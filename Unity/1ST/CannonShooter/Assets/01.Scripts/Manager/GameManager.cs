using System;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;

    private Cannon _player;
    public Cannon Player => _player;

    private Stage _currentStage;
    private AsyncOperationHandle<GameObject> _handle;

    private int _currentBoxCount = 0;
    private int _maxBoxCount = 0;

    public event Action OnStageLoadCompleted;
    public event Action OnStartLoad; 

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
    
    public int CurrentBoxCount
    {
        get => _currentBoxCount;
        set
        {
            _currentBoxCount = value;
            UpdateCountUI();
        }
    }

    private void LoadStage(int number)
    {
        if (_currentStage != null)
        {
            Destroy(_currentStage.gameObject);
            Addressables.Release(_handle); //이전 핸들도 함께 릴리즈
        }
        
        Addressables.LoadAssetAsync<GameObject>($"Level{number.ToString()}").Completed += (AsyncOperationHandle<GameObject> handle) => 
        {
            if (handle.Status == AsyncOperationStatus.Succeeded)
            {
                _handle = handle;
                GameObject stage = Instantiate(handle.Result, Vector3.zero, Quaternion.identity);
                SetStage(stage.GetComponent<Stage>());
            }
            else
                Debug.LogError(handle.Status);
        };
    }

    private void SetStage(Stage stage)
    {
        _currentStage = stage;
        _player.transform.position = _currentStage.PlayerPosition;
        _player.SetXBound(_currentStage.StartPos.x, _currentStage.EndPos.x);

        CurrentBoxCount = _maxBoxCount = _currentStage.BoxCount;
        CurrentBoxCount = _currentStage.BallCount;
                    
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
