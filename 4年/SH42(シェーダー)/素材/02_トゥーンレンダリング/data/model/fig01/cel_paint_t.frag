//------------------------------------------------------------
// 似非cel_paint

//------------------------------------------------------------
uniform sampler2D mmv_tex0; // テクスチャ
uniform sampler2D mmv_tex2; // EXテクスチャ1
uniform sampler2D mmv_tex3; // EXテクスチャ2
uniform sampler2DShadow	mmv_shadowbuffer;

//------------------------------------------------------------
varying vec3 VERTEX_NORMAL;	// 法線ベクトル
varying vec3 VERTEX_LIGHT;	// ライトベクトル
varying vec3 VERTEX_LIGHT2;	// ライトベクトル
varying vec3 VERTEX_EYE;	// 視線ベクトル

// ------------------------------------------------------------
// フラグメントシェーダプログラム
// ------------------------------------------------------------
void main( void )
{
	vec3	N	= normalize(VERTEX_NORMAL);	// 法線ベクトル
	vec3	L	= normalize(VERTEX_LIGHT);	// ライトベクトル
	vec3	L2	= normalize(VERTEX_LIGHT2);	// ライトベクトル
	vec3	E	= normalize(VERTEX_EYE);	// 視線ベクトル
	vec3	R	= reflect( L, N );			// 反射ベクトル
	
	//色
	vec3	color	= texture2D( mmv_tex0, gl_TexCoord[ 0 ].st ).rgb;	//マテリアル色
	float	a		= texture2D( mmv_tex0, gl_TexCoord[ 0 ].st ).a;		//不透明度
//	vec3	color	= gl_FrontMaterial.diffuse.rgb;	//マテリアル色
//	float	a		= gl_FrontMaterial.diffuse.a;	//不透明度
	
	float	lumi	= texture2D( mmv_tex3, gl_TexCoord[ 0 ].st ).r;
	
	float	dif		= max( dot( N, L ), 0.0 ) * 0.85;	//拡散強度（光の強さ）
	float	dif2	= max( dot( N, L2 ), 0.0 ) * 0.6;	//拡散強度（光の強さ）
	dif	= min( ( dif + dif2 ) * lumi, 1.0 );
	
	dif	= dif * ( 254.0 / 256.0 ) + ( 1.0 / 256.0 );	//オフセット
	
	vec3	cel1	= texture2D( mmv_tex2, vec2( dif, 0.25 ) ).rgb;	//乗算
	vec3	cel2	= texture2D( mmv_tex2, vec2( dif, 0.75 ) ).rgb;	//加算
	

	//スペキュラ
	float	powr	= gl_FrontMaterial.shininess;	//反射の強さ
	float	s_dif	= gl_FrontMaterial.specular.r;	//反射光(rgb同じ)
	
    float	spec	= pow( max( dot( R, E ), 0.0 ), powr ) * s_dif;
	
	
	gl_FragColor	= vec4( color * cel1 + cel2 + vec3( spec ), a );	//出力
}
