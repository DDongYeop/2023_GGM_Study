using System;
using System.Collections;
using System.Collections.Generic;
using BehaviourTree;
using UnityEngine;

public class SimpleEnemyBrain : EnemyBrain
{
    private Node _topNode;
    private NodeState _beforeTopState;

    private EnemyAttack _enemyAttack;
    private Gun _gun;

    protected override void Awake()
    {
        base.Awake();
        _enemyAttack = GetComponent<EnemyAttack>();
        _gun = transform.Find("Gun").GetComponent<Gun>();
    }

    public override void Attack()
    {
        _enemyAttack.Attack();
    }

    protected void Start()
    {
        ConstructAIBrin();
    }

    private void ConstructAIBrin()
    {
        Transform me = transform;
        
        NeedReloadingNode needReloadingNode = new NeedReloadingNode(_gun);
        Reloading reloading = new Reloading(this, _gun, 3f);
        Sequence reloadSeq = new Sequence(new List<Node> { needReloadingNode, reloading });
        
        RangeNode shootingRange = new RangeNode(7f, targetTrm, me);
        ShootNode shootNode = new ShootNode(NavAgent, this, 1.5f, _gun);
        Sequence shootSeq = new Sequence(new List<Node>{shootingRange, shootNode});

        RangeNode chasingRange = new RangeNode(14f, targetTrm, me);
        ChaseNode chaseNode = new ChaseNode(targetTrm, NavAgent, this);
        Sequence chaseSeq = new Sequence(new List<Node> { chasingRange, chaseNode });


        _topNode = new Selector(new List<Node> { reloadSeq, shootSeq, chaseSeq });
    }

    private void Update()
    {
        _topNode.Evaluate();
        if (_topNode.NodeState == NodeState.FAILURE && _beforeTopState != NodeState.FAILURE)
        {
            TryToTalk("아무것도 할게 없어");
            NavAgent.isStopped = true;
            currentCode = NodeActionCode.NODE;
        }

        _beforeTopState = _topNode.NodeState;
    }
}
