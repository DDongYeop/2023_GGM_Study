using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class AIDecision : MonoBehaviour
{
    public bool IsReverse; //역결정
    protected AIBrain _brain;
    //결정을 내리기 위해서 필요한 다른 정보들

    public virtual void Setup(AIBrain brain)
    {
        _brain = brain;
    }

    public abstract bool MakeADecision(); //결정을 내리는 것
}
