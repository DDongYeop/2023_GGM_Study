using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class GameItemManager : MonoBehaviour
{
    [SerializeField] private GameItemSO _gameItem;

    private UIDocument _uiDocument;
    private VisualElement _root;

    private void Awake()
    {
        _uiDocument = GetComponent<UIDocument>();
    }

    private void OnEnable()
    {
        _root = _uiDocument.rootVisualElement;

        VisualElement image = _root.Q<VisualElement>("Icon");
        image.style.backgroundImage = new StyleBackground(Background.FromSprite(_gameItem.icon));

        Label name = _root.Q<Label>("Name");
        name.text = "Name : " + _gameItem.name;

        Label type = _root.Q<Label>("Type");
        type.text = "Type : " + _gameItem.type;
        
        Label price = _root.Q<Label>("Price");
        price.text = "Price : " + _gameItem.price;
    }
}
