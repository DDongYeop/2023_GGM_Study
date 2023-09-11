using UnityEngine;

public class CharacterPluggableBehavior : MonoBehaviour
{
    private BaseBehavior nowBehavior;

    private void Update()
    {
        if (nowBehavior != null)
        {
            nowBehavior.Execute();
        }
    }

    public void ChangeBehavior(BaseBehavior newBehavior, bool prioritize = false)
    {
        if (prioritize || nowBehavior != newBehavior)
            nowBehavior = newBehavior;
    }
}