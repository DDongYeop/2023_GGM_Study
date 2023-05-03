using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;
using UnityEngine.UIElements;

public class UIManager : MonoBehaviour
{
    public static UIManager Instance;

    private UIDocument _uiDocument;
    private VisualElement _root;

    private EnemyHPBar _enemyHPBar;

    [SerializeField] private float _enemyBarTimer = 4f;
    [SerializeField] private float _currentEnemyBarTimer = 0f;

    private EnemyHealth _subscibedEnemy = null;
    
    private void Awake()
    {
        if (Instance != null)
            Debug.LogError("Multiple UIManager is running");
        Instance = this;
        _uiDocument = GetComponent<UIDocument>();
    }

    private void OnEnable()
    {
        _root = _uiDocument.rootVisualElement;
        VisualElement _hpBarRoot = _root.Q("HPBarRect");
        _enemyHPBar = new EnemyHPBar(_hpBarRoot); //이 클래스가 HPBar랑 1:1로 데이터 바인딩된다. 
    }

    public void Subscribe(EnemyHealth health)
    {
        if (_currentEnemyBarTimer <= 0)
        {
            _enemyHPBar.ShowBar(true);
        }

        if (_subscibedEnemy != health)
        {
            if (_subscibedEnemy != null)
            {
                _subscibedEnemy.OnHealthCchanged -= UpdateEnemyHPData;
            }

            _subscibedEnemy = health;
            _subscibedEnemy.OnHealthCchanged += UpdateEnemyHPData;

            _enemyHPBar.EnemyName = health.gameObject.name; //적의 고유 이름이 있다면
            _enemyHPBar.MaxHP = _subscibedEnemy.MaxHP;
        }
    }

    private void UpdateEnemyHPData(int current, int max)
    {
        _enemyHPBar.HP = current;
        _currentEnemyBarTimer = _enemyBarTimer;
    }

    private void Update()
    {
        if (_currentEnemyBarTimer > 0)
        {
            _currentEnemyBarTimer -= Time.deltaTime;
            if (_currentEnemyBarTimer <= 0)
                _enemyHPBar.ShowBar(false);
        }
    }
}
