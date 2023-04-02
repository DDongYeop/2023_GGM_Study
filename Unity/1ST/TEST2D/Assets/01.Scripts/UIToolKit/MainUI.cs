using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class MainUI : MonoBehaviour
{
    private UIDocument _document;

    private void OnEnable()
    {
        _document = GetComponent<UIDocument>();
        VisualElement root = _document.rootVisualElement;

        Button btn = root.Q<Button>("BtnClick");
        btn.RegisterCallback<ClickEvent>(e =>
        {
            Debug.Log("버튼 클릭");
            btn.style.backgroundColor = Random.ColorHSV();
        });
    }
}
