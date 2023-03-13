using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class CommonState : MonoBehaviour, IState
{
    public abstract void OnEnterState();
    public abstract void OnExitState();
    public abstract void UpdateState();
    
    protected AgentAnimator animator;
    protected AgentInput agentInput;
    protected AgentController agentController;

    public virtual void SetUp(Transform agentRoot)
    {
        animator = agentRoot.Find("Visual").GetComponent<AgentAnimator>();
        agentInput = agentRoot.GetComponent<AgentInput>();
        agentController = agentRoot.GetComponent<AgentController>();

    }
    
    //피격처리시 사용
    public void OnHitHandle(Vector3 hitPoint, Vector3 Normal)
    {

    }
}  