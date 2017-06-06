//------------------------------------------------------------
// 似非cel_paint

//------------------------------------------------------------
varying vec3 VERTEX_NORMAL;	// 法線ベクトル
varying vec3 VERTEX_LIGHT;	// ライトベクトル
varying vec3 VERTEX_LIGHT2;	// ライトベクトル
varying vec3 VERTEX_EYE;	// 視線ベクトル

//------------------------------------------------------------
//頂点シェーダ
//------------------------------------------------------------
void main( void )
{
	//座標変換
	gl_Position	= gl_ModelViewProjectionMatrix * gl_Vertex;
	
	// 色のための計算
	vec4	pos	= gl_ModelViewMatrix * gl_Vertex;
	vec3	L	= gl_LightSource[ 0 ].position.xyz;
	vec3	N	= gl_NormalMatrix * gl_Normal;
	
	VERTEX_NORMAL	= N;
	VERTEX_LIGHT	= L;
	VERTEX_LIGHT2	= vec3( -L.x, -L.y, L.z );
	VERTEX_EYE		= vec3( pos );
	
	//ＵＶ値
	gl_TexCoord[ 0 ] = gl_MultiTexCoord0;
	gl_TexCoord[ 1 ] = gl_TextureMatrix[ 1 ] * gl_Vertex;
}

