using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class AIAction : MonoBehaviour
{
    protected AIBrain _brain;

    public virtual void SetUp(AIBrain brain)
    {
        _brain = brain;
    }

    public abstract void TakeAction(); //이건 추상매서드
}
