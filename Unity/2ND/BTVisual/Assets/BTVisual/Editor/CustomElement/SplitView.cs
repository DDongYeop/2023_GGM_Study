using UnityEngine.UIElements;

namespace BTVisual
{
    public class SplitView : TwoPaneSplitView // 화면 이분할 
    {
        public new class UxmlFactory : UxmlFactory<SplitView, UxmlTraits> { }
        public new class UxmlTraits : TwoPaneSplitView.UxmlTraits { }
        
    }
}
