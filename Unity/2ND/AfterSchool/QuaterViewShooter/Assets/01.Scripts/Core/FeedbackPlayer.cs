using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FeedbackPlayer : MonoBehaviour
{
    private List<Feedback> _feedbackToPlay = new List<Feedback>();


    private void Awake()
    {
        GetComponents<Feedback>(_feedbackToPlay); //������ ���� ��� �ǵ���� �� �����´�.
    }

    public void PlayFeedback()
    {
        FinishFeedback();
        foreach (var f in _feedbackToPlay)
        {
            f.CreateFeedback();
        }
    }

    public void FinishFeedback()
    {
        foreach(var f in _feedbackToPlay)
        {
            f.CompletePrevFeedback();
        }
    }
}
