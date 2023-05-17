using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class EnemyHPBar
{
    private VisualElement _barParent;
    private VisualElement _bar;
    private Label _hpLabel;
    private Label _nameLabel;

    private int _currentHP;
    public int HP
    {
        set
        {
            _currentHP = value;
            UpdateHPText();
        }
    }

    private int _maxHP;
    public int MaxHP
    {
        set
        {
            _maxHP = value;
            UpdateHPText();
        }
    }

    public string EnemyName
    {
        set
        {
            _nameLabel.text = $"{value}";
        }
    }
    
    private void UpdateHPText()
    {
        _hpLabel.text = $"{_currentHP} / {_maxHP}";
        _bar.transform.scale = new Vector3((float)_currentHP / _maxHP, 1, 0);
    }

    public void ShowBar(bool value)
    {
        if(value)
        {
            _barParent.AddToClassList("on");
        }else
        {
            _barParent.RemoveFromClassList("on");
        }
    }

    public EnemyHPBar (VisualElement root)
    {
        _barParent = root;
        _bar = _barParent.Q<VisualElement>("Bar");
        _nameLabel = _barParent.Q<Label>("EnemyName");
        _hpLabel = _barParent.Q<Label>("HPText");
    }
}
