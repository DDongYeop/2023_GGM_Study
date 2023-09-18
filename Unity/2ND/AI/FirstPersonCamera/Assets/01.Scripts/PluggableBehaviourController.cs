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

    public Transform playerCamera;
    private Animator myAnimator;
    public Animator GetAnimator => myAnimator;
    private Rigidbody myRigidbody;
    public Rigidbody GetRigidbody => myRigidbody;
    private ShoulderViewCamera camScript;
    public ShoulderViewCamera GetCamScript => camScript;

    private Transform myTransform;
    private float h;
    public float GetH => h;
    private float v;
    public float GetV => v;
    public float turnSmoothing = 0.06f;

    private bool changeFOV;
    public float sprintFOV = 100;
    private Vector3 lastDirection;
    private bool sprint;
    private int hFloat;
    private int vFloat;
    private int groundedBool;
    private Vector3 colExtents;

    private void Awake()
    {
        behaviours = new List<BaseBehavior>();
        overrideBehaviours = new List<BaseBehavior>();

        myAnimator = GetComponent<Animator>();
        hFloat = Animator.StringToHash(AnimatorVarKey.Horizontal);
        vFloat = Animator.StringToHash(AnimatorVarKey.Vertical);

        camScript = playerCamera.GetComponent<ShoulderViewCamera>();
        myRigidbody = GetComponent<Rigidbody>();
        groundedBool = Animator.StringToHash(AnimatorVarKey.Grounded);
        colExtents = GetComponent<Collider>().bounds.extents;
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

    private void Update()
    {
        h = Input.GetAxis("Horizontal");
        v = Input.GetAxis("Vertical");
        
        myAnimator.SetFloat(hFloat, h, 0.1f, Time.deltaTime); 
        myAnimator.SetFloat(vFloat, v, 0.1f, Time.deltaTime);
        
        sprint = Input.GetButton(BtnName.Sprint);
        
        if (IsSprinting())
        {
            changeFOV = true; 
            camScript.SetFOV(sprintFOV);
        }
        else if (changeFOV)
        {
            camScript.ResetFOV();
            changeFOV = false;
        }
        myAnimator.SetBool (groundedBool, IsGrounded());
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

    public bool IsMoving()
    {
        return Mathf.Abs(h) > Mathf.Epsilon || Mathf.Abs(v) > Mathf.Epsilon;
    }

    public bool IsHorizontalMoving()
    {
        return Mathf.Abs(h) > Mathf.Epsilon;
    }

    public bool IsSprinting()
    {
        return sprint && IsMoving() && CanSprint();
    }

    public bool IsGrounded()
    {
        Ray ray = new Ray(myTransform.position + Vector3.up * 2 * colExtents.x, Vector3.down);
        return Physics.SphereCast(ray, colExtents.x, colExtents.x + 0.2f);
    }

    public bool CanSprint()
    {
        foreach (BaseBehavior behaviour in behaviours)
        {
            if (!behaviour.AllowSprint)
                return false;
        }
        foreach (BaseBehavior overrideBehaviour in overrideBehaviours)
        {
            if (!overrideBehaviour.AllowSprint)
                return false;
        }
        return true;
    }

    public void Repositioning()
    {
        if (lastDirection != Vector3.zero)
        {
            lastDirection.y = 0f;
            Quaternion targetRotation = Quaternion.LookRotation(lastDirection);
            Quaternion newRotation = Quaternion.Slerp(myRigidbody.rotation, targetRotation, turnSmoothing);
            myRigidbody.MoveRotation(newRotation);
        }
    }
}
