// �e�탉�C�e�B���O
//
//string XFile = "misc/nanase_pose.x";float weight = 0.003f;
//string XFile = "misc/mone_pose.x";float weight = 0.003f;
//string XFile = "misc/maid_pose.x";float weight = 0.005f;
//string XFile = "fig01/fig01.x";float weight = 0.001f;
string XFile = "hackadoll/1��_v1.00.x";float weight = 0.2f;
//string XFile = "hackadoll/2��_v1.00.x";float weight = 0.2f;
//string XFile = "hackadoll/3��_v1.00.x";float weight = 0.2f;

int BCLR = 0x000000ff;

// �ϊ��}�g���b�N�X
float4x4 matWVP : WORLDVIEWPROJECTION;  // ���[���h�~�r���[�~�ˉe
//                ^^^^^^^^^^^^^^^^^^^ �Z�}���e�B�N�X (���[�U��`)
float4x4 matW   : WORLD;                // ���[���h
float4x4 matVP	: VIEWPROJECTION;

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

// �֊s���̑���
float	thickness = 0.7f;

// �T���v���X�e�[�g
sampler Sampler = sampler_state
{
    Texture = (tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// �g�D�[���V�F�[�f�B���O(VS)
// (Phone�V�F�[�f�B���O�Ɠ���)
void ToonVS(float4 InPos : POSITION,
            float3 InNor : NORMAL,
            float2 InTex : TEXCOORD0,
            out float4 OutPos  : POSITION,
            out float2 OutTex  : TEXCOORD0,
			out float3 OutWPos : TEXCOORD1,
			out float3 OutWNor : TEXCOORD2)
{
    OutPos = mul(InPos, matWVP);
    OutTex = InTex;
	OutWPos = mul(InPos, matW).xyz;
	OutWNor = mul(InNor, (float3x3)matW);
}

// �g�D�[���V�F�[�f�B���O
void ToonPS(float2 InTex : TEXCOORD0,
            float3 InPos : TEXCOORD1,
			float3 InNor : TEXCOORD2,
			out float4 OutCol : COLOR0)
{
	float3 L = normalize(-light);
	float3 N = normalize(InNor);
	float3 V = normalize(camera - InPos);
	float3 R = reflect(-V, N);
	//float B = saturate(dot(L, N));
	float B = dot(L, N);

	// if����2�K����
	if (B < 0.3f)
		B = 0.6f;
	else 
		B = 1.0f;

    OutCol = I_a * k_a + I_d * k_d * B;
    if (tex_enable) {
        OutCol *= tex2D(Sampler, InTex);
    }
	//OutCol += I_s * k_s * pow(saturate(dot(L, R)), k_p * 0.25f);
}

// ���_�V�F�[�_(�֊s���`��)
void EdgeVS(float4 InPos : POSITION,
	float3 InNor : NORMAL,
	out float4 OutPos : POSITION) {

	float3 P = InPos.xyz + InNor * thickness;
	OutPos = mul(float4(P, 1), matWVP);
}

// �s�N�Z���V�F�[�_(�֊s���`��)
void EdgePS(out float4 OutCol : COLOR0) {
	OutCol = float4(0.0f, 0.0f, 0.0f, 1.0f);
}

// �t�H�� �V�F�[�f�B���O
technique TToon
{
    // �p�X
    pass P0
    {
		CullMode = CCW;
        VertexShader = compile vs_3_0 ToonVS();
        PixelShader = compile ps_3_0 ToonPS();
    }
	pass P1
	{
		CullMode = CW;
		VertexShader = compile vs_3_0 EdgeVS();
		PixelShader = compile ps_3_0 EdgePS();
	}
}