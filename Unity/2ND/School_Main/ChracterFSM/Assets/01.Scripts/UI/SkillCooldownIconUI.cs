using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class SkillCooldownIconUI : MonoBehaviour
{
    [SerializeField] private PlayerSkill _skillType;
    [SerializeField] private Image _cooldownImage;
    [SerializeField] private TextMeshProUGUI _text;
    private bool _showText;

    private Skill _targetSkill;

    private void Start()
    {
        _targetSkill = SkillManager.Instance.GetSkill(_skillType);
        _cooldownImage.fillAmount = 0;
        _targetSkill.OnCooldown += HandleCoolDown;
    }

    private void HandleCoolDown(float current, float total)
    {
        _text.text = Math.Round(current, 1).ToString();
        _cooldownImage.fillAmount = current / total;
        if (current <= 0)
            _text.enabled = _showText = false;
        else
            _text.enabled = _showText = true;
    }

#if UNITY_EDITOR

    private void OnValidate()
    {
        if (_skillType != 0)
        {
            gameObject.name = $"SkillCooldownUI[{_skillType.ToString()}]";
        }
    }

#endif
}
