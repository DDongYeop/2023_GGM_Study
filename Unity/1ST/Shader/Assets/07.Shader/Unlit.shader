Shader "Unlit/Unlit"
{
    Properties
    {
        _ColorA("Color A", Color) = (1, 0, 0, 1)
        _ColorB("Color B", Color) = (0, 0, 1, 1)
        // Int, Float, Vector, Range, Color, 2D, CUBE
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            struct v2f
            {
                float4 vertex: SV_POSITION;
                float4 pos: TEXCOORD1;
                float2 uv: TEXCOORD0;
            };

            v2f vert(appdata_base v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.pos - v.vertex;
                o.uv - v.texcoord;
                return o;
            }

            fixed4 _ColorA;
            fixed4 _ColorB;
            
            fixed4 frag (v2f_img i) : SV_Target
            {
                //fixed3 c = fixed3((sin(_Time.z) + 1.0) * 0.5, 0, (cos(_Time.z)+1) * 0.5);

                //float delta = (i.uv.x + i.uv.y) * 0.5;
                //fixed3 color = lerp(_ColorA, _ColorB, delta);

                fixed3 color = saturate(i.pos * 2);
                
                return float4(color, 1);
            }
            ENDCG
        }
    }
}
