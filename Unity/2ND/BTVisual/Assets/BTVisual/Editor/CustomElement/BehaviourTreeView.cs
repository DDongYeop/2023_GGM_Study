using System;
using UnityEditor;
using UnityEditor.Experimental.GraphView;
using UnityEngine;
using UnityEngine.UIElements;

namespace BTVisual
{
    public class BehaviourTreeView : GraphView
    {
        public new class UxmlFactory : UxmlFactory<BehaviourTreeView, UxmlTraits> { }
        public new class UxmlTraits : GraphView.UxmlTraits { }

        private BehaviourTree _tree;

        public BehaviourTreeView()
        {
            Insert(0, new GridBackground());

            //매뉴퓰레이터 (드래그이벤트 -> 마우스다운 + 마우스 무브 + 마우스 업 이벤트)

            this.AddManipulator(new ContentZoomer());
            this.AddManipulator(new ContentDragger());
            this.AddManipulator(new SelectionDragger());
            this.AddManipulator(new RectangleSelector());
        }

        public void PopulateView(BehaviourTree tree)
        {
            //DeleteElements(graphElements); //기존에 그려졌던 애들을 전부 삭제, 버그로 인해 주석처리. 
            _tree = tree;

            graphViewChanged -= OnGraphViewChanged; //이전 이벤트 제거하고
            graphViewChanged += OnGraphViewChanged; //다시 이벤트 구독
            
            _tree.nodes.ForEach(n => CreateNodeView(n));
        }

        private GraphViewChange OnGraphViewChanged(GraphViewChange graphViewChange)
        {
            if (graphViewChange.elementsToRemove != null)
            {
                graphViewChange.elementsToRemove.ForEach(elem =>
                {
                    var nv = elem as NodeView;
                    if (nv != null)
                    {
                        _tree.DeleteNode(nv.node); //실제 SO에서도 삭제해라 
                    }
                });
            }
            
            return graphViewChange;
        }

        private void CreateNodeView(Node n)
        {
            NodeView nv = new NodeView(n);
            AddElement(nv);
        }

        private void CreateNode(Type t)
        {
            Node node = _tree.CreateNode(t);
            CreateNodeView(node);
        }

        public override void BuildContextualMenu(ContextualMenuPopulateEvent evt)
        {
            {
                var types = TypeCache.GetTypesDerivedFrom<ActionNode>();
                foreach(var t in types)
                {
                    evt.menu.AppendAction($"[{t.BaseType.Name}] / {t.Name}", (a) => { CreateNode(t); });
                }
            }
            {
                var types = TypeCache.GetTypesDerivedFrom<CompositeNode>();
                foreach(var t in types)
                {
                    evt.menu.AppendAction($"[{t.BaseType.Name}] / {t.Name}", (a) => { CreateNode(t); });
                }
            }
            {
                var types = TypeCache.GetTypesDerivedFrom<DecoratorNode>();
                foreach(var t in types)
                {
                    evt.menu.AppendAction($"[{t.BaseType.Name}] / {t.Name}", (a) => { CreateNode(t); });
                }
            }
        }
    }
}