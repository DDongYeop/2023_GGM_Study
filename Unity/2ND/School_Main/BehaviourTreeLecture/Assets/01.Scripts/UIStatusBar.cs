using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;
using Random = UnityEngine.Random;

public class UIStatusBar : MonoBehaviour
{
    private UIDocument _uiDocument;
    private VisualElement _panelElement;
    private DialogPanel _dialogPanel;
    private BulletUI _bulletUI;

    private bool _isOn = false;
    public bool IsOn
    {
        get => _isOn;
        set
        {
            _dialogPanel.Show(value);
            _isOn = value;
        }
    }

    public string DialogText
    {
        get => _dialogPanel.Text;
        set => _dialogPanel.Text = value;
    }

    private Camera _mainCam;

    private void Awake()
    {
        _uiDocument = GetComponent<UIDocument>();
        _mainCam = Camera.main;
    }

    private void OnEnable()
    {
        _panelElement = _uiDocument.rootVisualElement.Q("PanelContainer");
        _dialogPanel = new DialogPanel(_panelElement, "");

        var bulletContiner = _uiDocument.rootVisualElement.Q("BulletContainer");
        _bulletUI = new BulletUI(bulletContiner, 8);
    }

    public void LookToCamera()
    {
        Vector3 dir = (transform.position - _mainCam.transform.position);
        transform.rotation = Quaternion.LookRotation(dir.normalized);
    }

    public void SetBulletCount(int count)
    {
        _bulletUI.Bulletcount = count;
    }

    /*
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            SetBulletCount(Random.Range(0, 9));
        }

        if (Input.GetKeyDown(KeyCode.W))
        {
            _dialogPanel.Text = $"Hello {Random.Range(0, 999)}";
        }
    }
    */
}
