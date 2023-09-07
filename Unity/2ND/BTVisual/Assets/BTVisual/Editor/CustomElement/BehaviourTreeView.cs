using UnityEditor.Experimental.GraphView;
using UnityEngine.UIElements;

namespace BTVisual
{
    public class BehaviourTreeView : GraphView
    {
        public new class UxmlFactory : UxmlFactory<BehaviourTreeView, UxmlTraits> { }
        public new class UxmlTraits : GraphView.UxmlTraits { }

        public BehaviourTreeView()
        {
            Insert(0, new GridBackground());
            
            //메뉴퓰레이터 (드래그이벤트 -> 마우스 다운 + 마우스 무브 + 마우스 업 이벤트)
            
            this.AddManipulator(new ContentZoomer()); //마우스 휠로 커졌다 작아졋다
            this.AddManipulator(new ContentDragger()); //마우스 휠버튼으로 왔다 갔다
            this.AddManipulator(new SelectionDragger()); // 잡고 옮기는 친구
            this.AddManipulator(new RectangleSelector()); // 네모 만들어서 선택할 수 있게 해주는 애
        }
    }
}