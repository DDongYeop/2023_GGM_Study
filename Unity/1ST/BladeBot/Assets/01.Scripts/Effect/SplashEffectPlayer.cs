using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VFX;

public class SplashEffectPlayer : EffectPlayer
{
    private readonly int _deltaYNameHash = Shader.PropertyToID("YDelta");
    private readonly int _colorNameHash = Shader.PropertyToID("COLOR");
    private readonly int _hitNormalHash = Shader.PropertyToID("HitNormal");

    public void SetData(Color color, float yDelta, Vector3 hitNormal)
    {
        foreach(VisualEffect ve in _effects)
        {
            ve.SetFloat(_deltaYNameHash, yDelta);
            ve.SetVector4(_colorNameHash, color);
            ve.SetVector3(_hitNormalHash, hitNormal);
        }
    }
}
