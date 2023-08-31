using BehaviourTree;

public class NeedReloadingNode : Node
{
    private Gun _gun;

    public NeedReloadingNode(Gun gun)
    {
        _gun = gun;
    }
    
    public override NodeState Evaluate()
    {
        return _gun.IsEnpty ? NodeState.SUCCESS : NodeState.FAILURE;
    }
}
