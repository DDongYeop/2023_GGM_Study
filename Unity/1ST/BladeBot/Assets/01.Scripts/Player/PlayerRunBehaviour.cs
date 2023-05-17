using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerRunBehaviour : StateMachineBehaviour
{
    private PlayerVFXManager _vfxManager = null;

    public override void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        if(_vfxManager == null)
        {
            _vfxManager = animator.transform.parent.GetComponent<PlayerVFXManager>();
        }
        _vfxManager?.UpdateFootStep(true);
    }

    public override void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        _vfxManager?.UpdateFootStep(false);
    }
}
