
using System;
using System.Collections;
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
    
    private int _maxBoxCount = 0;

    public event Action OnStageLoadCompleted;
    public event Action OnStartLoad;

    private float _time;
    
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

    private int _currentBallCount;
    public int CurrentBallCount {
        get => _currentBallCount; 
        set
        {
            _currentBallCount = value;
            UpdateCountUI();
        }
    }

    private int _currentBoxCount;
    public int CurrentBoxCount
    {
        get => _currentBoxCount;
        set
        {
            _currentBoxCount = value;
            UpdateCountUI();
        }
    }

    public void LoadStage(int number)
    {
        if (_currentStage != null)
        {
            Destroy(_currentStage.gameObject);
            Addressables.Release(_handle); //���� �ڵ鵵 �Բ� ������
        }
        
        Addressables.LoadAssetAsync<GameObject>($"Level{number.ToString()}").Completed += (AsyncOperationHandle<GameObject> handle) =>
        {
            if (handle.Status == AsyncOperationStatus.Succeeded)
            {
                _handle = handle;
                GameObject stage = Instantiate(handle.Result, Vector3.zero, Quaternion.identity);
                SetStage(stage.GetComponent<Stage>());
                _time = Time.time;
            }
            else
            {
                Debug.Log(handle.Status);
            }
        };
    }

    private void SetStage(Stage stage)
    {
        _currentStage = stage;
        _player.transform.position = _currentStage.PlayerPosition;
        _player.SetXBound(_currentStage.StartPos.x, _currentStage.EndPos.x);

        _currentBoxCount = _maxBoxCount = _currentStage.BoxCount; //��ü �ڽ� ���� �����ϰ�
        _currentBallCount = _currentStage.BallCount; //��ü ��ź �� ������
        UpdateCountUI();
        StartCoroutine(DelayStart());
    }

    private IEnumerator DelayStart()
    {
        yield return new WaitForSeconds(1f);
        OnStageLoadCompleted?.Invoke(); //�������� ���� ��� �Ϸ�
    }

    private void UpdateCountUI()
    {
        UIManager.Instance.BoxCount = $"{_currentBoxCount} / {_maxBoxCount}";
        UIManager.Instance.BallCount = _currentBallCount.ToString();
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

    public bool CheckGameEnd()
    {
        if (_currentBallCount == 0)
        {
            UIManager.Instance.ShowResultPanel(4-CurrentBallCount, _maxBoxCount-_currentBoxCount, (int)(Time.time - _time),1);
            return true;
        }
        else
        {
            return false;
        }
    }
}
