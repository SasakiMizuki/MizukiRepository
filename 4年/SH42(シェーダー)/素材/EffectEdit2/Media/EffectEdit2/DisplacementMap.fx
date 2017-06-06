// �f�B�X�v���[�X�����g �}�b�s���O (EffectEdit2�p)
//
string XFile = "Bump/square2.x";

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
texture Tex < string Name = "Bump/stones.bmp"; >;               // �ʏ�e�N�X�`��
texture NormalMap < string Name = "Bump/stones_NM_height.tga"; >;   // �@���}�b�v �e�N�X�`��

float MaxHeight = 0.05f;            // �����ő�l
float Division = 0.002f;            // ������

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

// �t�H���̔��˃��f�� (���_�V�F�[�_)
void PhongVS(float3 InPos  : POSITION,
             float3 InNorm : NORMAL,
             float2 InTex  : TEXCOORD0,
             out float4 OutPos      : POSITION,
             out float2 OutTex      : TEXCOORD0,
             out float3 OutPosForPS : TEXCOORD1,
             out float3 OutNorm     : TEXCOORD2)
{
    OutPos      = mul(float4(InPos, 1), WorldViewProj);     // ���_���W (�ˉe���)
    OutTex      = InTex;                                    // �e�N�X�`�����W
    OutPosForPS = mul(float4(InPos, 1), World).xyz;             // ���_���W (���[���h���)
    OutNorm     = normalize(mul(InNorm, (float3x3)World));  // �@���x�N�g�� (���[���h���)
}

// �f�B�X�v���[�X�����g �}�b�v (���_�V�F�[�_)
void DisplacementVS(float3 InPos  : POSITION,
                    float3 InTan  : TANGENT,
                    float3 InNorm : NORMAL,
                    float2 InTex  : TEXCOORD0,
                    out float4 OutPos      : POSITION,
                    out float2 OutTex      : TEXCOORD0,
                    out float3 OutPosForPS : TEXCOORD1,
                    out float3 OutNorm     : TEXCOORD2)
{
    float4 NH = tex2Dlod(NormalSampler, float4(InTex, 0, 1));   // ����
    InPos += InNorm * NH.w * MaxHeight - 0.5f * MaxHeight;;
    OutPos      = mul(float4(InPos, 1), WorldViewProj);     // ���_���W (�ˉe���)
    OutTex      = InTex;                                    // �e�N�X�`�����W
    OutPosForPS = mul(float4(InPos, 1), World).xyz;             // ���_���W (���[���h���)

    float3 BiNormal = cross(InTan, InNorm);                 // �]�@�������߂�
    float3 T = normalize(mul(InTan, (float3x3)World));      // �ڃx�N�g�� (���[���h���)
    float3 B = normalize(mul(BiNormal, (float3x3)World));   // �]�@���x�N�g�� (���[���h���)
    float3 N = normalize(mul(InNorm, (float3x3)World));     // �@���x�N�g�� (���[���h���)
    float3 NewNorm = NH.xyz * 2.0f - 1.0f;
    OutNorm.x = dot(NewNorm, B);                            // �@���x�N�g�� (���[���h���)
    OutNorm.y = dot(NewNorm, -T);
    OutNorm.z = dot(NewNorm, N);
}

// �t�H���̔��˃��f�� (�s�N�Z���V�F�[�_)
void PhongPS(float2 InTex  : TEXCOORD0,
             float3 InPos  : TEXCOORD1,
             float3 InNorm : TEXCOORD2,
             out float4 OutCol : COLOR)
{
    float3 L = normalize(-lightDir);            // �����ւ̃x�N�g��
    float3 N = normalize(InNorm);               // �@���x�N�g��
    float3 V = normalize(CameraPos - InPos);    // ���_�ւ̃x�N�g��
    float3 R = reflect(-V, N);                  // ���˃x�N�g��

    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // �g�U�F + ���F
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25);   // ���ʔ��ːF

    OutCol = tex2D(TexSampler, InTex) * Diff + Spec;
}

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
    float3 BiNormal = cross(InTan, InNorm);                 // �]�@�������߂�
    float4 P = mul(float4(InPos, 1), World);                // ���_���W (���[���h���)
    float3 T = normalize(mul(InTan, (float3x3)World));      // �ڃx�N�g�� (���[���h���)
    float3 B = normalize(mul(BiNormal, (float3x3)World));   // �]�@���x�N�g�� (���[���h���)
    float3 N = normalize(mul(InNorm, (float3x3)World));     // �@���x�N�g�� (���[���h���)
    float3 V = normalize(CameraPos - P.xyz);                    // ���_�ւ̃x�N�g�� (���[���h���)
    float3 L = normalize(-lightDir);                        // �����ւ̃x�N�g�� (���[���h���)
    OutView.x = dot(V, B);                                  // ���_�ւ̃x�N�g�� (�ڋ��)
    OutView.y = dot(V, T);
    OutView.z = dot(V, N);
    OutLight.x = dot(L, B);                                 // �����ւ̃x�N�g�� (�ڋ��)
    OutLight.y = -dot(L, T);    // (�ǂ����Ƀo�O��!?)
    OutLight.z = dot(L, N);
}

