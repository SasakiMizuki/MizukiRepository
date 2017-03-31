xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 204;
 1.11042;-0.00000;-0.20169;,
 1.11042;-0.14262;-0.14262;,
 -1.11042;-0.14262;-0.14262;,
 -1.11042;0.00000;-0.20169;,
 1.11042;-0.20169;0.00000;,
 -1.11042;-0.20169;0.00000;,
 1.11042;-0.14262;0.14262;,
 -1.11042;-0.14262;0.14262;,
 1.11042;0.00000;0.20169;,
 -1.11042;0.00000;0.20169;,
 1.11042;0.14262;0.14262;,
 -1.11042;0.14262;0.14262;,
 1.11042;0.20169;-0.00000;,
 -1.11042;0.20169;-0.00000;,
 1.11042;0.14262;-0.14262;,
 -1.11042;0.14262;-0.14262;,
 1.11042;-0.00000;-0.20169;,
 -1.11042;0.00000;-0.20169;,
 1.11042;-0.00000;-0.00000;,
 1.11042;-0.00000;-0.00000;,
 1.11042;-0.00000;-0.00000;,
 1.11042;-0.00000;-0.00000;,
 1.11042;-0.00000;-0.00000;,
 1.11042;-0.00000;-0.00000;,
 1.11042;-0.00000;-0.00000;,
 1.11042;-0.00000;-0.00000;,
 -1.11042;0.00000;0.00000;,
 -1.11042;0.00000;0.00000;,
 -1.11042;0.00000;0.00000;,
 -1.11042;0.00000;0.00000;,
 -1.11042;0.00000;0.00000;,
 -1.11042;0.00000;0.00000;,
 -1.11042;0.00000;0.00000;,
 -1.11042;0.00000;0.00000;,
 1.11042;-0.00000;-0.55185;,
 1.11042;-0.14262;-0.49277;,
 -1.11042;-0.14262;-0.49277;,
 -1.11042;0.00000;-0.55185;,
 1.11042;-0.20169;-0.35015;,
 -1.11042;-0.20169;-0.35015;,
 1.11042;-0.14262;-0.20753;,
 -1.11042;-0.14262;-0.20753;,
 1.11042;0.00000;-0.14846;,
 -1.11042;0.00000;-0.14846;,
 1.11042;0.14262;-0.20753;,
 -1.11042;0.14262;-0.20753;,
 1.11042;0.20169;-0.35015;,
 -1.11042;0.20169;-0.35015;,
 1.11042;0.14262;-0.49277;,
 -1.11042;0.14262;-0.49277;,
 1.11042;-0.00000;-0.55185;,
 -1.11042;0.00000;-0.55185;,
 1.11042;-0.00000;-0.35015;,
 1.11042;-0.00000;-0.35015;,
 1.11042;-0.00000;-0.35015;,
 1.11042;-0.00000;-0.35015;,
 1.11042;-0.00000;-0.35015;,
 1.11042;-0.00000;-0.35015;,
 1.11042;-0.00000;-0.35015;,
 1.11042;-0.00000;-0.35015;,
 -1.11042;0.00000;-0.35015;,
 -1.11042;0.00000;-0.35015;,
 -1.11042;0.00000;-0.35015;,
 -1.11042;0.00000;-0.35015;,
 -1.11042;0.00000;-0.35015;,
 -1.11042;0.00000;-0.35015;,
 -1.11042;0.00000;-0.35015;,
 -1.11042;0.00000;-0.35015;,
 1.11042;-0.00000;-0.92145;,
 1.11042;-0.14262;-0.86238;,
 -1.11042;-0.14262;-0.86238;,
 -1.11042;0.00000;-0.92145;,
 1.11042;-0.20169;-0.71976;,
 -1.11042;-0.20169;-0.71976;,
 1.11042;-0.14262;-0.57714;,
 -1.11042;-0.14262;-0.57714;,
 1.11042;0.00000;-0.51806;,
 -1.11042;0.00000;-0.51806;,
 1.11042;0.14262;-0.57714;,
 -1.11042;0.14262;-0.57714;,
 1.11042;0.20169;-0.71976;,
 -1.11042;0.20169;-0.71976;,
 1.11042;0.14262;-0.86238;,
 -1.11042;0.14262;-0.86238;,
 1.11042;-0.00000;-0.92145;,
 -1.11042;0.00000;-0.92145;,
 1.11042;-0.00000;-0.71976;,
 1.11042;-0.00000;-0.71976;,
 1.11042;-0.00000;-0.71976;,
 1.11042;-0.00000;-0.71976;,
 1.11042;-0.00000;-0.71976;,
 1.11042;-0.00000;-0.71976;,
 1.11042;-0.00000;-0.71976;,
 1.11042;-0.00000;-0.71976;,
 -1.11042;0.00000;-0.71976;,
 -1.11042;0.00000;-0.71976;,
 -1.11042;0.00000;-0.71976;,
 -1.11042;0.00000;-0.71976;,
 -1.11042;0.00000;-0.71976;,
 -1.11042;0.00000;-0.71976;,
 -1.11042;0.00000;-0.71976;,
 -1.11042;0.00000;-0.71976;,
 1.11042;-0.00000;0.11928;,
 1.11042;-0.14262;0.17835;,
 -1.11042;-0.14262;0.17835;,
 -1.11042;0.00000;0.11928;,
 1.11042;-0.20169;0.32097;,
 -1.11042;-0.20169;0.32097;,
 1.11042;-0.14262;0.46359;,
 -1.11042;-0.14262;0.46359;,
 1.11042;0.00000;0.52267;,
 -1.11042;0.00000;0.52267;,
 1.11042;0.14262;0.46359;,
 -1.11042;0.14262;0.46359;,
 1.11042;0.20169;0.32097;,
 -1.11042;0.20169;0.32097;,
 1.11042;0.14262;0.17835;,
 -1.11042;0.14262;0.17835;,
 1.11042;-0.00000;0.11928;,
 -1.11042;0.00000;0.11928;,
 1.11042;-0.00000;0.32097;,
 1.11042;-0.00000;0.32097;,
 1.11042;-0.00000;0.32097;,
 1.11042;-0.00000;0.32097;,
 1.11042;-0.00000;0.32097;,
 1.11042;-0.00000;0.32097;,
 1.11042;-0.00000;0.32097;,
 1.11042;-0.00000;0.32097;,
 -1.11042;0.00000;0.32097;,
 -1.11042;0.00000;0.32097;,
 -1.11042;0.00000;0.32097;,
 -1.11042;0.00000;0.32097;,
 -1.11042;0.00000;0.32097;,
 -1.11042;0.00000;0.32097;,
 -1.11042;0.00000;0.32097;,
 -1.11042;0.00000;0.32097;,
 1.11042;-0.00000;0.42080;,
 1.11042;-0.14262;0.47987;,
 -1.11042;-0.14262;0.47987;,
 -1.11042;0.00000;0.42080;,
 1.11042;-0.20169;0.62249;,
 -1.11042;-0.20169;0.62249;,
 1.11042;-0.14262;0.76511;,
 -1.11042;-0.14262;0.76511;,
 1.11042;0.00000;0.82419;,
 -1.11042;0.00000;0.82419;,
 1.11042;0.14262;0.76511;,
 -1.11042;0.14262;0.76511;,
 1.11042;0.20169;0.62249;,
 -1.11042;0.20169;0.62249;,
 1.11042;0.14262;0.47987;,
 -1.11042;0.14262;0.47987;,
 1.11042;-0.00000;0.42080;,
 -1.11042;0.00000;0.42080;,
 1.11042;-0.00000;0.62249;,
 1.11042;-0.00000;0.62249;,
 1.11042;-0.00000;0.62249;,
 1.11042;-0.00000;0.62249;,
 1.11042;-0.00000;0.62249;,
 1.11042;-0.00000;0.62249;,
 1.11042;-0.00000;0.62249;,
 1.11042;-0.00000;0.62249;,
 -1.11042;0.00000;0.62249;,
 -1.11042;0.00000;0.62249;,
 -1.11042;0.00000;0.62249;,
 -1.11042;0.00000;0.62249;,
 -1.11042;0.00000;0.62249;,
 -1.11042;0.00000;0.62249;,
 -1.11042;0.00000;0.62249;,
 -1.11042;0.00000;0.62249;,
 1.11415;0.24089;0.76265;,
 1.07997;0.12183;0.79376;,
 -1.06534;0.33164;-0.76080;,
 -1.03116;0.45070;-0.79191;,
 1.00828;0.06953;0.88562;,
 -1.13703;0.27935;-0.66893;,
 0.94110;0.11464;0.98443;,
 -1.20421;0.32446;-0.57013;,
 0.91776;0.23073;1.03230;,
 -1.22755;0.44054;-0.52226;,
 0.95195;0.34979;1.00119;,
 -1.19336;0.55960;-0.55337;,
 1.02363;0.40208;0.90933;,
 -1.12168;0.61190;-0.64523;,
 1.09082;0.35697;0.81052;,
 -1.05449;0.56679;-0.74404;,
 1.11415;0.24089;0.76265;,
 -1.03116;0.45070;-0.79191;,
 1.01596;0.23581;0.89748;,
 1.01596;0.23581;0.89748;,
 1.01596;0.23581;0.89748;,
 1.01596;0.23581;0.89748;,
 1.01596;0.23581;0.89748;,
 1.01596;0.23581;0.89748;,
 1.01596;0.23581;0.89748;,
 1.01596;0.23581;0.89748;,
 -1.12935;0.44562;-0.65708;,
 -1.12935;0.44562;-0.65708;,
 -1.12935;0.44562;-0.65708;,
 -1.12935;0.44562;-0.65708;,
 -1.12935;0.44562;-0.65708;,
 -1.12935;0.44562;-0.65708;,
 -1.12935;0.44562;-0.65708;,
 -1.12935;0.44562;-0.65708;;
 
 144;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 3;60,37,36;,
 3;61,36,39;,
 3;62,39,41;,
 3;63,41,43;,
 3;64,43,45;,
 3;65,45,47;,
 3;66,47,49;,
 3;67,49,51;,
 4;68,69,70,71;,
 4;69,72,73,70;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 3;86,69,68;,
 3;87,72,69;,
 3;88,74,72;,
 3;89,76,74;,
 3;90,78,76;,
 3;91,80,78;,
 3;92,82,80;,
 3;93,84,82;,
 3;94,71,70;,
 3;95,70,73;,
 3;96,73,75;,
 3;97,75,77;,
 3;98,77,79;,
 3;99,79,81;,
 3;100,81,83;,
 3;101,83,85;,
 4;102,103,104,105;,
 4;103,106,107,104;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 3;120,103,102;,
 3;121,106,103;,
 3;122,108,106;,
 3;123,110,108;,
 3;124,112,110;,
 3;125,114,112;,
 3;126,116,114;,
 3;127,118,116;,
 3;128,105,104;,
 3;129,104,107;,
 3;130,107,109;,
 3;131,109,111;,
 3;132,111,113;,
 3;133,113,115;,
 3;134,115,117;,
 3;135,117,119;,
 4;136,137,138,139;,
 4;137,140,141,138;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 3;154,137,136;,
 3;155,140,137;,
 3;156,142,140;,
 3;157,144,142;,
 3;158,146,144;,
 3;159,148,146;,
 3;160,150,148;,
 3;161,152,150;,
 3;162,139,138;,
 3;163,138,141;,
 3;164,141,143;,
 3;165,143,145;,
 3;166,145,147;,
 3;167,147,149;,
 3;168,149,151;,
 3;169,151,153;,
 4;170,171,172,173;,
 4;171,174,175,172;,
 4;174,176,177,175;,
 4;176,178,179,177;,
 4;178,180,181,179;,
 4;180,182,183,181;,
 4;182,184,185,183;,
 4;184,186,187,185;,
 3;188,171,170;,
 3;189,174,171;,
 3;190,176,174;,
 3;191,178,176;,
 3;192,180,178;,
 3;193,182,180;,
 3;194,184,182;,
 3;195,186,184;,
 3;196,173,172;,
 3;197,172,175;,
 3;198,175,177;,
 3;199,177,179;,
 3;200,179,181;,
 3;201,181,183;,
 3;202,183,185;,
 3;203,185,187;;
 
 MeshMaterialList {
  1;
  144;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\log.jpg";
   }
  }
 }
 MeshNormals {
  116;
  1.000000;-0.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.707107;-0.707107;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-0.707107;0.707107;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.707107;0.707106;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.707107;-0.707107;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000001;0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;-0.000000;,
  -1.000000;0.000001;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.707107;-0.707106;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-0.707107;0.707107;,
  -0.000000;0.000000;1.000000;,
  0.000000;0.707107;0.707106;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.707107;-0.707106;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000001;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;-0.000000;,
  -1.000000;0.000001;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.707107;-0.707107;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-0.707107;0.707106;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.707107;0.707106;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.707107;-0.707107;,
  -1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000001;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;-0.000000;,
  -1.000000;0.000001;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.707106;-0.707107;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-0.707108;0.707106;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.707108;0.707106;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.707106;-0.707107;,
  -1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000001;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;-0.000000;,
  -1.000000;0.000001;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;-0.000000;0.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.707107;-0.707107;,
  -0.000000;-1.000000;0.000001;,
  -0.000000;-0.707107;0.707106;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.707107;0.707106;,
  0.000000;1.000000;0.000001;,
  0.000000;0.707107;-0.707107;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000001;0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;-0.000000;,
  -1.000000;0.000001;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.807225;-0.078947;0.584941;,
  0.588451;0.030442;-0.807959;,
  0.383585;-0.683045;-0.621540;,
  -0.045980;-0.996414;-0.071031;,
  -0.448610;-0.726097;0.521087;,
  -0.588451;-0.030438;0.807960;,
  -0.383583;0.683047;0.621539;,
  0.045980;0.996414;0.071031;,
  0.448611;0.726097;-0.521087;,
  -0.807224;0.078945;-0.584942;,
  0.807223;-0.078945;0.584943;,
  0.807221;-0.078946;0.584946;,
  0.807224;-0.078941;0.584942;,
  0.807225;-0.078945;0.584941;,
  0.807227;-0.078951;0.584938;,
  0.807227;-0.078952;0.584937;,
  0.807227;-0.078951;0.584938;,
  0.807223;-0.078947;0.584943;,
  -0.807226;0.078949;-0.584939;,
  -0.807227;0.078949;-0.584937;,
  -0.807228;0.078946;-0.584937;,
  -0.807224;0.078942;-0.584943;,
  -0.807221;0.078942;-0.584947;,
  -0.807222;0.078944;-0.584945;,
  -0.807224;0.078942;-0.584943;,
  -0.807225;0.078944;-0.584941;;
  144;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,10,10;,
  3;0,10,10;,
  3;0,10,10;,
  3;0,10,10;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,10,13;,
  3;9,14,15;,
  3;9,15,16;,
  3;9,16,17;,
  3;9,17,14;,
  3;9,14,14;,
  3;9,14,14;,
  3;9,14,14;,
  3;9,14,14;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,19,19,26;,
  3;18,28,28;,
  3;18,28,28;,
  3;18,28,28;,
  3;18,28,28;,
  3;18,29,28;,
  3;18,30,29;,
  3;18,31,30;,
  3;18,28,31;,
  3;27,32,33;,
  3;27,33,34;,
  3;27,34,35;,
  3;27,35,32;,
  3;27,32,32;,
  3;27,32,32;,
  3;27,32,32;,
  3;27,32,32;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,37,37,44;,
  3;36,46,46;,
  3;36,46,46;,
  3;36,46,46;,
  3;36,46,46;,
  3;36,47,46;,
  3;36,48,47;,
  3;36,49,48;,
  3;36,46,49;,
  3;45,50,51;,
  3;45,51,52;,
  3;45,52,53;,
  3;45,53,50;,
  3;45,50,50;,
  3;45,50,50;,
  3;45,50,50;,
  3;45,50,50;,
  4;55,56,56,55;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,55,55,62;,
  3;54,64,64;,
  3;54,64,64;,
  3;54,64,64;,
  3;54,64,64;,
  3;54,65,64;,
  3;54,66,65;,
  3;54,67,66;,
  3;54,64,67;,
  3;63,68,69;,
  3;63,69,70;,
  3;63,70,71;,
  3;63,71,68;,
  3;63,68,68;,
  3;63,68,68;,
  3;63,68,68;,
  3;63,68,68;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,73,73,80;,
  3;72,82,82;,
  3;72,82,82;,
  3;72,82,82;,
  3;72,82,82;,
  3;72,83,82;,
  3;72,84,83;,
  3;72,85,84;,
  3;72,82,85;,
  3;81,86,87;,
  3;81,87,88;,
  3;81,88,89;,
  3;81,89,86;,
  3;81,86,86;,
  3;81,86,86;,
  3;81,86,86;,
  3;81,86,86;,
  4;91,92,92,91;,
  4;92,93,93,92;,
  4;93,94,94,93;,
  4;94,95,95,94;,
  4;95,96,96,95;,
  4;96,97,97,96;,
  4;97,98,98,97;,
  4;98,91,91,98;,
  3;90,100,101;,
  3;90,102,100;,
  3;90,103,102;,
  3;90,104,103;,
  3;90,105,104;,
  3;90,106,105;,
  3;90,107,106;,
  3;90,101,107;,
  3;99,108,109;,
  3;99,109,110;,
  3;99,110,111;,
  3;99,111,112;,
  3;99,112,113;,
  3;99,113,114;,
  3;99,114,115;,
  3;99,115,108;;
 }
 MeshTextureCoords {
  204;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
 MeshVertexColors {
  204;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;,
  108;1.000000;1.000000;1.000000;1.000000;,
  109;1.000000;1.000000;1.000000;1.000000;,
  110;1.000000;1.000000;1.000000;1.000000;,
  111;1.000000;1.000000;1.000000;1.000000;,
  112;1.000000;1.000000;1.000000;1.000000;,
  113;1.000000;1.000000;1.000000;1.000000;,
  114;1.000000;1.000000;1.000000;1.000000;,
  115;1.000000;1.000000;1.000000;1.000000;,
  116;1.000000;1.000000;1.000000;1.000000;,
  117;1.000000;1.000000;1.000000;1.000000;,
  118;1.000000;1.000000;1.000000;1.000000;,
  119;1.000000;1.000000;1.000000;1.000000;,
  120;1.000000;1.000000;1.000000;1.000000;,
  121;1.000000;1.000000;1.000000;1.000000;,
  122;1.000000;1.000000;1.000000;1.000000;,
  123;1.000000;1.000000;1.000000;1.000000;,
  124;1.000000;1.000000;1.000000;1.000000;,
  125;1.000000;1.000000;1.000000;1.000000;,
  126;1.000000;1.000000;1.000000;1.000000;,
  127;1.000000;1.000000;1.000000;1.000000;,
  128;1.000000;1.000000;1.000000;1.000000;,
  129;1.000000;1.000000;1.000000;1.000000;,
  130;1.000000;1.000000;1.000000;1.000000;,
  131;1.000000;1.000000;1.000000;1.000000;,
  132;1.000000;1.000000;1.000000;1.000000;,
  133;1.000000;1.000000;1.000000;1.000000;,
  134;1.000000;1.000000;1.000000;1.000000;,
  135;1.000000;1.000000;1.000000;1.000000;,
  136;1.000000;1.000000;1.000000;1.000000;,
  137;1.000000;1.000000;1.000000;1.000000;,
  138;1.000000;1.000000;1.000000;1.000000;,
  139;1.000000;1.000000;1.000000;1.000000;,
  140;1.000000;1.000000;1.000000;1.000000;,
  141;1.000000;1.000000;1.000000;1.000000;,
  142;1.000000;1.000000;1.000000;1.000000;,
  143;1.000000;1.000000;1.000000;1.000000;,
  144;1.000000;1.000000;1.000000;1.000000;,
  145;1.000000;1.000000;1.000000;1.000000;,
  146;1.000000;1.000000;1.000000;1.000000;,
  147;1.000000;1.000000;1.000000;1.000000;,
  148;1.000000;1.000000;1.000000;1.000000;,
  149;1.000000;1.000000;1.000000;1.000000;,
  150;1.000000;1.000000;1.000000;1.000000;,
  151;1.000000;1.000000;1.000000;1.000000;,
  152;1.000000;1.000000;1.000000;1.000000;,
  153;1.000000;1.000000;1.000000;1.000000;,
  154;1.000000;1.000000;1.000000;1.000000;,
  155;1.000000;1.000000;1.000000;1.000000;,
  156;1.000000;1.000000;1.000000;1.000000;,
  157;1.000000;1.000000;1.000000;1.000000;,
  158;1.000000;1.000000;1.000000;1.000000;,
  159;1.000000;1.000000;1.000000;1.000000;,
  160;1.000000;1.000000;1.000000;1.000000;,
  161;1.000000;1.000000;1.000000;1.000000;,
  162;1.000000;1.000000;1.000000;1.000000;,
  163;1.000000;1.000000;1.000000;1.000000;,
  164;1.000000;1.000000;1.000000;1.000000;,
  165;1.000000;1.000000;1.000000;1.000000;,
  166;1.000000;1.000000;1.000000;1.000000;,
  167;1.000000;1.000000;1.000000;1.000000;,
  168;1.000000;1.000000;1.000000;1.000000;,
  169;1.000000;1.000000;1.000000;1.000000;,
  170;1.000000;1.000000;1.000000;1.000000;,
  171;1.000000;1.000000;1.000000;1.000000;,
  172;1.000000;1.000000;1.000000;1.000000;,
  173;1.000000;1.000000;1.000000;1.000000;,
  174;1.000000;1.000000;1.000000;1.000000;,
  175;1.000000;1.000000;1.000000;1.000000;,
  176;1.000000;1.000000;1.000000;1.000000;,
  177;1.000000;1.000000;1.000000;1.000000;,
  178;1.000000;1.000000;1.000000;1.000000;,
  179;1.000000;1.000000;1.000000;1.000000;,
  180;1.000000;1.000000;1.000000;1.000000;,
  181;1.000000;1.000000;1.000000;1.000000;,
  182;1.000000;1.000000;1.000000;1.000000;,
  183;1.000000;1.000000;1.000000;1.000000;,
  184;1.000000;1.000000;1.000000;1.000000;,
  185;1.000000;1.000000;1.000000;1.000000;,
  186;1.000000;1.000000;1.000000;1.000000;,
  187;1.000000;1.000000;1.000000;1.000000;,
  188;1.000000;1.000000;1.000000;1.000000;,
  189;1.000000;1.000000;1.000000;1.000000;,
  190;1.000000;1.000000;1.000000;1.000000;,
  191;1.000000;1.000000;1.000000;1.000000;,
  192;1.000000;1.000000;1.000000;1.000000;,
  193;1.000000;1.000000;1.000000;1.000000;,
  194;1.000000;1.000000;1.000000;1.000000;,
  195;1.000000;1.000000;1.000000;1.000000;,
  196;1.000000;1.000000;1.000000;1.000000;,
  197;1.000000;1.000000;1.000000;1.000000;,
  198;1.000000;1.000000;1.000000;1.000000;,
  199;1.000000;1.000000;1.000000;1.000000;,
  200;1.000000;1.000000;1.000000;1.000000;,
  201;1.000000;1.000000;1.000000;1.000000;,
  202;1.000000;1.000000;1.000000;1.000000;,
  203;1.000000;1.000000;1.000000;1.000000;;
 }
}