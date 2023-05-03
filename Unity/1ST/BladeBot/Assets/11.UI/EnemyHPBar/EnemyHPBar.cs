using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class EnemyHPBar
{
    private VisualElement _barParnet;
    private VisualElement _bar;
    private Label _hpLabel;
    private Label _nameLabel;

    private int _currentHP;
    public int HP
    {
        set
        {
            _currentHP = value;
            UpdateHpText();
        }
    }
    
    private int _maxHP;
    public int MaxHP
    {
        set
        {
            _maxHP = value;
            UpdateHpText();
        }
    }

    public string EnemyName
    {
        set
        {
            _nameLabel.text = $"{value}";
        }
    }
    
    private void UpdateHpText()
    {
        _hpLabel.text = $"{_currentHP} / {_maxHP}";
        _bar.transform.scale = new Vector3((float)_currentHP / _maxHP, 1, 0);
    }

    public void ShowBar(bool value)
    {
        if (value)
        {
            _barParnet.AddToClassList("on");
        }
        else
        {
            _barParnet.RemoveFromClassList("on");
        }
    }

    public EnemyHPBar(VisualElement root)
    {
        _barParnet = root;
        _bar = _barParnet.Q<VisualElement>("Bar");
        _nameLabel = _barParnet.Q<Label>("EnemyName");
        _hpLabel = _barParnet.Q<Label>("HPText");
    }
}
