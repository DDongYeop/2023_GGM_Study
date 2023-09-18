using UnityEngine;

public class BaseBehavior : MonoBehaviour
{
    protected PluggableBehaviourController behaviourController;
    protected int behaviourCode;
    public int GetBehaviourCode => behaviourCode;
    public bool AllowSprint;

    private void Awake()
    {
        this.behaviourController = GetComponent<PluggableBehaviourController>();
        behaviourCode = this.GetType().GetHashCode();
    }

    public virtual void LocalLateUpdate() {}
    public virtual void LocalFixedUpdate() {}
    public virtual void OnOverride() {}
}
