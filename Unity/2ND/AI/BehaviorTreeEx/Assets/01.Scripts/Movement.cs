using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting.Antlr3.Runtime.Tree;
using UnityEngine;

public class Movement
{
    private Transform followerTransform;
    private float followDistance;
    private float maxSpd = 10.0f;
    private float nowSpd = 0.0f;
    private float addSpd = 2.0f;

    public Movement(Transform follower, float distance)
    {
        followerTransform = follower;
        followDistance = distance;
    }

    public NodeState FollowPlayerAction(Transform playerTransform)
    {
        Vector3 direction = playerTransform.position - followerTransform.position;
        float distance = direction.magnitude;

        float targetSpd = Mathf.Lerp(0, maxSpd, Mathf.InverseLerp(0, followDistance, distance));
        nowSpd = Mathf.MoveTowards(nowSpd, targetSpd, addSpd * Time.deltaTime);

        Vector3 moveVector = direction.normalized * nowSpd * Time.deltaTime;
        
        followerTransform.Translate(moveVector);

        if (distance > followDistance)
            return NodeState.Running;
        else
        {
            nowSpd = 0.0f;
            return NodeState.Success;
        }
    }
}
