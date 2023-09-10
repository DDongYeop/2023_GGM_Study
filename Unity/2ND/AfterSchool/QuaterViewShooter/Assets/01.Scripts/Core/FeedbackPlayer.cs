using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FeedbackPlayer : MonoBehaviour
{
    private List<Feedback> _feedbackToPlayer = new List<Feedback>();

    private void Awake()
    {
        GetComponents<Feedback>(_feedbackToPlayer);
    }

    public void PlayFeedback()
    {
        FinishFeedback();
        foreach (var f in _feedbackToPlayer)
        {
            f.CreateFeedback();
        }
    }

    private void FinishFeedback()
    {
        foreach (var f in _feedbackToPlayer)
        {
            f.CompletePreFeedback();
        }
    }
}
