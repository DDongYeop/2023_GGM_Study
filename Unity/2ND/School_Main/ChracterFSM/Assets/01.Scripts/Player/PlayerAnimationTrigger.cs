using UnityEngine;

public class PlayerAnimationTrigger : MonoBehaviour
{
    private Player _player;

    private void Awake()
    {
        _player = transform.parent.GetComponent<Player>();
    }

    private void AnimationFinishTrigger()
    {
        _player.AnimationFinishTrigger();
    }
}
