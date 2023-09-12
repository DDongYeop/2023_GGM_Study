using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PluggableBehaviourController : MonoBehaviour
{
    private List<BaseBehavior> behaviours;
    private List<BaseBehavior> overrideBehaviours;
    private int currentBehaviour;
    private int behaviourLocked;
    private int defaultBehaviour;
    public int GetDefaultBehaviour => defaultBehaviour;

    private void Awake()
    {
        behaviours = new List<BaseBehavior>();
        overrideBehaviours = new List<BaseBehavior>();
    }

    private void FixedUpdate()
    {
        bool isAnyBehaviourActive = false;
        if (behaviourLocked > 0 || overrideBehaviours.Count == 0)
        {
            foreach (var behaviour in behaviours)
            {
                if (behaviour.isActiveAndEnabled && currentBehaviour == behaviour.GetBehaviourCode)
                {
                    isAnyBehaviourActive = true;
                    behaviour.LocalFixedUpdate();
                }
            }
        }
        else
        {
            foreach (var behaviour in overrideBehaviours)
            {
                behaviour.LocalFixedUpdate();
            }
        }
    }

    private void LateUpdate()
    {
        if (behaviourLocked > 0 || overrideBehaviours.Count == 0)
        {
            foreach (var behaviour in behaviours)
            {
                if (behaviour.isActiveAndEnabled && currentBehaviour == behaviour.GetBehaviourCode)
                    behaviour.LocalLateUpdate();
            }
        }
        else
        {
            foreach (var behaviour in overrideBehaviours)
                behaviour.LocalLateUpdate();
        }
    }

    public void SubscribeBehaviour(BaseBehavior behaviour)
    {
        behaviours.Add(behaviour);
    }

    public void RegisterDefaultBehaviour(int behaviourCode)
    {
        defaultBehaviour = behaviourCode;
        currentBehaviour = behaviourCode;
    }

    public void RegisterBehaviour(int behaviourCode)
    {
        if (currentBehaviour == defaultBehaviour)
            currentBehaviour = behaviourCode;
    }

    public void UnRegisterBehaviour(int behaviourCode)
    {
        if (currentBehaviour == behaviourCode)
            currentBehaviour = defaultBehaviour;
    }

    public bool OverrideWithBehaviour(BaseBehavior behaviour)
    {
        if (!overrideBehaviours.Contains(behaviour))
        {
            if (overrideBehaviours.Count == 0)
            {
                foreach (var behavior1 in behaviours)
                {
                    if (behavior1.isActiveAndEnabled && currentBehaviour == behavior1.GetBehaviourCode)
                    {
                        behavior1.OnOverride();
                        break;
                    }
                }
            }
            overrideBehaviours.Add(behaviour);
            return true;
        }
        return false;
    }

    public bool RevokeOverridingBehaviour(BaseBehavior behaviour)
    {
        if (overrideBehaviours.Contains(behaviour))
        {
            overrideBehaviours.Remove(behaviour);
            return true;
        }
        return false;
    }

    public bool IsOverriding(BaseBehavior behavior = null)
    {
        if (behavior == null)
            return overrideBehaviours.Count > 0;
        return overrideBehaviours.Contains(behavior);
    }

    public bool IsCurrentBehaviour(int behaviourCode)
    {
        return currentBehaviour == behaviourCode;
    }

    public bool GetTempLockStatus(int behaviourCode = 0)
    {
        return (behaviourLocked != 0 && behaviourLocked != behaviourCode);
    }

    public void LockTempBehaviour(int behaviourCode)
    {
        if (behaviourLocked == 0)
            behaviourLocked = behaviourCode;
    }

    public void UnLockTempBehaviour(int behaviourCode)
    {
        if (behaviourLocked == behaviourCode)
            behaviourLocked = 0;
    }

    public Vector3 GetLastDirection()
    {
        //return lastDirection;
        return Vector3.zero;
    }

    public void SetLastDirection(Vector3 direction)
    {
        //lastDirection = direction;
    }
}
