using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CrystalSkill : Skill
{
    [SerializeField] private CrystalSkillController _crystalPrefab;
    public float timeOut = 5f;

    private CrystalSkillController _currentCrystal;

    public int damage = 5;

    public bool canExplode;
    public float explosionRadius = 3f;

    public bool canMove;
    public float moveSpeed;
    public float findEnemyRadius = 10f;

    public override bool AttemptUseSkill()
    {
        if (_cooldownTimer <= 0 && _currentCrystal == null)
        {
            UseSkill();
            return true;
        }

        if (_currentCrystal != null)
        {
            //이미 소환한 크리스탈 있으면 해줄일을 여기에 적고
        }

        Debug.Log("Skill cooldown or locked");
        return true;
    }

    public override void UseSkill()
    {
        base.UseSkill();

        if (_currentCrystal == null)
        {
            CreateCrystal(_player.transform.position);
        }
    }

    public void UnlinkCrystal()
    {
        _cooldownTimer = _cooldown;
        _currentCrystal = null;
    }

    private void CreateCrystal(Vector3 pos)
    {
        _currentCrystal = Instantiate(_crystalPrefab, pos, Quaternion.identity);
        _currentCrystal.SetUpCrystal(this);
    }
}
