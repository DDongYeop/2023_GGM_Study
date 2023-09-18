
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    private void Update()
    {
        if(Keyboard.current.yKey.wasPressedThisFrame)
        {
            PoolManager.Instance.ClearPool(true); //로드했던 프리팹들까지 싹다 언로드해서 종료
            SceneManager.LoadScene(SceneName.MenuName);
        }
    }
}
