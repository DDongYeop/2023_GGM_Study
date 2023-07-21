using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu (fileName = "ColorDB")]
public class ColorSetSO : MonoBehaviour
{
    private Color _backgroundColor;
    private Color _textColor;
    private Sprite _backgroundImage;

    public Color BackgroundColor
    {
        get => _backgroundColor;
        set => _backgroundColor = value;
    }

    public Color TextColor
    {
        get => _textColor;
        set => _textColor = value;
    }

    public Sprite BackgroundImage
    {
        get => _backgroundImage;
        set => _backgroundImage = value;
    }
}
