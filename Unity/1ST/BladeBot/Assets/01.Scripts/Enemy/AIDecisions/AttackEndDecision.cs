using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackEndDecision : AIDecision
{
    //리플렉션 FieldInfo 를 가져와서 멤버변수에 캐싱하는 작업을 해야해. 
    public override bool MakeADecision()
    {
        return _aiActionData.IsAttacking == false;
    }
}
