// �o���v�}�b�s���O (EffectEdit2�p)
//
string XFile = "misc/teapot2.x";
//string XFile = "Bump/square.x";

float3 lightDir
<
    string UIDirectional = "Light Direction";
> = {-0.35f, -0.25f, 0.9f};

float3 CameraPos : CAMERAPOSITION;

float4 I_a = {0.1f, 0.1f, 0.1f, 1.0f};
float4 I_d = {1.0f, 1.0f, 1.0f, 1.0f};
float4 I_s = {1.0f, 1.0f, 1.0f, 1.0f};

float4  k_a : MATERIALAMBIENT;
float4  k_d : MATERIALDIFFUSE;
float4  k_s : MATERIALSPECULAR;
float   k_n : MATERIALPOWER;
texture k_t : MATERIALTEXTURE;      // �g�p���Ȃ�
bool    k_e : MATERIALTEXTUREVAID;  // �g�p���Ȃ�

// �o���v�}�b�v�p�e�N�X�`��
texture Tex < string Name = "Earth/earth.bmp"; >;               // �ʏ�e�N�X�`��
//texture Tex < string Name = "Bump/stones.bmp"; >;               // �ʏ�e�N�X�`��
texture NormalMap < string Name = "Earth/earthnormal.bmp"; >;   // �@���}�b�v �e�N�X�`��
//texture NormalMap < string Name = "Bump/stones_NM_height.tga"; >;   // �@���}�b�v �e�N�X�`��

// �ϊ��}�g���b�N�X
float4x4 World : WORLD;
float4x4 WorldViewProj : WORLDVIEWPROJECTION;

sampler Sampler = sampler_state     // �g�p���Ȃ�
{
    Texture = (k_t);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler TexSampler = sampler_state
{
    Texture = (Tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler NormalSampler = sampler_state
{
    Texture = (NormalMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// �o���v�}�b�s���O (���_�V�F�[�_)
void BumpMapVS(float3 InPos  : POSITION,
               float3 InTan  : TANGENT,
               float3 InNorm : NORMAL,
               float2 InTex  : TEXCOORD0,
               out float4 OutPos   : POSITION,
               out float2 OutTex   : TEXCOORD0,
               out float3 OutLight : TEXCOORD1,
               out float3 OutView  : TEXCOORD2)
{
    OutPos = mul(float4(InPos, 1), WorldViewProj);          // ���_���W (�ˉe���)
    OutTex = InTex;                                         // �e�N�X�`�����W
    float3 BiNormal = cross(InNorm, InTan);                 // �]�@�������߂�
    float4 P = mul(float4(InPos, 1), World);                // ���_���W (���[���h���)
    float3 T = normalize(mul(InTan, (float3x3)World));      // �ڃx�N�g�� (���[���h���)
    float3 B = normalize(mul(BiNormal, (float3x3)World));   // �]�@���x�N�g�� (���[���h���)
    float3 N = normalize(mul(InNorm, (float3x3)World));     // �@���x�N�g�� (���[���h���)
    float3 V = normalize(CameraPos - P);                    // ���_�ւ̃x�N�g�� (���[���h���)
    float3 L = normalize(-lightDir);                        // �����ւ̃x�N�g�� (���[���h���)
    OutView.x = dot(V, B);                                  // ���_�ւ̃x�N�g�� (�ڋ��)
    OutView.y = dot(V, T);
    OutView.z = dot(V, N);
    OutLight.x = dot(L, B);                                 // �����ւ̃x�N�g�� (�ڋ��)
    OutLight.y = dot(L, T);
    OutLight.z = dot(L, N);
}

// �o���v�}�b�s���O (�s�N�Z���V�F�[�_)
void BumpMapPS(float2 InTex   : TEXCOORD0,
               float3 InLight : TEXCOORD1,
               float3 InView  : TEXCOORD2,
               out float4 OutCol : COLOR)
{
    float3 L = normalize(InLight);                          // �����ւ̃x�N�g�� (�ڋ��)
    float3 N = tex2D(NormalSampler, InTex) * 2.0f - 1.0f;   // �@���x�N�g�� (�ڋ��)
    N = normalize(float3(-N.y, -N.x, N.z));
    float3 V = normalize(InView);                           // ���_�ւ̃x�N�g�� (�ڋ��)
    float3 R = reflect(-V, N);                              // ���˃x�N�g�� (�ڋ��)
    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // �g�U��
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25f);  // ���ʔ��ˌ�
    OutCol = tex2D(TexSampler, InTex) * Diff + Spec;        // �ŏI�I�ȐF
}

// �o���v�}�b�s���O
technique TBumpMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 BumpMapVS();
        PixelShader  = compile ps_3_0 BumpMapPS();
    }
}
