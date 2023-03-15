using System.Collections;
using System.Collections.Generic;
using Core;
using UnityEngine;

public class NormalState : CommonState
{
    protected AgentMovement _agentMovement;

    public override void OnEnterState()
    {
        _agentMovement?.StopImmediately();
        _agentInput.OnMovementKeyPress += OnMovementHandle;
        _agentInput.OnAttackKeyPress += OnAttackKeyHandle;
    }

    public override void OnExitState()
    {
        _agentMovement?.StopImmediately();
        _agentInput.OnMovementKeyPress -= OnMovementHandle;
        _agentInput.OnAttackKeyPress -= OnAttackKeyHandle;
    }

    private void OnAttackKeyHandle()
    {
        Vector3 targetPos = _agentInput.GetMouseWorldPosition();
        //_agentMovement.SetRotation(targetPos);
        _agentController.ChangeState(StateType.Attack);
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
