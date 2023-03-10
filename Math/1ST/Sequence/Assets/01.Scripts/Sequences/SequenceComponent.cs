using UnityEngine;

namespace _01.Scripts.Sequences
{
    public interface SequenceComponent
    {
        void PriceUpdate(float earlyMoney, float money, float level);
    }
}
