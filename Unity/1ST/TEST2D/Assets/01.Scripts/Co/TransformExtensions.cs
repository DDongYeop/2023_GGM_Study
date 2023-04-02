using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class TransformExtensions
{
    public static bool IsInGround(this Transform trm, float delta)
    {
        return trm.position.y <= delta;
    }
}
