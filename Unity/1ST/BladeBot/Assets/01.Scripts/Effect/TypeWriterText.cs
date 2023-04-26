using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class TypeWriterText : MonoBehaviour
{
    [SerializeField] private float _typeTime = 0.3f;
    [SerializeField] private Color _startColor, _endColor;
    private TMP_Text _tmpText;
    private int _tIndex = 0;
    private bool _isTyping = false;

        private void Awake()
    {
        _tmpText = GetComponent<TMP_Text>();
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.A) && _isTyping == false)
        {
            _isTyping = true;
            StartEffect("Hello GGM! This is game!");
        }
        else if (Input.GetKeyDown(KeyCode.A) && _isTyping)
        {
            StopAllCoroutines();
        }
    }

    public void StartEffect(string text)
    {
        _tmpText.SetText(text);
        _tmpText.color = _endColor;
        _tmpText.ForceMeshUpdate();

        _tIndex = 0;
        _tmpText.maxVisibleCharacters = 0; //아무 글자도 안보여

        StartCoroutine(TypeText());
    }

    private IEnumerator TypeText()
    {
        TMP_TextInfo textInfo = _tmpText.textInfo;
        for(int i = 0; i < textInfo.characterCount; i++)
        {
            yield return StartCoroutine(TypeOneCharacter(textInfo));
        }
        _isTyping = false;
    }


    private IEnumerator TypeOneCharacter(TMP_TextInfo textInfo)
    {
        _tmpText.maxVisibleCharacters = _tIndex + 1;
        _tmpText.ForceMeshUpdate();

        TMP_CharacterInfo charInfo = textInfo.characterInfo[_tIndex];

        if(charInfo.isVisible == false)
        {
            yield return new WaitForSeconds(_typeTime);
        }
        else
        {
            //여기가 공백이 아닐 때 건드린다.
            Vector3[] vertices = textInfo.meshInfo[charInfo.materialReferenceIndex].vertices;
            Color32[] vertexColors = textInfo.meshInfo[charInfo.materialReferenceIndex].colors32;
            //우리가 유니티에서 사용하는 Color변수는 float로 0~1까지 값을 받는거고
            // Color32이는 0~255까지의 1바이트 값을 받는 녀석이다.

            int vIndex0 = charInfo.vertexIndex;
            int vIndex1 = vIndex0 + 1;
            int vIndex2 = vIndex0 + 2;
            int vIndex3 = vIndex0 + 3;

            Vector3 v1Origin = vertices[vIndex1];
            Vector3 v2Origin = vertices[vIndex2];

            float currentTime = 0;
            float percent = 0;

            while(percent < 1)
            {
                currentTime += Time.deltaTime;
                percent = currentTime / _typeTime;
                float yDelta = Mathf.Lerp(2f, 0, percent);

                vertices[vIndex1] = v1Origin + new Vector3(0, yDelta, 0);
                vertices[vIndex2] = v2Origin + new Vector3(0, yDelta, 0);

                for (int i = 0; i < 4; i++)
                {
                    vertexColors[vIndex0 + i] = Color.Lerp(_startColor, _endColor, percent);
                }
                
                _tmpText.UpdateVertexData();
                yield return null;
            }

            vertices[vIndex1] = v1Origin;
            vertices[vIndex2] = v2Origin;

            _tmpText.UpdateVertexData(TMP_VertexDataUpdateFlags.Vertices | TMP_VertexDataUpdateFlags.Colors32);
        }
        _tIndex++;
    }

}
