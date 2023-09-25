using BTVisual;
using UnityEngine;

public class ChaseNode : ActionNode
{
    public float chaseSpeed;
    public float thresholdDistance;
    public float findTime;
    public float range;

    private float _currentFindTime;

    protected override void OnStart()
    {
        _currentFindTime = 0;
        brain.NavAgent.speed = chaseSpeed;
        brain.NavAgent.isStopped = false;
        brain.NavAgent.destination = blackboard.enemySpotPosition;
    }

    protected override void OnStop()
    {
        
    }

    protected override State OnUpdate()
    {
        if(brain.NavAgent.remainingDistance <= thresholdDistance)
        {
            brain.NavAgent.isStopped = true;
            return State.SUCCESS;
        }

        _currentFindTime += Time.deltaTime;
        if(_currentFindTime >= findTime)
        {
            Collider[] targets = new Collider[1];
            int cnt = Physics.OverlapSphereNonAlloc(brain.transform.position, range, targets, blackboard.whatIsEnemy);
            
            if (cnt >= 1)
            {
                blackboard.enemySpotPosition = targets[0].transform.position;
                brain.NavAgent.destination = blackboard.enemySpotPosition;
            }else
            {
                return State.FAILURE;
            }
            _currentFindTime = 0;
        }
        
        return State.RUNNING;
    }
}