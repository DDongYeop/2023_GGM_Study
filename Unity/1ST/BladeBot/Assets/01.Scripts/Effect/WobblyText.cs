using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class WobblyText : MonoBehaviour
{
    private TMP_Text _tmpText;

    private void Awake()
    {
        _tmpText = GetComponent<TMP_Text>();
    }

    private void Update()
    {
        _tmpText.ForceMeshUpdate();

        TMP_TextInfo textInfo = _tmpText.textInfo;

        for (int i = 0; i < textInfo.characterCount; i++)
        {
            TMP_CharacterInfo cInfo = textInfo.characterInfo[i];

            if (cInfo.isVisible == false)
                continue;

            Vector3[] vertices = textInfo.meshInfo[cInfo.materialReferenceIndex].vertices;

            int vIndex0 = cInfo.vertexIndex;
            for (int j = 0; j < 4; j++)
            {
                if (j == 1 || j == 2)
                {
                    Vector3 origin = vertices[vIndex0 + j];
                    vertices[vIndex0 + j] = origin + new Vector3(0, Mathf.Sin(Time.time * 2f + origin.x), 0);
                }
            }
        }

        /*var meshInfo = textInfo.meshInfo[0];
        meshInfo.mesh.vertices = meshInfo.vertices;
        _tmpText.UpdateGeometry(meshInfo.mesh, 0);*/
        _tmpText.UpdateVertexData();
    }
}