// �o���v�}�b�s���O (�s�N�Z���V�F�[�_)
void BumpMapPS(float2 InTex   : TEXCOORD0,
               float3 InLight : TEXCOORD1,
               float3 InView  : TEXCOORD2,
               out float4 OutCol : COLOR)
{
    float3 L = normalize(InLight);                          // �����ւ̃x�N�g�� (�ڋ��)
    float3 N = tex2D(NormalSampler, InTex).rgb * 2.0f - 1.0f;       // �@���x�N�g�� (�ڋ��)
    N = normalize(N);
    float3 V = normalize(InView);                           // ���_�ւ̃x�N�g�� (�ڋ��)
    float3 R = reflect(-V, N);                              // ���˃x�N�g�� (�ڋ��)
    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // �g�U��
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25f);  // ���ʔ��ˌ�
    OutCol = tex2D(TexSampler, InTex) * Diff + Spec;        // �ŏI�I�ȐF
}

// �����}�b�s���O (�s�N�Z���V�F�[�_)
void ParalluxMapPS(float2 InTex   : TEXCOORD0,
                   float3 InLight : TEXCOORD1,
                   float3 InView  : TEXCOORD2,
                   out float4 OutCol : COLOR)
{
    float3 L = normalize(InLight);                          // �����ւ̃x�N�g�� (�ڋ��)
    float3 V = normalize(InView);                           // ���_�ւ̃x�N�g�� (�ڋ��)
    float  H = tex2D(NormalSampler, InTex).a;                   // �����擾
    float2 Tex = InTex + V.xy * H * MaxHeight;              // UV���W�����炷
    float3 N = (float3)tex2D(NormalSampler, Tex) * 2.0f - 1.0f; // �@���x�N�g�� (�ڋ��)
    N = normalize(N);
    float3 R = reflect(-V, N);                              // ���˃x�N�g�� (�ڋ��)
    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // �g�U��
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25f);  // ���ʔ��ˌ�
    OutCol = tex2D(TexSampler, Tex) * Diff + Spec;          // �ŏI�I�ȐF
}

// �����Օ��}�b�s���O (�s�N�Z���V�F�[�_)
void POMapPS(float2 InTex   : TEXCOORD0,
             float3 InLight : TEXCOORD1,
             float3 InView  : TEXCOORD2,
             out float4 OutCol : COLOR)
{
    float3 L = normalize(InLight);      // �����ւ̃x�N�g�� (�ڋ��)
    float3 V = normalize(InView);       // ���_�ւ̃x�N�g�� (�ڋ��)
    float2 dx = ddx(InTex);             // x�����̌��z
    float2 dy = ddy(InTex);             // y�����̌��z
    float4 NH = float4(0, 0, 1, 1);     // �@���x�N�g��&���� (�ڋ��)
    float2 offset = V.xy * Division;    // �T���v�����O�ʒu�̃I�t�Z�b�g�l
    float2 Tex = InTex;                 // �T���v�����O�ʒu
    float height = MaxHeight;                // 
    while (height > 0.0f) {
        NH = tex2Dgrad(NormalSampler, Tex, dx, dy); // 
        if (NH.a * MaxHeight >= height)         // 
            break;
        Tex -= offset;                          // 
        height -= V.z * Division;               // 
    }
    float3 N = normalize((float3)NH * 2.0f - 1.0f);                 // �@���x�N�g��
    float3 R = reflect(-V, N);                                      // ���˃x�N�g��
    float4 Diff = I_a * k_a + I_d * k_d * max(0, dot(L, N));        // �g�U��
    float4 Spec = I_s * k_s * pow(max(0, dot(L, R)), k_n * 0.25f);  // ���ʔ��ˌ�
    OutCol = tex2Dgrad(TexSampler, Tex, dx, dy) * Diff + Spec;      // �ŏI�I�ȐF
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

// �����}�b�s���O
technique TParallaxMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 BumpMapVS();
        PixelShader  = compile ps_3_0 ParalluxMapPS();
    }
}

// �����Օ��}�b�s���O
technique TParallaxOcclusionMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 BumpMapVS();
        PixelShader  = compile ps_3_0 POMapPS();
    }
}

// �f�B�X�v���[�X�����g �}�b�s���O
technique TDisplacementMap
{
    pass P0
    {
        VertexShader = compile vs_3_0 DisplacementVS();
        PixelShader  = compile ps_3_0 PhongPS();
    }
}

// �t�H�� �V�F�[�f�B���O
technique TPhong
{
    pass P0
    {
        VertexShader = compile vs_3_0 PhongVS();
        PixelShader  = compile ps_3_0 PhongPS();
    }
}