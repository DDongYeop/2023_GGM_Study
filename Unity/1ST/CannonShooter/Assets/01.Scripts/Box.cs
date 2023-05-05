using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class Box : MonoBehaviour
{
    private SpriteRenderer _spriteRenderer;

    private float _pixelPerUnit;
    
    private void Awake()
    {
        _spriteRenderer = GetComponent<SpriteRenderer>();

        float x = _spriteRenderer.bounds.size.x;
        float textureX = _spriteRenderer.sprite.texture.width;
        _pixelPerUnit = textureX / x;
     }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            Texture2D originalTexture = _spriteRenderer.sprite.texture; // 이렇게 32X32의 그림이 가져와짐
            int size = 4;

            for (int i = 0; i < 10; i++)
            {
                Texture2D slicedTexture = new Texture2D(size, size);
                slicedTexture.filterMode = FilterMode.Point;
                
                int xStart = Random.Range(0, originalTexture.width - size);
                int yStart = Random.Range(0, originalTexture.height - size);
                SetPixel(yStart,xStart, 8,slicedTexture, originalTexture);
                
                slicedTexture.Apply(); //픽셀로 텍스쳐에 반영

                Sprite s = Sprite.Create(slicedTexture, new Rect(0, 0, size, size), Vector2.one * 0.5f, _pixelPerUnit);
                
                GameObject obj = new GameObject();
                obj.AddComponent<SpriteRenderer>().sprite = s;
                obj.transform.position = transform.position + new Vector3(0, 1, 0);
                obj.AddComponent<PolygonCollider2D>();
                Rigidbody2D rigid = obj.AddComponent<Rigidbody2D>();
                
                rigid.AddForce(Random.insideUnitCircle * Random.Range(10, 15), ForceMode2D.Impulse);
            }
        }
    }

    private void SetPixel(int x, int y, int size, Texture2D tex, Texture2D original)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                Color c = original.GetPixel(x + j, y + j);
                tex.SetPixel(j,i, c);
            }
        }
    }
}
