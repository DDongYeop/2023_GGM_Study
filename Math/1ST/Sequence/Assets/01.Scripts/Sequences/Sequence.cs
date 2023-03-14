using TMPro;
using UnityEngine;

namespace _01.Scripts.Sequences
{
    public class Sequence : MonoBehaviour
    {
        [SerializeField] private int _upgradeLevelIndex;
        [SerializeField] private TextMeshProUGUI _text;
        
        
        public void PriceUpdate(float earlyMoney, float money, float level)
        {
            _text.text = ((earlyMoney + (money * ((level + _upgradeLevelIndex - 1) - 1) + earlyMoney)) - (earlyMoney + (money * ((level - 1) - 1) + earlyMoney))).ToString();
        }
    }
}
