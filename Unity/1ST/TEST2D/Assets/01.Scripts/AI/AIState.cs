using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AIState : MonoBehaviour
{
    public List<AIAction> Actions = null;
    public List<AITransition> Transitions = null;

    protected AIBrain _brain;

    private void Awake()
    {
        _brain = transform.parent.parent.GetComponent<AIBrain>();
        Actions = new List<AIAction>();
        GetComponents<AIAction>(Actions);
        Actions.ForEach(a => a.SetUp(_brain));

        Transitions = new List<AITransition>();
        GetComponentsInChildren<AITransition>(Transitions);
        
        Transitions.ForEach(t => t.SetUp(_brain));
    }

    public void UpdateState()
    {
        //내가 가진 액션 전부 수행
        foreach (AIAction a in Actions)
        {
            a.TakeAction();
        }
        //내가 전이할 곳들도 전부 판단
        foreach (AITransition t in Transitions)
        {
            if (t.CheckTransition())
            {
                _brain.ChangeState(t.NextState);
                break;
            }
        }
    }
}
