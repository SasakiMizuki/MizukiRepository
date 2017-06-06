//------------------------------------------------------------
// ����cel_paint

//------------------------------------------------------------
varying vec3 VERTEX_NORMAL;	// �@���x�N�g��
varying vec3 VERTEX_LIGHT;	// ���C�g�x�N�g��
varying vec3 VERTEX_LIGHT2;	// ���C�g�x�N�g��
varying vec3 VERTEX_EYE;	// �����x�N�g��

//------------------------------------------------------------
//���_�V�F�[�_
//------------------------------------------------------------
void main( void )
{
	//���W�ϊ�
	gl_Position	= gl_ModelViewProjectionMatrix * gl_Vertex;
	
	// �F�̂��߂̌v�Z
	vec4	pos	= gl_ModelViewMatrix * gl_Vertex;
	vec3	L	= gl_LightSource[ 0 ].position.xyz;
	vec3	N	= gl_NormalMatrix * gl_Normal;
	
	VERTEX_NORMAL	= N;
	VERTEX_LIGHT	= L;
	VERTEX_LIGHT2	= vec3( -L.x, -L.y, L.z );
	VERTEX_EYE		= vec3( pos );
	
	//�t�u�l
	gl_TexCoord[ 0 ] = gl_MultiTexCoord0;
	gl_TexCoord[ 1 ] = gl_TextureMatrix[ 1 ] * gl_Vertex;
}

