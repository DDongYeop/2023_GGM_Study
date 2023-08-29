using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectorNode : Node
{
    private List<Node> childNodes;

    public SelectorNode(List<Node> nodes)
    {
        childNodes = nodes;
    }

    public override NodeState Evaluate()
    {
        foreach (var node in childNodes)
        {
            NodeState result = node.Evaluate();
            if (result == NodeState.Success)
                return NodeState.Success;
            else if (result == NodeState.Running)
                return NodeState.Running;
        }

        return NodeState.Failure;
    }
}
