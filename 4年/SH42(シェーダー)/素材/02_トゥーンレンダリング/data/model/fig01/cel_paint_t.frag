//------------------------------------------------------------
// ����cel_paint

//------------------------------------------------------------
uniform sampler2D mmv_tex0; // �e�N�X�`��
uniform sampler2D mmv_tex2; // EX�e�N�X�`��1
uniform sampler2D mmv_tex3; // EX�e�N�X�`��2
uniform sampler2DShadow	mmv_shadowbuffer;

//------------------------------------------------------------
varying vec3 VERTEX_NORMAL;	// �@���x�N�g��
varying vec3 VERTEX_LIGHT;	// ���C�g�x�N�g��
varying vec3 VERTEX_LIGHT2;	// ���C�g�x�N�g��
varying vec3 VERTEX_EYE;	// �����x�N�g��

// ------------------------------------------------------------
// �t���O�����g�V�F�[�_�v���O����
// ------------------------------------------------------------
void main( void )
{
	vec3	N	= normalize(VERTEX_NORMAL);	// �@���x�N�g��
	vec3	L	= normalize(VERTEX_LIGHT);	// ���C�g�x�N�g��
	vec3	L2	= normalize(VERTEX_LIGHT2);	// ���C�g�x�N�g��
	vec3	E	= normalize(VERTEX_EYE);	// �����x�N�g��
	vec3	R	= reflect( L, N );			// ���˃x�N�g��
	
	//�F
	vec3	color	= texture2D( mmv_tex0, gl_TexCoord[ 0 ].st ).rgb;	//�}�e���A���F
	float	a		= texture2D( mmv_tex0, gl_TexCoord[ 0 ].st ).a;		//�s�����x
//	vec3	color	= gl_FrontMaterial.diffuse.rgb;	//�}�e���A���F
//	float	a		= gl_FrontMaterial.diffuse.a;	//�s�����x
	
	float	lumi	= texture2D( mmv_tex3, gl_TexCoord[ 0 ].st ).r;
	
	float	dif		= max( dot( N, L ), 0.0 ) * 0.85;	//�g�U���x�i���̋����j
	float	dif2	= max( dot( N, L2 ), 0.0 ) * 0.6;	//�g�U���x�i���̋����j
	dif	= min( ( dif + dif2 ) * lumi, 1.0 );
	
	dif	= dif * ( 254.0 / 256.0 ) + ( 1.0 / 256.0 );	//�I�t�Z�b�g
	
	vec3	cel1	= texture2D( mmv_tex2, vec2( dif, 0.25 ) ).rgb;	//��Z
	vec3	cel2	= texture2D( mmv_tex2, vec2( dif, 0.75 ) ).rgb;	//���Z
	

	//�X�y�L����
	float	powr	= gl_FrontMaterial.shininess;	//���˂̋���
	float	s_dif	= gl_FrontMaterial.specular.r;	//���ˌ�(rgb����)
	
    float	spec	= pow( max( dot( R, E ), 0.0 ), powr ) * s_dif;
	
	
	gl_FragColor	= vec4( color * cel1 + cel2 + vec3( spec ), a );	//�o��
}
