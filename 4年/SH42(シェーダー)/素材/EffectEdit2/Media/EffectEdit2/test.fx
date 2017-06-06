string XFile = "misc/nanase_pose.x";
int BCLR = 0x000000ff;

// �ϊ��}�g���b�N�X
float4x4 matWVP : WORLDVIEWPROJECTION;  // ���[���h�~�r���[�~�ˉe
//                ^^^^^^^^^^^^^^^^^^^ �Z�}���e�B�N�X (���[�U��`)
float4x4 matW   : WORLD;                // ���[���h

float3 camera   : CAMERAPOSITION;       //���_���W

// �����x�N�g�� (���̐i�ޕ���)
float3 light
  <string UIDirectional = "Light Direction";>
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ �A�m�e�[�V����
= {-0.35f, -0.25f, 0.9f};

// �����̐F
float4  I_d = {1.0f, 1.0f, 1.0f, 1.0f};//�g�U��
float4  I_a = {0.2f, 0.2f, 0.2f, 1.0f};//����
float4  I_s = {1.0f, 1.0f, 1.0f, 1.0f};//���ʔ��ˌ�

// X�t�@�C���@�}�e���A��
float4  k_d : MATERIALDIFFUSE;   //�g�U�F
float4  k_s : MATERIALSPECULAR;  //���ʔ��ːF
float   k_p : MATERIALPOWER;     //���ʔ��ˎw��
float4  k_a : MATERIALAMBIENT;   //���F
texture tex : MATERIALTEXTURE;
bool    tex_enable : MATERIALTEXTUREVALID;

// �T���v���X�e�[�g
sampler Sampler = sampler_state
{
    Texture = (tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// ���_�V�F�[�_
void testVS(float3 InPos : POSITION,
//                         ^^^^^^^^ �Z�}���e�B�N�X(�V�X�e����`)
            float3 InNor : NORMAL,
            float2 InTex : TEXCOORD0,
            out float4 OutPos  : POSITION,
            out float4 OutDiff : COLOR0,
            out float4 OutSpec : COLOR1,
            out float2 OutTex  : TEXCOORD0)
{
    OutPos = mul(float4(InPos, 1), matWVP);
    float3 L = normalize(-light);
    float3 N = mul(InNor, (float3x3)matW);
    float3 P = mul(float4(InPos, 1), matW).xyz;
    float3 V = normalize(camera - P);
    float3 R = reflect(-V, N);
    OutDiff = I_a * k_a + I_d * k_d * saturate(dot(L, N));
    OutSpec = I_s * k_s * pow(saturate(dot(L, R)), k_p * 0.25f);
    OutTex = InTex;
}

// �s�N�Z���V�F�[�_
void testPS(float4 InDiff : COLOR0,
            float4 InSpec : COLOR1,
            float2 InTex  : TEXCOORD0,
            out float4 OutCol : COLOR0)
{
    OutCol = InDiff;
    if (tex_enable) {
        OutCol *= tex2D(Sampler, InTex);
    }
    OutCol += InSpec;
}

// �e�N�j�b�N
technique tec0
{
    // �p�X
    pass p0
    {
        VertexShader = compile vs_2_0 testVS();
        PixelShader = compile ps_2_0 testPS();
    }
}