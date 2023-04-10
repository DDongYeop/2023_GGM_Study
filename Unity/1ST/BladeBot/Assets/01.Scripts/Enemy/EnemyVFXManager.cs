using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VFX;

public class EnemyVFXManager : MonoBehaviour
{
    [SerializeField] private VisualEffect _footSteop;

    public void PlayerFootStep()
    {
        _footSteop.Play();
    }
}
