using System;
using System.Collections;
using System.Collections.Generic;
using BehaviourTree;
using UnityEngine;

public class SimpleEnemyBrain : EnemyBrain
{
    private Node _topNode;
    private NodeState _beforeTopState;

    protected void Start()
    {
        ConstructAIBrin();
    }

    private void ConstructAIBrin()
    {
        Transform me = transform;
        RangeNode shootingRange = new RangeNode(3f, _targetTrm, me);
        ShootNode shootNode = new ShootNode(NavAgent, this, 1.5f);
        Sequence shootSeq = new Sequence(new List<Node>{shootingRange, shootNode});

        RangeNode chasingRange = new RangeNode(10f, _targetTrm, me);
        ChaseNode chaseNode = new ChaseNode(_targetTrm, NavAgent, this);
        Sequence chaseSeq = new Sequence(new List<Node> { chasingRange, chaseNode });

        _topNode = new Selector(new List<Node> { shootSeq, chaseSeq });
    }

    private void Update()
    {
        _topNode.Evaluate();
        if (_topNode.NodeState == NodeState.FAILURE && _beforeTopState != NodeState.FAILURE)
        {
            TryToTalk("아무것도 할게 없어");
        }

        _beforeTopState = _topNode.NodeState;
    }
}
