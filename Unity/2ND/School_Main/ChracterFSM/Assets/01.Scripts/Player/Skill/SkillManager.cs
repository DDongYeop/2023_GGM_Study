using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum PlayerSkill
{
    Dash = 1,
    Clone = 2,
    //Crystal = 3
}

public class SkillManager : MonoSingleton<SkillManager>
{
    private Dictionary<Type, Skill> _skills;
    private Dictionary<PlayerSkill, Type> _skillTypes;

    private void Awake()
    {
        _skills = new Dictionary<Type, Skill>();
        _skillTypes = new Dictionary<PlayerSkill, Type>();

        foreach(PlayerSkill skill in Enum.GetValues(typeof(PlayerSkill)))
        {
            Skill skillCompo = GetComponent($"{skill.ToString()}Skill") as Skill;
            if (skillCompo != null)
            {
                Type skillType = skillCompo.GetType(); //타입을 뽑아오고
                _skills.Add(skillType, skillCompo);
                _skillTypes.Add(skill, skillType);
            }
        }
    }

    public T GetSkill<T>() where T : Skill
    {
        Type t = typeof(T);
        if(_skills.TryGetValue(t, out Skill targetSkill))
        {
            return targetSkill as T;
        }
        return null;
    }

    public Skill GetSkill(PlayerSkill enumType)
    {
        Type t = _skillTypes[enumType];
        if (_skills.TryGetValue(t, out Skill targetSkill))
        {
            return targetSkill;
        }
        return null;
    }


    public void UseSkillFeedback(PlayerSkill skillType)
    {
     
    }
}
