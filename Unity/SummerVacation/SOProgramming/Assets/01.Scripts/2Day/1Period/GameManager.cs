using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    private static GameManager instance;
    private static GameManager Instance
    {
        get
        {
            if (instance == null)
                instance = FindObjectOfType<GameManager>();
            return instance;
        }
    }

    private void Start()
    {
        GameSettingSO setting = Resources.Load<GameSettingSO>("GameSettingSO");
    }

    private void GameSetting(GameSettingSO gameSettingSo)
    {
        
    }

    // 오디오 설정
    private float masterVolum = 1f;
    private float musicVolum = 1f;
    private float sfxVolum = 1f;

    public static void SetMasterVolume(float volume)
    {
        Instance.masterVolum = Mathf.Clamp01(volume);
        //오디오 설정 적용 
    }
    
    public static void SetMusicVolume(float volume)
    {
        Instance.musicVolum = Mathf.Clamp01(volume);
        //오디오 설정 적용 
    }
    
    public static void SetSfxVolume(float volume)
    {
        Instance.sfxVolum = Mathf.Clamp01(volume);
        //오디오 설정 적용 
    }
}
