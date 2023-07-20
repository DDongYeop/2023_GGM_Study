using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu (fileName = "GameSettingData")]
public class GameSoundSO : ScriptableObject
{
    public bool soundEnabled;
    public float musicVolume;
    public float sfxVolume;

    public bool SoundEnabled
    {
        get => soundEnabled;
        set => soundEnabled = value;
    }
}
