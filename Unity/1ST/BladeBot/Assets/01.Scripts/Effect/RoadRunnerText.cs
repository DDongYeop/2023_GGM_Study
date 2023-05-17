using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class TypeChar
{
    public bool IsComplete = false;

    private Vector3[] _originPos;
    private float _currentTime = 0;
    private float _delayTime = 0;
    private float _effectTime = 0;
    private int _startIndex;

    private Color _startColor;
    private Color _endColor;

    public TypeChar(int start, Vector3[] vertices, Color32[] colors, Color startColor, Color endColor, 
                        float delayTime, float effectTime = 0.5f, float offset = 15f)
    {
        _originPos = new Vector3[4];
        for(int i = 0; i < 4; ++i)
        {
            Vector3 point = vertices[start + i];  //이걸 하는 이유는 벡터3를 복사하기 위함.
            _originPos[i] = point;

            //로드러너 이펙트에 필요하도록 초반 셋팅
            if(i == 0 || i == 3)
            {
                vertices[start + i] = point + new Vector3(offset, 0, 0); //우측으로 오프셋만큼 더 간 곳
            }else
            {
                vertices[start + i] = point + new Vector3(offset + 0.25f, 0, 0); //우측으로 오프셋 + 0.25f간곳
            }

            colors[start + i].a = 0; //투명도만 0으로 변경
        }
        _delayTime = delayTime;
        _effectTime = effectTime;
        _startIndex = start;
        _startColor = startColor;
        _endColor = endColor;
    }

    public void UpdateMesh(Vector3[] vertices, Color32[] colors)
    {
        _currentTime += Time.deltaTime;
        if (_currentTime < _delayTime || IsComplete) return;
        //딜레이타임이 아직 안지났거나 완료된 이펙트라면 아무것도 하지 않는다.

        float time = _currentTime - _delayTime;
        float percent = time / _effectTime; 

        for(int i = 0; i < 4; i++)
        {
            vertices[_startIndex + i] = Vector3.Lerp(vertices[_startIndex + i], _originPos[i], percent);
            colors[_startIndex + i] = Color.Lerp(_startColor, _endColor, percent);
        }

        if(percent >= 1)
        {
            IsComplete = true;
        }
    }
}

public class RoadRunnerText : MonoBehaviour
{
    [SerializeField]
    private float _typeTime = 0.1f;
    [SerializeField]
    private Color _startColor, _endColor;

    private bool _isTyping = false;

    private TMP_Text _tmpText;

    private void Awake()
    {
        _tmpText = GetComponent<TMP_Text>();
    }

    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.A) && _isTyping == false)
        {
            _isTyping = true;
            StartEffect("This is GGM!! 조용히 해 김민수!");
        }
    }

    public void StartEffect(string text)
    {
        _tmpText.SetText(text);
        _tmpText.color = _endColor;
        _tmpText.ForceMeshUpdate();

        StartCoroutine(TypeText());
    }

    private IEnumerator TypeText()
    {
        List<TypeChar> charList = new List<TypeChar>();
        TMP_TextInfo textInfo = _tmpText.textInfo;
        Vector3[] vertices = textInfo.meshInfo[0].vertices;
        Color32[] colors = textInfo.meshInfo[0].colors32;

        for(int i = 0; i < textInfo.characterCount; i++)
        {
            TMP_CharacterInfo charInfo = textInfo.characterInfo[i];
            if (charInfo.isVisible == false) continue;
            charList.Add(
                new TypeChar(charInfo.vertexIndex, vertices, colors, 
                            _startColor, _endColor, 
                            i * _typeTime, _typeTime));
        }

        bool isAllComplete = false;
        
        while(isAllComplete == false)
        {
            yield return null;
            foreach(TypeChar t in charList)
            {
                t.UpdateMesh(vertices, colors);
                isAllComplete = t.IsComplete;
            }
            _tmpText.UpdateVertexData(TMP_VertexDataUpdateFlags.Vertices | TMP_VertexDataUpdateFlags.Colors32);
        }

        _isTyping = false;
    }
}
