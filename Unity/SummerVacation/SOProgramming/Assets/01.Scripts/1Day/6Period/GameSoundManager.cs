using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameSoundManager : MonoBehaviour
{
    public GameSoundSO settingsData;

    private void Start()
    {
        settingsData = Resources.Load<GameSoundSO>("GameSettingData");

        Debug.Log("사운드 사용 여부" + settingsData.soundEnabled);
        Debug.Log("음악 볼륨" + settingsData.musicVolume);
        Debug.Log("효과음 볼륨" + settingsData.sfxVolume);
    }
}

// SO의 장점들 
//  - 동일한 애들 다른 곳에서도 사용가능 (값 바뀌더라도 다른 곳에도 동일하게 적용)
//  - 관리가 편하다 (기획자 같은 사람이 와서 바꾸기 좋음)
//  - 이상진 선생님이 알려주신다 ! (미춋다 미춋다 개쩐다)
// 관리 편함
// 유지 보수 편함 
// 등등 