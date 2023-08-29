using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementBT : MonoBehaviour
{
    private Node root;
    private Movement movement;

    private void Start()
    {
        Transform followerTransform = transform;
        float followDistance = 2.0f;
        movement = new Movement(followerTransform, followDistance);

        PlayerMove playerMove = GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerMove>();

        root = new SelectorNode(new List<Node>
        {
            new SequenceNode(new List<Node>
            {
                new CKPlayerStateNode(playerMove),
                new GotoTarget(() => movement.FollowPlayerAction(playerMove.transform))
            }),
            new MonsterRun(followerTransform, playerMove.transform),
        });
    }

    private void Update()
    {
        root.Evaluate();
    }
}
