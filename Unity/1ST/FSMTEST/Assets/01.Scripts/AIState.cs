using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AIState : MonoBehaviour
{
    public List<AITransition> Transitions = null;

    protected AIBrain _brain;
    
    private void Awake()
    {
        _brain = transform.GetComponentInParent<AIBrain>();
        if (_brain == null)
            Debug.Log("뇌가 없어요 !!");
    }
    
    public void UpdateState()
    {
        // 여기서 원래 내 상태에서 해줘야 할 일을 수행해야함

        foreach (AITransition t in Transitions)
        {
            if (t.CheckTransision())
            {
                //여기서 상태전환을 해야한다 
                _brain.ChangeState(t.NextState);
                break;
            }
        }
    }
}
