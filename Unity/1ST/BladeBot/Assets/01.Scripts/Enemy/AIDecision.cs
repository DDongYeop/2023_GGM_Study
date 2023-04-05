using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class AIDecision : MonoBehaviour
{
    public bool IsReverse = false;
    protected AIActionData _aiActionData;
    protected EnemyController _enemyController;

    public virtual void SetUp(Transform enemyRoot)
    {
        _enemyController = enemyRoot.GetComponent<EnemyController>();
        _aiActionData = enemyRoot.Find("AI").GetComponent<AIActionData>();
    }

    public abstract bool MakeDecision();
}
