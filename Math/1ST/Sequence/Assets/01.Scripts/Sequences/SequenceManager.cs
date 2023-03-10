using System;
using TMPro;
using UnityEngine;
using UnityEngine.Serialization;

namespace _01.Scripts.Sequences
{
    public class SequenceManager : MonoBehaviour
    {
        public static SequenceManager Instance;

        public float thisLevel;
        public float earlyMoney;
        public float upgradelevelMoney;

        [FormerlySerializedAs("Level")] [SerializeField] private TMP_InputField _level;
        [FormerlySerializedAs("Money")] [SerializeField] private TMP_InputField _money;
        [FormerlySerializedAs("UpgradeLevel")] [SerializeField] private TMP_InputField _upgradeMoney;
        private void Awake()
        {
            if (Instance == null)
                Instance = this;
            else 
                Destroy(this);
        }

        public void InputApply()
        {
            thisLevel = float.Parse(_level.text);
            earlyMoney = float.Parse(_money.text);
            upgradelevelMoney = float.Parse(_upgradeMoney.text);
        }
    }
}
