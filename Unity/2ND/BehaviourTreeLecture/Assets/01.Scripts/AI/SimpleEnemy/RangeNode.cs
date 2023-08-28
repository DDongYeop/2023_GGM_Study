using System.Collections;
using System.Collections.Generic;
using BehaviourTree;
using UnityEngine;

public class RangeNode : Node
{
    private float _range;
    private Transform _target;
    private Transform _bodyTrm;

    public RangeNode(float range, Transform target, Transform body)
    {
        _range = range;
        _target = target;
        _bodyTrm = body;
    }
    
    public override NodeState Evaluate()
    {
        float distance = Vector3.Distance(_bodyTrm.position, _target.position);
        return distance < _range ? NodeState.SUCCESS : NodeState.FAILURE;
    }
}
