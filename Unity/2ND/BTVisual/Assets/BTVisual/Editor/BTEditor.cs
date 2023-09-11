using System;
using BTVisual;
using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;

public class BTEditor : EditorWindow
{
    [SerializeField] private VisualTreeAsset m_VisualTreeAsset = default;
    
    private BehaviourTreeView _treeView;
    private InspectorView _inspectorView;

    [MenuItem("Window/BTEditor")]
    public static void OpenWindow()
    {
        BTEditor wnd = GetWindow<BTEditor>();
        wnd.titleContent = new GUIContent("BTEditor");
    }

    public void CreateGUI()
    {
        VisualElement root = rootVisualElement;

        VisualElement template = m_VisualTreeAsset.Instantiate();
        template.style.flexGrow = 1;
        root.Add(template);

        var styleSheet = AssetDatabase.LoadAssetAtPath<StyleSheet>("Assets/BTVisual/Editor/BTEditor.uss");
        root.styleSheets.Add(styleSheet);

        _treeView = root.Q<BehaviourTreeView>("tree-view");
        _inspectorView = root.Q<InspectorView>("inspector-view");
        
        OnSelectionChange(); //강제로 호출해서 
    }

    private void OnSelectionChange()
    {
        var tree = Selection.activeObject as BehaviourTree;

        if (tree != null)
        {
            _treeView.PopulateView(tree);
        }
    }
}
