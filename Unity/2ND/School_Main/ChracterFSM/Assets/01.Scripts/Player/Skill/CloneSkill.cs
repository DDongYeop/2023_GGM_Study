using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CloneSkill : Skill
{
    [Header("Clone Info")] 
    [SerializeField] private CloneSkillController _clonePrefab;
    [SerializeField] private bool _createCloneOnDashStart;
    [SerializeField] private bool _createCloneOnDashEnd;
    [SerializeField] private bool _createCloneOnCounterAttack; //그냥 만들어만 두기

    public float cloneDuration;
    public float findEnemyRadius = 5f; //적을 찾아서 적 방향으로 회전

    public void CreateClone(Transform originTrm, Vector3 offset)
    {
        CloneSkillController newClone = Instantiate(_clonePrefab);
        newClone.SetUpClone(this, originTrm, offset);
    }

    public void CreateCloneOnDashEnd()
    {
        if (_createCloneOnDashEnd)
            CreateClone(_player.transform, Vector3.zero);
    }
}
