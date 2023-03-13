using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NormalState : CommonState
{
    protected AgentMovement _agentMovment;
    protected AgentInput _agentInput;
    
    public override void OnEnterState()
    {
        _agentMovment?.StopImmediately();
        _agentInput.OnMovementKeyPress += OnMovementHandle;
    }

    public override void OnExitState()
    {
        _agentMovment?.StopImmediately();
        _agentInput.OnMovementKeyPress -= OnMovementHandle;
    }

    private void OnMovementHandle(Vector3 obj)
    {
        _agentMovment?.SetMovementVelocity(obj);
    }

    public override void SetUp(Transform agentRoot)
    {
        base.SetUp(agentRoot);
        _agentMovment = agentRoot.GetComponent<AgentMovement>();
    }

    public override void UpdateState()
    {
    }
}
