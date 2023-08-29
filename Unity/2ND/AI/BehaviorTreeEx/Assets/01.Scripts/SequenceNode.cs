using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SequenceNode : Node
{
    private List<Node> childNodes;

    public SequenceNode(List<Node> nodes)
    {
        childNodes = nodes;
    }

    public override NodeState Evaluate()
    {
        bool allChildrenSuccess = true;
        foreach (var node in childNodes)
        {
            NodeState result = node.Evaluate();
            if (result == NodeState.Failure)
                return NodeState.Failure;
            else if (result == NodeState.Running)
                allChildrenSuccess = false;
        }

        return allChildrenSuccess ? NodeState.Success : NodeState.Running;
    }
}
