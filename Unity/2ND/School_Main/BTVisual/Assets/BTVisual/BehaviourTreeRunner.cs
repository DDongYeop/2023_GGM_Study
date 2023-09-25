using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;

namespace BTVisual
{
    public class BehaviourTreeRunner : MonoBehaviour
    {
        public BehaviourTree tree;
        private EnemyBrain _brain;

        private void Awake()
        {
            _brain = GetComponent<EnemyBrain>();
        }

        private void Start()
        {
            tree = tree.Clone();
            tree.Bind(_brain); //이순간에 클론노드 전체에 블랙보드 복사가 된다
        }


        private void Update()
        {
            tree.Update();
        }
    }
}
