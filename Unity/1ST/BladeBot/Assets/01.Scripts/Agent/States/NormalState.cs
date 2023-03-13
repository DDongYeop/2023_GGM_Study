using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NormalState : CommonState
{
    protected AgentMovement _agentMovement;

    public override void OnEnterState()
    {
        _agentMovement?.StopImmediately();
        _agentInput.OnMovementKeyPress += OnMovementHandle;
    }

    public override void OnExitState()
    {
        _agentMovement?.StopImmediately();
        _agentInput.OnMovementKeyPress -= OnMovementHandle;
    }

    private void OnMovementHandle(Vector3 obj)
    {
        _agentMovement?.SetMovementVelocity(obj);
    }

    public override void SetUp(Transform agentRoot)
    {
        base.SetUp(agentRoot);
        _agentMovement = agentRoot.GetComponent<AgentMovement>();
    }

    public override void UpdateState()
    {
        
    }

}
