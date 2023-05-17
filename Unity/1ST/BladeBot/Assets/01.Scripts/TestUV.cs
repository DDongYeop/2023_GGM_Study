using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestUV : MonoBehaviour
{
    private MeshFilter _meshFilter;
    private void Awake()
    {
        _meshFilter = GetComponent<MeshFilter>();
    }

    private void Start()
    {
        Mesh mesh = new Mesh(); //새로운 메시를 만들어서

        Vector3[] vertices = new Vector3[4];
        Vector2[] uv = new Vector2[4];
        int[] triangles = new int[6];


        vertices[0] = new Vector3(0, 0);
        vertices[1] = new Vector3(0, 5);
        vertices[2] = new Vector3(5, 5);
        vertices[3] = new Vector3(5, 0);

        triangles[0] = 0;
        triangles[1] = 1;
        triangles[2] = 2;
        triangles[3] = 0;
        triangles[4] = 2;
        triangles[5] = 3;

        uv[0] = new Vector2(0, 0);
        uv[1] = new Vector2(0, 1);
        uv[2] = new Vector2(1, 1);
        uv[3] = new Vector2(1, 0);

        mesh.vertices = vertices;
        mesh.uv = uv; //비어있는 배열
        mesh.triangles = triangles;

        _meshFilter.mesh = mesh; //메시 필터에 제공한다.
    }
}
