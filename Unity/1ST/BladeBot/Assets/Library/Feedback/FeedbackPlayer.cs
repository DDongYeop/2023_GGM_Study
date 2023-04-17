using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FeedbackPlayer : MonoBehaviour
{
    private List<Feedback> _feedbackToPlay = null;

    private void Awake()
    {
        _feedbackToPlay = new List<Feedback>();
        GetComponents<Feedback>(_feedbackToPlay); //나한테 붙은 피드백 가져오기
    }

    public void PlayFeedback()
    {
        FinishFeedback();
        foreach (Feedback f in _feedbackToPlay)
        {
            f.CreateFeedback();
        }
    }

    public void FinishFeedback()
    {
        foreach (Feedback f in _feedbackToPlay)
        {
            f.FinishFeedback();
        }
    }
}
