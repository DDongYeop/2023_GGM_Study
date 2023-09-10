using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class SoundFeedback : Feedback
{
    [SerializeField] private AudioClip _audioClip;
    [SerializeField] private SoundEffect _effectPrefab;
    [SerializeField] private float _pitchRandom = 0.2f;

    public override void CompletePreFeedback()
    {
    }
    
    public override void CreateFeedback()
    {
        var effect = Instantiate(_effectPrefab);
        effect.PlayClip(_audioClip, _pitchRandom);
    }
}
