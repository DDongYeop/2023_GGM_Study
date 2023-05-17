public class CheckHitDecision : AIDecision
{
    public override bool MakeADecision()
    {
        return _aiActionData.IsHit;
    }
}
