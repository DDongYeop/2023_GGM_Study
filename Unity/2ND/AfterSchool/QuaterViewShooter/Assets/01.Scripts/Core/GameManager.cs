
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    private void Update()
    {
        if(Keyboard.current.yKey.wasPressedThisFrame)
        {
            PoolManager.Instance.ClearPool(true); //�ε��ߴ� �����յ���� �ϴ� ��ε��ؼ� ����
            SceneManager.LoadScene(SceneName.MenuName);
        }
    }
}
