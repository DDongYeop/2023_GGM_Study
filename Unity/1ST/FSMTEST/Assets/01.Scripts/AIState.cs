using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AIState : MonoBehaviour
{
    public List<AITransition> Transitions = null;
    public List<AIAction> Actions = null;
    
    protected AIBrain _brain;
    
    private void Awake()
    {
        _brain = transform.GetComponentInParent<AIBrain>();
        if (_brain == null)
            Debug.Log("뇌가 없어요 !!");

        Actions = new List<AIAction>();
        GetComponents<AIAction>(Actions); // 자기에 붙어있는 모든 엑션 찾아 넣기
    }
    
    public void UpdateState()
    {
        // 여기서 원래 내 상태에서 해줘야 할 일을 수행해야함

        foreach (AIAction a in Actions)
        {
            a.TakeAction();
        }
        
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
