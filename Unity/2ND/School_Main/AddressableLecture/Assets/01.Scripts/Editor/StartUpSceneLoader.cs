using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEditor.SceneManagement;
using UnityEngine;

[InitializeOnLoad]
public static class StartUpSceneLoader 
{
    static StartUpSceneLoader()
    {
        EditorApplication.playModeStateChanged += LoadStartUpScene;
    }

    private static void LoadStartUpScene(PlayModeStateChange state)
    {
        if (state == PlayModeStateChange.ExitingEditMode)
            EditorSceneManager.SaveCurrentModifiedScenesIfUserWantsTo(); //유저가 원하면 현재 수정된 씬 저장할 수 있도록 팝업 띄우는거

        if (state == PlayModeStateChange.EnteredPlayMode)
        {
            if (EditorSceneManager.GetActiveScene().buildIndex != 0)
                EditorSceneManager.LoadScene(0);
        }
    }
}
