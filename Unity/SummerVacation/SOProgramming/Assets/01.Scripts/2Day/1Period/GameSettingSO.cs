using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameSettingSO : MonoBehaviour
{
    [Header("Audio Setting")] 
    public float masterVolume;
    public float musicVolume;
    public float sfxVolume;

    [Header("Graphics Setting")] 
    public int resolutionWidth;
    public int resolutionHeight;
    public bool fullScreen;

    [Header("Gameplay Setting")] 
    public bool showTutorial;
    public bool enableVibration;
}
