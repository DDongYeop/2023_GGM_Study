using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CKPlayerStateNode : Node
{
    private PlayerMove playerMove;

    public CKPlayerStateNode(PlayerMove movement)
    {
        playerMove = movement;
    }
    
    public override NodeState Evaluate()
    {
        if (playerMove.IsMoving())
            return NodeState.Success;
        else
            return NodeState.Failure;
    }
}
