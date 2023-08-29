using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterRun : Node
{
    private Transform agentTransform;
    private Transform playerTransform;
    private float moveSpd = 2.0f;
    private float fleeDistance = 10.0f;

    private bool fleeing = false;

    public MonsterRun(Transform agent, Transform player)
    {
        agentTransform = agent;
        playerTransform = player;
        fleeing = false;
    }
    
    public override NodeState Evaluate()
    {
        Vector3 agentPosition = agentTransform.position;
        Vector3 playerPosition = playerTransform.position;
        Vector3 dirToPlayer = playerPosition - agentPosition;
        float _distance = dirToPlayer.magnitude;

        if (!fleeing)
        {
            Vector3 dirAvoidPlayer = -dirToPlayer.normalized;
            Vector3 vecMove = dirAvoidPlayer * moveSpd * Time.deltaTime;

            if (_distance > fleeDistance)
            {
                fleeing = false;
                return NodeState.Running;
            }
            else
            {
                agentTransform.Translate(vecMove);
                return NodeState.Running;
            }
        }
        else
        {
            Vector3 dirOpposite = (agentPosition - playerPosition).normalized;

            Vector3 moveVector = dirOpposite * moveSpd * Time.deltaTime;
            agentTransform.Translate(moveVector);

            return NodeState.Success;
        }
    }
}
