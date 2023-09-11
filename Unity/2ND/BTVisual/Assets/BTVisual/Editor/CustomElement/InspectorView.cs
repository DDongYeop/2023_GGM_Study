using UnityEditor;
using UnityEngine.UIElements;

namespace BTVisual
{
    public class InspectorView : VisualElement
    {
        public new class UxmlFactory : UxmlFactory<InspectorView, UxmlTraits> { }
        public new class UxmlTraits : VisualElement.UxmlTraits { }

        private Editor _editor;
        
        public InspectorView()
        {
            
        }

        public void UpdateSelection(NodeView nv)
        {
            Clear(); //인스펙터뷰에 있느 ㄴ모든 UI툴킷을 전부 삭제 
            
            UnityEngine.Object.DestroyImmediate(_editor);
            _editor = Editor.CreateEditor(nv.node); //유니티 기본 인스펙터뷰 만들어줌

            var container = new IMGUIContainer(() => _editor.OnInspectorGUI()); //엔진 공부 하려면 "IMGUI"배워라 
            
            Add(container);
        }
    }
}
