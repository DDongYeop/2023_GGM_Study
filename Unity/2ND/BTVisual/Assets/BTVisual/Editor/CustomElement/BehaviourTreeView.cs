using System;
using System.Collections.Generic;
using System.Linq;
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

        public Action<NodeView> OnNodeSelected;

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
            _tree = tree;
            graphViewChanged -= OnGraphViewChanged; //이전 이벤트 제거하고

            DeleteElements(graphElements); //기존에 그려졌던 애들을 전부 삭제, 버그로 인해 주석처리. 
            
            graphViewChanged += OnGraphViewChanged; //다시 이벤트 구독

            if (_tree.rootNode == null)
            {
                _tree.rootNode = CreateNode(typeof(RootNode)) as RootNode;
                EditorUtility.SetDirty(_tree);
                AssetDatabase.SaveAssets();
            }
            
            tree.nodes.ForEach(n => CreateNodeView(n));
            
            tree.nodes.ForEach(n =>
            {
                var children = tree.GetChildren(n); //n의 자식을 가져온다
                NodeView parent = FindNodeView(n);
                children.ForEach(c =>
                {
                    NodeView child = FindNodeView(c); //해당자식 가져온다
                    Edge edge = parent.output.ConnectTo(child.input);
                    AddElement(edge);
                });
            });
        }

        //guid로 노드 엘레멘트 가져온다
        private NodeView FindNodeView(Node node)
        {
            return GetNodeByGuid(node.guid) as NodeView;
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

                    var edge = elem as Edge;
                    if (edge != null) //연결선이 삭제된거다
                    {
                        NodeView parent = edge.output.node as NodeView;
                        NodeView child = edge.input.node as NodeView; //자식 가져오기
                    
                        _tree.RemoveChild(parent.node, child.node);                        
                    }
                });
            }

            if (graphViewChange.edgesToCreate != null)
            {
                graphViewChange.edgesToCreate.ForEach(edge =>
                {
                    NodeView parent = edge.output.node as NodeView;
                    NodeView child = edge.input.node as NodeView; //자식 가져오기
                    
                    _tree.AddChild(parent.node, child.node);
                });
            }
            
            return graphViewChange;
        }

        private void CreateNodeView(Node n)
        {
            NodeView nv = new NodeView(n);
            nv.OnNodeSelected = OnNodeSelected;
            AddElement(nv);
        }

        private Node CreateNode(Type t)
        {
            Node node = _tree.CreateNode(t);
            CreateNodeView(node);
            return node;
        }

        public override void BuildContextualMenu(ContextualMenuPopulateEvent evt)
        {
            if (_tree == null && AssetDatabase.CanOpenAssetInEditor(_tree.GetInstanceID())) 
            {
                evt.StopPropagation(); //이벤트 전파금지 걸고
                return;
            }
            
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
        
        //드레깅이 시작될떄 연결가능한 포트를 가져오는 함수 
        public override List<Port> GetCompatiblePorts(Port startPort, NodeAdapter nodeAdapter)
        {
            //ToList 두번쓰는 미친짓은 하지마라. 특히 게임에서. 
            return ports.ToList()
                .Where(x => x.direction != startPort.direction && x.node != startPort.node)
                .ToList();
        }
    }
}
