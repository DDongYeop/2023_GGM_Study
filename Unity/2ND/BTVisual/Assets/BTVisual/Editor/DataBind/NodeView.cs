using System.Collections;
using System.Collections.Generic;
using UnityEditor.Experimental.GraphView;
using UnityEngine;

namespace BTVisual
{
    public class NodeView : UnityEditor.Experimental.GraphView.Node
    {
        public Node node;

        public Port input; //입력노드
        public Port output; //출력노드

        public NodeView(Node node)
        {
            this.node = node;
            this.title = node.name;

            this.viewDataKey = node.guid;

            style.left = node.position.x;
            style.top = node.position.y;

            CreteInputPorts();
            CreteOutputPorts();
        }

        private void CreteInputPorts()
        {
            if (node is CompositeNode)
            {
                input = InstantiatePort(Orientation.Horizontal, Direction.Input, Port.Capacity.Single, typeof(bool));
            }
            else if (node is CompositeNode)
            {
                input = InstantiatePort(Orientation.Horizontal, Direction.Input, Port.Capacity.Single, typeof(bool));   
            }
            else if (node is DecoratorNode)
            {
                input = InstantiatePort(Orientation.Horizontal, Direction.Input, Port.Capacity.Single, typeof(bool));
            }

            if (input != null)
            {
                input.portName = "";
                inputContainer.Add(input);
            }
        }

        private void CreteOutputPorts()
        {
            if (node is CompositeNode)
            {
                
            }
            else if (node is CompositeNode)
            {
                
            }
            else if (node is DecoratorNode)
            {
                
            }
        }

        public override void SetPosition(Rect newPos)
        {
            base.SetPosition(newPos);
            node.position.x = newPos.xMin;
            node.position.y = newPos.yMin;
        }
    }
}
