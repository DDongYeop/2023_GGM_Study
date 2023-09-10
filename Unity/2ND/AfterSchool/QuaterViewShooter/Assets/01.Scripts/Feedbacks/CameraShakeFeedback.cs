using System.Collections;
using System.Collections.Generic;
using Cinemachine;
using UnityEngine;

public class CameraShakeFeedback : Feedback
{
    [SerializeField] private CinemachineImpulseSource _source;
    [SerializeField] private float _impulsePower = 0.2f;

    public override void CompletePreFeedback()
    {
        
    }
    
    public override void CreateFeedback()
    {
        _source.GenerateImpulse(_impulsePower);
    }
}
