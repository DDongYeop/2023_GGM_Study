using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace BTVisual
{
    [CreateAssetMenu (menuName = "BehaviourTree/Tree")]
    public class BehaviourTree : ScriptableObject
    {
        public Node rootNode;
        public Node.State treeState = Node.State.RUNNING;

        public List<Node> nodes = new List<Node>(); 

        public Node.State Update()
        {
            if (rootNode.state == Node.State.RUNNING)
            {
                treeState = rootNode.Update();
            }
            return treeState;
        }

        public Node CreateNode(System.Type type)
        {
            var node = ScriptableObject.CreateInstance(type) as Node;
            node.name = type.Name;
            node.guid = GUID.Generate().ToString();
            nodes.Add(node);
            
            AssetDatabase.AddObjectToAsset(node, this);
            AssetDatabase.SaveAssets();

            return node;
        }

        public void DeleteNode(Node node)
        {
            nodes.Remove(node);
            AssetDatabase.RemoveObjectFromAsset(node);
            AssetDatabase.SaveAssets();
        }

        public void AddChild(Node parent, Node child)
        {
            //부모가 누군지에 따라 작동을 달리 해야함
            var decorator = parent as DecoratorNode;
            if (decorator != null)
            {
                decorator.child = child;
                return;
            }

            var composite = parent as CompositeNode;
            if (composite != null)
            {
                composite.children.Add(child);
                return;
            }

            var rootNode = parent as RootNode;
            if (rootNode != null)
            {
                rootNode.child = child;
            }
            //자식이 없기에 다른 경우는 없다.
        }

        public void RemoveChild(Node parent, Node child)
        {
            var decorator = parent as DecoratorNode;
            if (decorator != null)
            {
                decorator.child = null;
                return;
            }

            var composite = parent as CompositeNode;
            if (composite != null)
            {
                composite.children.Remove(child);
                return;
            }
            
            var rootNode = parent as RootNode;
            if (rootNode != null)
            {
                rootNode.child = null;
                return;
            }
        }

        public List<Node> GetChildren(Node parent)
        {
            List<Node> children = new List<Node>();
            
            var composite = parent as CompositeNode;
            if (composite != null)
            {
                return composite.children;
            }
            
            var decorator = parent as DecoratorNode;
            if (decorator != null && decorator.child != null)
            {
                children.Add(decorator.child);
            }
            
            var rootNode = parent as RootNode;
            if (rootNode != null && rootNode.child != null)
            {
                children.Add(rootNode.child);
            }

            return children;
        }
    }
}
