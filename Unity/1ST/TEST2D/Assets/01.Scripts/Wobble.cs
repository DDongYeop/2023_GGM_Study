using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Wobble : MonoBehaviour
{
    private TMP_Text _tmpText;

    private void Awake()
    {
        _tmpText = GetComponent<TMP_Text>();
    }

    private void Update() 
    {
        _tmpText.ForceMeshUpdate(); //강제적으로 현재 텍스트에 맞게 메시 정보 업데이트

        TMP_TextInfo textInfo = _tmpText.textInfo; //문제 정보 넘어옴
        
        for (int i = 0; i < textInfo.characterCount; ++i)
        {
            TMP_CharacterInfo charInfo = textInfo.characterInfo[i];
            if (charInfo.isVisible == false) //띄어쓰기 같은건 매쉬없음
                continue;
            Vector3[] vertices = textInfo.meshInfo[charInfo.materialReferenceIndex].vertices;
            Color32[] colors = textInfo.meshInfo[charInfo.materialReferenceIndex].colors32;
            int vIndex0 = charInfo.vertexIndex;
            
            
            for (int j = 0; j < 4; ++j)
            {
                Vector3 origin = vertices[vIndex0 + j];
                vertices[vIndex0 + j] = origin + new Vector3(0, Mathf.Sin(Time.time * 2f + origin.x), 0);
            }
        }
        
        _tmpText.UpdateVertexData(TMP_VertexDataUpdateFlags.Colors32 | TMP_VertexDataUpdateFlags.Vertices);
        
        for (int i = 0; i < textInfo.meshInfo.Length; ++i)
        {
            var meshInfo = textInfo.meshInfo[i];
            meshInfo.mesh.vertices = meshInfo.vertices;
            
            _tmpText.UpdateGeometry(meshInfo.mesh, i);
        }
    }
}
