// �g�D�[�������_�����O
// (�g�D�[���V�F�[�f�B���O+�֊s��)

// �ϊ��s��
float4x4 matWVP : WORLDVIEWPROJECTION;
// ���[���h�~�r���[�~�ˉe�ϊ�
float4x4 matW   : WORLD;
// ���[���h�ϊ�

float3 camera   : CAMERAPOSITION;       //���_���W

// �����x�N�g�� (���̐i�ޕ���)
float3 light = {-0.35f, -0.25f, 0.9f};

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

texture texBlur;	// �ڂ����e�N�X�`��
texture texDepth;	// �[�x�l�e�N�X�`��
float focus;		// �s���g����(0.0f~0.1f)
float range = 10.0f;// �t�H�[�J�X�͈�

// �֊s���̑���
float   thickness = 0.005f;   // ���f���ɂ�蒲���K�v

							  // �T���v���X�e�[�g
sampler Sampler = sampler_state
{
	Texture = (tex);
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};
// �T���v���X�e�[�g
sampler SamplerBlur = sampler_state
{
	Texture = (texBlur);
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};
// �T���v���X�e�[�g
sampler SamplerDepth = sampler_state
{
	Texture = (texDepth);
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// ��ʊE�[�x �ʏ�o�͗p(VS)
// (Phong�V�F�[�f�B���O�Ɠ���)
void PhongVS(float4 InPos : POSITION,
            float3 InNor : NORMAL,
            float2 InTex : TEXCOORD0,
            out float4 OutPos  : POSITION,
            out float2 OutTex  : TEXCOORD0,
            out float3 OutWPos : TEXCOORD1,
            out float3 OutWNor : TEXCOORD2,
			out float4 OutDepth: TEXCOORD3)
{
    OutPos = mul(InPos, matWVP);
    OutTex = InTex;
    OutWPos = mul(InPos, matW).xyz;
    OutWNor = mul(InNor, (float3x3)matW);
	OutDepth = OutPos;	// �[�x�l�����̂܂܏o��
}

// �g�D�[���V�F�[�f�B���O(PS)
void PhongPS(float2 InTex : TEXCOORD0,
            float3 InPos : TEXCOORD1,
            float3 InNor : TEXCOORD2,
			float4 InDepth: TEXCOORD3,
            out float4 OutCol : COLOR0,
			out float4 OutDepth: COLOR1)
{
	float z = InDepth.z / InDepth.w;
	OutDepth = float4(z, z, z, 1.0f);

    float3 L = normalize(-light);
    float3 N = normalize(InNor);
    float3 V = normalize(camera - InPos);
    float3 R = reflect(-V, N);

    OutCol = I_a * k_a + I_d * k_d * saturate(dot(L, N);
    if (tex_enable) {
        OutCol *= tex2D(Sampler, InTex);
    }
    OutCol += I_s * k_s * pow(saturate(dot(L, R)), k_p * 0.25f);
}

// �֊s��(VS)
void SimpleVS(float4 InPos : POSITION,
			float2 InTex : TEXCOORD0,
            out float4 OutPos : POSITION,
			out float2 OutTex : TEXCOORD0)
{
	OutPos = InPos;
	OutTex = InTex;
}

// �֊s��(PS)
// (�֊s���̐F���o�͂��邾��)
void BlurPS(float2 InTex : TEXCOORD0,
	out float4 OutCol : COLOR0)
{
    // �e�N�Z�������ɂ��炷(�o��400*300��)
	InTex.x += 0.5f / 400.0f;
	InTex.y += 0.5f / 300.0f;
	// 1�e�N�Z���̃T�C�Y
	float dx = 1.0f / 400.0f;
	float dy = 1.0f / 300.0f;
	OutCol = float4(0, 0, 0, 0);
	for (int y = -4; y < 5; ++y) {
		for (int x = -4; x < 5; ++x) {
			OutCol += tex2D(Sampler,
				InTex + float2(dx * x, dy * y)) / 81.0f;
			
		}
	}

	OutCol.a = 1.0f;
}

// ��ʊE�[�x
void FocusPS(float2 InTex : TEXCOORD0,
	out float4 OutCol : COLOR0)
	{
	float depth = tex2D(SamplerDepth, InTex).r;
	float blend = abs(depth - focus) * range;
	blend = saturate(blend);
	
	 OutCol = tex2D(Sampler, InTex) * (1.0f - blend)
		+ tex2D(SamplerBlur, InTex) * blend;
	}

// 
technique TFocus
{
    pass P0
    {
        VertexShader = compile vs_3_0 PhongVS();
        PixelShader = compile ps_3_0 PhongPS();
    }
}

// ��ʊE�[�x(�ڂ��� + 1/2�R�s�[)
techique TBlur{

	// �p�X1 : �֊s��
	pass P0
{
	CullMode = CW;
	VertexShader = compile vs_3_0 SimpleVS();
	PixelShader = compile ps_3_0 BlurPS();
}
}


// ��ʊE�[�x(�ŏI�\��)
techique TFocus{

	// �p�X1 : �֊s��
	pass P0
{
	CullMode = CW;
	VertexShader = compile vs_3_0 SimpleVS();
	PixelShader = compile ps_3_0 FocusPS();
}
}
