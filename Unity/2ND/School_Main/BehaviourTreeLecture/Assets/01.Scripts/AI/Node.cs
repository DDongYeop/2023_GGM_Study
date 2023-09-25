namespace BehaviourTree
{
    public enum NodeState
    {
        SUCCESS = 1,
        FAILURE = 2,
        RUNNING = 3
    }

    public enum NodeActionCode
    {
        NODE = 0,
        CHASING = 1,
        SHOOT = 2,
        RELOADING = 3
    }
    
    public abstract class Node
    {
        protected NodeState _nodeState;
        public NodeState NodeState => _nodeState;

        protected NodeActionCode _code = NodeActionCode.NODE;

        public abstract NodeState Evaluate();
    }
}
