using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;
using UnityEngine.UIElements;

public class LoadingScreen : MonoBehaviour
{
    [SerializeField] private LoadingSetSO _loadingSet;
    private UIDocument _uiDocument;
    
    private bool _loadingComplete = false;
    private Label _descriptionLabel;
    private Label _completeLabel;

    private void Awake()
    {
        _uiDocument = GetComponent<UIDocument>();
    }

    private void OnEnable()
    {
        var root = _uiDocument.rootVisualElement;
        _descriptionLabel = root.Q<Label>("description-label");
        _completeLabel = root.Q<Label>("complete-label");
    }

    private async void Start()
    {
        await LoadItems();
        _descriptionLabel.text = "making object pooling!";
        await MakePoolingObjects();
    }

    private async Task LoadItems()
    {
        int index = 0;
        int totalCount = _loadingSet.GetTotalCount();

        foreach (var item in _loadingSet.loadingList)
        {
            if(!item.reference.IsValid())  
            {
                _descriptionLabel.text = $"loading items ({index + 1}/{totalCount})";
                await item.reference.LoadAssetAsync<GameObject>().Task;
            }
            index++;
        }

        foreach (var item in _loadingSet.poolingList)
        {
            if (!item.reference.IsValid())
            {
                _descriptionLabel.text = $"loading items ({index + 1}/{totalCount})";
                await item.reference.LoadAssetAsync<GameObject>().Task;
            }
            index++;
        }
    }

    private async Task MakePoolingObjects()
    {
        int index = 0;
        int totalCount = _loadingSet.poolingList.Count;
        ObjectPools.Instance.DestroyAll(); //처음 시작할때 기존에 있던 애들 다 뽀샤주고
        foreach(var item in _loadingSet.poolingList)
        {
            _descriptionLabel.text = $"make item pool ({index + 1}/{totalCount})";
            await PoolManager.Instance.CreatePool(item.reference, item.count);
            ++index;
        }
        _loadingComplete = true;
        _completeLabel.AddToClassList("on");
    }

    private void Update()
    {
        if(Keyboard.current.anyKey.wasPressedThisFrame && _loadingComplete)
        {
            SceneManager.LoadScene(SceneName.GameName);
        }
    }
}
