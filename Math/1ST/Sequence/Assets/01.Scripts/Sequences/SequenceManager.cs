using System;
using System.Collections.Generic;
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

        private List<Sequence> _sequence = new List<Sequence>();

        private void Awake()
        {
            if (Instance == null)
                Instance = this;
            else 
                Destroy(this);
        }

        private void Start()
        {
            _sequence.Add(GameObject.Find("Button (1)").GetComponent<Sequence>());
            _sequence.Add(GameObject.Find("Button (2)").GetComponent<Sequence>());
            _sequence.Add(GameObject.Find("Button (3)").GetComponent<Sequence>());
        }

        public void InputApply()
        {
            thisLevel = float.Parse(_level.text);
            earlyMoney = float.Parse(_money.text);
            upgradelevelMoney = float.Parse(_upgradeMoney.text);
                print(_sequence);
            foreach (var seq in _sequence)
            {
                seq.PriceUpdate(earlyMoney, upgradelevelMoney, thisLevel);
            }
        }
    }
}
