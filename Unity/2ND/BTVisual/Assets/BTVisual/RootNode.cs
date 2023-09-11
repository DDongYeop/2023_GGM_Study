namespace BTVisual
{
    public class RootNode : Node
    {
        public Node child;
        
        protected override void OnStart()
        {
            
        }

        protected override void OnStop()
        {
            
        }

        protected override State OnUpdate()
        {
            return child.Update();
        }
    }
}
