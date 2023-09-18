using Cinemachine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraShakeFeedback : Feedback
{
    [SerializeField] private CinemachineImpulseSource _source;
    [SerializeField] private float _impulsePower = 0.2f;

    public override void CompletePrevFeedback()
    {
        _source.GenerateImpulse(_impulsePower);
    }

    public override void CreateFeedback()
    {
        
    }
}
