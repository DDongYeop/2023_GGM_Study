using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public GameSetting resourcePath;
    
    private void Start()
    {
        resourcePath = Resources.Load<GameSetting>("ResourcesPathAsset");
        GameObject characterPrefab = Resources.Load<GameObject>(resourcePath.characterPrefabPath);
        Instantiate(characterPrefab);
    }
}
