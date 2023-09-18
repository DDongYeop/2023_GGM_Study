using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

public class MenuScreen : MonoBehaviour
{
    
    private void Update()
    {
        if(Keyboard.current.spaceKey.wasPressedThisFrame)
        {
            SceneManager.LoadScene(SceneName.LoadingName);
        }
    }
}
