using System;
using BTVisual;
using UnityEditor;
using UnityEditor.Callbacks;
using UnityEngine;
using UnityEngine.UIElements;

public class BTEditor : EditorWindow
{
    [SerializeField] private VisualTreeAsset m_VisualTreeAsset = default;
    
    private BehaviourTreeView _treeView;
    private InspectorView _inspectorView;

    private IMGUIContainer _blackboardView;
    private SerializedObject _treeObject;
    private SerializedProperty _blackboardProp;

    [MenuItem("Window/BTEditor")]
    public static void OpenWindow()
    {
        BTEditor wnd = GetWindow<BTEditor>();
        wnd.titleContent = new GUIContent("BTEditor");
    }

    [OnOpenAsset]
    public static bool OnOpenAsset(int instanceId, int line)
    {
        if (Selection.activeObject is BehaviourTree)
        {
            OpenWindow();
            return true;
        }
        return false;
    }

    private void OnEnable()
    {
        EditorApplication.playModeStateChanged -= OnPlayModeStateChanged;
        EditorApplication.playModeStateChanged += OnPlayModeStateChanged;
    }

    private void OnDisable()
    {
        EditorApplication.playModeStateChanged -= OnPlayModeStateChanged;
    }

    private void OnPlayModeStateChanged(PlayModeStateChange state)
    {
        switch (state)
        {
            case PlayModeStateChange.EnteredEditMode:
                OnSelectionChange();
                break;
            case PlayModeStateChange.ExitingEditMode:
                break;
            case PlayModeStateChange.EnteredPlayMode:
                OnSelectionChange(); 
                break;
            case PlayModeStateChange.ExitingPlayMode:
                break;
        }
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
        _blackboardView = root.Q<IMGUIContainer>("blackboard");
        _blackboardView.onGUIHandler = () =>
        {
            if (_treeObject != null && _treeObject.targetObject != null)
            {
                _treeObject.Update(); //갱신
                EditorGUILayout.PropertyField(_blackboardProp);
                _treeObject.ApplyModifiedProperties(); //이걸 해줘야 원본 데이터도 수정됨.
            }
        };

        _treeView.OnNodeSelected += OnSelectionNodeChanged;
        
        OnSelectionChange(); //강제로 호출해서 
    }

    private void OnSelectionNodeChanged(NodeView nv)
    {
        _inspectorView.UpdateSelection(nv);
    }

    private void OnSelectionChange()
    {
        var tree = Selection.activeObject as BehaviourTree;

        if (tree == null) //만약 선택된게 BT는 아니였지만 GameObj라면 다르게 동작
        {
            if (Selection.activeGameObject) //선택된게 겜오브제
            {
                var runner = Selection.activeGameObject.GetComponent<BehaviourTreeRunner>();
                if (runner != null)
                    tree = runner.tree; //구동중인 러너 넣기
            }
        }

        if (Application.isPlaying)
        {
            if (tree != null)
            {
                _treeView?.PopulateView(tree);
            }
        }
        else
        {
            if (tree != null && AssetDatabase.CanOpenAssetInEditor(tree.GetInstanceID()))
            {
                _treeView.PopulateView(tree);
            }
        }

        if (tree != null)
        {
            _treeObject = new SerializedObject(tree);
            Debug.Log(_treeObject);
            _blackboardProp = _treeObject.FindProperty("blackboard"); //트리의 멤버변수 가져온다
            Debug.Log(_blackboardProp);
        }
    }

    private void OnInspectorUpdate()
    {
        _treeView?.UpdateNodeState();
    }
}
