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
 183;
 138.07745;12.32350;-13.06310;,
 138.07745;12.32350;12.25706;,
 138.07745;-12.52866;12.25706;,
 138.07745;-12.52866;-13.06310;,
 146.34795;30.60214;11.54210;,
 146.34795;30.60214;-12.34814;,
 146.34795;-18.80730;23.54210;,
 146.34795;18.60214;23.54210;,
 146.34795;-30.80730;-12.34814;,
 146.34795;-30.80730;11.54210;,
 146.34795;18.60214;-24.34814;,
 146.34795;-18.80730;-24.34814;,
 -29.89207;16.93606;-13.68326;,
 -6.06024;18.60214;-15.25102;,
 -6.06024;-18.80730;-15.25102;,
 -29.89207;-17.14122;-13.68326;,
 -29.89207;28.93606;-1.68334;,
 -6.06024;30.60214;-3.25102;,
 -6.06024;-30.80730;-3.25102;,
 -29.89207;-29.14122;-1.68334;,
 -165.99326;-0.18978;-3.71262;,
 -169.44806;22.02374;-3.20518;,
 -29.89207;16.93606;12.87722;,
 -169.44806;22.02374;2.39914;,
 -165.99326;-0.18978;2.90658;,
 -29.89207;-17.14122;12.87722;,
 -29.89207;28.93606;0.87730;,
 -29.89207;-29.14122;0.87730;,
 -6.06024;18.60214;14.44498;,
 -6.06024;-18.80730;14.44498;,
 -6.06024;30.60214;2.44498;,
 -6.06024;-30.80730;2.44498;,
 -88.16139;6.15246;-0.40302;,
 -116.87167;6.15246;95.80290;,
 -116.87167;-0.43858;95.80290;,
 -88.16139;-0.43858;-0.40302;,
 -116.87167;-0.43858;-96.60894;,
 -116.87167;6.15246;-96.60894;,
 -147.69127;6.15246;-96.60894;,
 -130.38495;6.15246;-0.40302;,
 -147.69127;6.15246;95.80290;,
 -130.38495;-0.43858;-0.40302;,
 -147.69127;-0.43858;-96.60894;,
 -147.69127;-0.43858;95.80290;,
 -153.67368;6.15246;-16.42326;,
 -153.67368;-0.43858;-16.42326;,
 -153.67368;-0.43858;15.61722;,
 -153.67368;6.15246;15.61722;,
 40.73848;13.59838;-215.98105;,
 42.35696;14.95446;-223.62700;,
 42.35696;12.58078;-223.62700;,
 40.73848;10.81494;-215.98105;,
 -4.89544;-31.99347;-0.40302;,
 -4.89544;-17.65714;-0.40302;,
 40.73848;10.81494;215.17496;,
 42.35696;12.58078;222.82086;,
 42.35696;14.95446;222.82086;,
 40.73848;13.59838;215.17496;,
 101.59856;13.59838;215.17496;,
 101.59856;14.95446;222.82086;,
 101.59856;12.58078;222.82086;,
 101.59856;10.81494;215.17496;,
 101.59856;-31.99347;-0.40302;,
 101.59856;-17.65714;-0.40302;,
 101.59856;10.81494;-215.98105;,
 101.59856;12.58078;-223.62700;,
 101.59856;14.95446;-223.62700;,
 101.59856;13.59838;-215.98105;,
 55.18568;14.01998;-232.30659;,
 55.18568;16.93574;-232.39961;,
 55.18568;16.93574;231.59352;,
 55.18568;14.01998;231.50044;,
 86.46000;16.93574;-232.39961;,
 86.46000;14.56206;-232.39961;,
 86.46000;14.56206;231.59352;,
 86.46000;16.93574;231.59352;,
 -140.47118;-0.43858;-102.83951;,
 -140.47118;6.15246;-102.83951;,
 -140.47118;6.15246;102.03345;,
 -140.47118;-0.43858;102.03345;,
 -123.64870;6.15246;-102.83951;,
 -123.64870;-0.43858;-102.83951;,
 -123.64870;-0.43858;102.03345;,
 -123.64870;6.15246;102.03345;,
 -60.89696;22.02374;-3.20518;,
 -60.89696;22.02374;2.39914;,
 -149.49846;88.10493;-3.20518;,
 -158.04103;79.54126;-3.20518;,
 -158.04103;79.54126;2.39914;,
 -149.49846;88.10493;2.39914;,
 -133.84430;90.76398;2.39914;,
 -133.84430;90.76398;-3.20518;,
 -115.77575;89.31213;2.39914;,
 -98.75398;79.22974;2.39914;,
 -98.75398;79.22974;-3.20518;,
 -115.77575;89.31213;-3.20518;,
 -162.51918;64.85310;2.39914;,
 -162.51918;64.85310;-3.20518;,
 -165.36191;50.52294;-3.20518;,
 -165.36191;50.52294;2.39914;,
 -93.60430;64.85310;-3.20518;,
 -87.89787;50.52294;-3.20518;,
 -93.60430;64.85310;2.39914;,
 -87.89787;50.52294;2.39914;,
 -167.47926;34.63510;-3.20518;,
 -167.47926;34.63510;2.39914;,
 -76.31512;34.63510;-3.20518;,
 -76.31512;34.63510;2.39914;,
 -170.19591;15.06814;2.51354;,
 -170.19591;15.06814;-3.31958;,
 -170.13910;8.10742;-3.46190;,
 -170.13910;8.10742;2.65586;,
 130.09450;18.60214;-23.37798;,
 130.09442;-18.80730;-23.37798;,
 130.09450;30.60214;-11.37798;,
 130.09450;-30.80730;-11.37798;,
 130.09450;-18.80730;22.57194;,
 130.09450;18.60214;22.57194;,
 130.09442;-30.80730;10.57194;,
 130.09450;30.60214;10.57194;,
 138.13490;10.29742;-10.80302;,
 154.23674;5.49742;-10.80302;,
 154.23674;-5.70258;-10.80302;,
 138.13490;-10.50258;-10.80302;,
 154.23674;10.29742;-6.00302;,
 154.23674;-10.50258;-6.00302;,
 154.23674;5.49742;9.99698;,
 138.13490;10.29742;9.99698;,
 138.13490;-10.50258;9.99698;,
 154.23674;-5.70258;9.99698;,
 154.23674;10.29742;5.19698;,
 154.23674;-10.50258;5.19698;,
 167.83730;-3.30258;-6.69670;,
 167.83730;3.09742;-6.69670;,
 165.53972;-6.39626;-6.69670;,
 165.58722;6.19110;-6.69670;,
 170.13483;-3.30258;-3.60302;,
 170.13483;3.09742;-3.60302;,
 167.83730;-6.39626;-3.60302;,
 168.36017;6.19110;-3.60302;,
 170.13483;3.09742;2.79698;,
 170.19505;-3.30258;2.80090;,
 168.34425;6.19110;2.80090;,
 167.82138;-3.27674;5.89066;,
 167.83730;3.09742;5.89066;,
 167.83730;-6.39626;2.79698;,
 165.54970;6.19110;5.88674;,
 165.53972;-6.39626;5.89066;,
 -6.00344;35.41998;-13.32262;,
 -6.00344;18.53678;-13.32262;,
 -30.12047;16.97910;-13.36254;,
 -13.23680;34.48542;-13.36254;,
 -6.00344;35.41998;12.51658;,
 -13.23680;34.48542;12.55650;,
 -30.12047;16.97910;12.55650;,
 -6.00344;18.53678;12.51658;,
 73.12423;35.41998;-13.15678;,
 73.12423;18.53678;-13.15678;,
 73.12423;18.53678;12.35074;,
 73.12423;35.41998;12.35074;,
 -13.23680;39.42886;8.62066;,
 -6.00344;40.36342;8.62066;,
 86.15704;34.44438;8.62066;,
 73.12423;40.36342;8.62066;,
 86.15704;29.50102;12.31746;,
 103.27306;18.53678;8.62066;,
 103.27306;18.53678;12.31746;,
 -6.00344;40.36342;-9.42670;,
 -13.23680;39.42886;-9.42670;,
 86.15704;34.44438;-9.42670;,
 86.15704;29.50102;-13.12350;,
 73.12423;40.36342;-9.42670;,
 103.27306;18.53678;-9.42670;,
 103.27306;18.53678;-13.12350;,
 -13.23680;43.93478;-0.41358;,
 -6.00344;44.86942;-0.41358;,
 -22.02527;38.70214;-0.41358;,
 -22.02527;34.19614;8.62066;,
 -22.02527;34.19614;-9.42670;,
 73.12423;44.86942;-0.41358;,
 86.15704;38.95038;-0.41358;,
 103.27306;18.53678;-0.41358;,
 -30.12047;16.97910;-0.41358;;
 
 184;
 4;0,1,2,3;,
 4;4,1,0,5;,
 4;6,2,1,7;,
 4;8,3,2,9;,
 4;10,0,3,11;,
 3;10,5,0;,
 3;4,7,1;,
 3;6,9,2;,
 3;8,11,3;,
 4;12,13,14,15;,
 4;12,16,17,13;,
 4;18,19,15,14;,
 4;12,15,20,21;,
 3;20,15,19;,
 3;16,12,21;,
 4;22,23,24,25;,
 3;23,22,26;,
 3;27,25,24;,
 4;28,22,25,29;,
 4;28,30,26,22;,
 4;27,31,29,25;,
 4;16,21,23,26;,
 4;17,16,26,30;,
 4;19,18,31,27;,
 4;19,27,24,20;,
 4;32,33,34,35;,
 4;32,35,36,37;,
 4;32,37,38,39;,
 4;32,39,40,33;,
 4;41,42,36,35;,
 4;41,35,34,43;,
 4;44,38,42,45;,
 4;44,45,41,39;,
 4;46,43,40,47;,
 4;46,47,39,41;,
 3;43,46,41;,
 3;41,45,42;,
 3;39,47,40;,
 3;38,44,39;,
 4;48,49,50,51;,
 4;48,51,52,53;,
 4;54,55,56,57;,
 4;54,57,53,52;,
 4;58,59,60,61;,
 4;58,61,62,63;,
 4;64,65,66,67;,
 4;64,67,63,62;,
 4;67,48,53,63;,
 4;57,58,63,53;,
 4;51,50,65,64;,
 4;51,64,62,52;,
 4;61,60,55,54;,
 4;61,54,52,62;,
 4;68,50,49,69;,
 4;70,56,55,71;,
 4;72,66,65,73;,
 4;74,60,59,75;,
 4;76,42,38,77;,
 4;78,40,43,79;,
 4;80,37,36,81;,
 4;82,34,33,83;,
 4;23,21,84,85;,
 4;86,87,88,89;,
 4;86,89,90,91;,
 4;92,93,94,95;,
 4;92,95,91,90;,
 3;94,87,86;,
 3;89,88,93;,
 4;86,91,95,94;,
 4;93,92,90,89;,
 4;96,88,87,97;,
 4;96,97,98,99;,
 4;97,87,94,100;,
 4;97,100,101,98;,
 4;100,94,93,102;,
 4;100,102,103,101;,
 4;102,93,88,96;,
 4;102,96,99,103;,
 4;104,21,23,105;,
 4;104,105,99,98;,
 4;106,84,21,104;,
 4;106,104,98,101;,
 4;107,85,84,106;,
 4;107,106,101,103;,
 4;105,23,85,107;,
 4;105,107,103,99;,
 4;108,23,21,109;,
 4;108,109,110,111;,
 4;112,10,11,113;,
 4;112,113,14,13;,
 4;112,13,17,114;,
 4;112,114,5,10;,
 4;113,11,8,115;,
 4;113,115,18,14;,
 4;116,6,7,117;,
 4;116,117,28,29;,
 4;116,29,31,118;,
 4;116,118,9,6;,
 4;117,7,4,119;,
 4;117,119,30,28;,
 4;119,4,5,114;,
 4;119,114,17,30;,
 4;115,8,9,118;,
 4;115,118,31,18;,
 4;68,73,65,50;,
 4;55,60,74,71;,
 4;72,73,68,69;,
 4;70,71,74,75;,
 4;57,56,59,58;,
 4;67,66,49,48;,
 4;56,70,75,59;,
 4;66,72,69,49;,
 4;82,79,43,34;,
 4;83,78,79,82;,
 4;81,76,77,80;,
 4;33,40,78,83;,
 4;80,77,38,37;,
 4;111,110,20,24;,
 4;23,108,111,24;,
 4;20,110,109,21;,
 4;81,36,42,76;,
 4;120,121,122,123;,
 3;124,121,120;,
 3;123,122,125;,
 4;126,127,128,129;,
 3;127,126,130;,
 3;131,129,128;,
 4;130,124,120,127;,
 4;128,123,125,131;,
 4;132,122,121,133;,
 3;122,132,134;,
 3;135,133,121;,
 4;136,132,133,137;,
 4;136,138,134,132;,
 4;135,139,137,133;,
 3;124,135,121;,
 3;139,135,124;,
 3;134,125,122;,
 3;125,134,138;,
 4;137,140,141,136;,
 4;142,140,137,139;,
 4;143,141,140,144;,
 4;138,136,141,145;,
 4;142,146,144,140;,
 4;143,147,145,141;,
 4;130,142,139,124;,
 3;146,142,130;,
 4;129,143,144,126;,
 3;147,143,129;,
 3;126,144,146;,
 4;125,138,145,131;,
 3;131,145,147;,
 3;130,126,146;,
 3;129,131,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,149,148;,
 4;158,159,152,155;,
 4;160,153,152,161;,
 4;162,163,159,164;,
 4;163,161,152,159;,
 4;165,162,164,166;,
 4;167,148,151,168;,
 4;169,170,156,171;,
 4;171,156,148,167;,
 4;172,173,170,169;,
 4;174,160,161,175;,
 4;174,175,167,168;,
 4;176,177,160,174;,
 4;176,174,168,178;,
 4;179,163,162,180;,
 4;179,180,169,171;,
 4;175,161,163,179;,
 4;175,179,171,167;,
 4;180,162,165,181;,
 4;180,181,172,169;,
 4;177,176,182,154;,
 4;150,182,176,178;,
 4;153,160,177,154;,
 4;150,178,168,151;,
 3;170,173,157;,
 3;158,166,164;,
 3;157,156,170;,
 3;164,159,158;;
 
 MeshMaterialList {
  4;
  184;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  2,
  2,
  0,
  2,
  2,
  0,
  0,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2;;
  Material {
   0.037255;0.400000;0.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.668000;0.442400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.800000;0.768800;0.800000;;
   25.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.500000;0.258824;0.237255;1.000000;;
   2.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  181;
  -0.032603;0.193815;0.980496;,
  -0.084001;-0.241930;0.966651;,
  -0.032603;0.193815;-0.980496;,
  -0.084001;-0.241930;-0.966651;,
  -0.829880;-0.007118;0.557897;,
  -0.829880;-0.007113;-0.557897;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.847946;0.000000;-0.530083;,
  0.847946;0.000000;0.530083;,
  0.941556;-0.213287;0.260733;,
  0.941556;-0.213287;-0.260733;,
  0.941556;0.213287;-0.260733;,
  0.941556;0.213287;0.260733;,
  -0.071128;0.381568;-0.921600;,
  0.840077;-0.200898;0.503896;,
  0.840077;0.200898;0.503896;,
  -0.071128;-0.381568;-0.921600;,
  -0.070910;0.383006;-0.921020;,
  -0.101076;-0.378536;-0.920051;,
  -0.070910;0.383006;0.921020;,
  -0.101076;-0.378536;0.920051;,
  -0.071128;0.381568;0.921600;,
  -0.071128;-0.381568;0.921600;,
  0.840077;0.200898;-0.503896;,
  0.840077;-0.200898;-0.503896;,
  -0.065491;0.921947;-0.381740;,
  -0.065491;0.921947;0.381740;,
  -0.056150;0.922542;-0.381790;,
  -0.056150;0.922542;0.381790;,
  0.889706;-0.410387;-0.200014;,
  0.889706;-0.410387;0.200014;,
  -0.056149;-0.922542;-0.381790;,
  0.889706;0.410387;0.200014;,
  0.889706;0.410387;-0.200014;,
  -0.056149;-0.922542;0.381790;,
  -0.138502;-0.914574;-0.379963;,
  -0.138502;-0.914574;0.379963;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.997228;0.000000;0.074400;,
  -0.997228;0.000000;-0.074400;,
  -0.978322;0.000000;0.207091;,
  -0.978322;0.000000;-0.207091;,
  -0.293981;-0.015247;0.955690;,
  -0.293981;-0.015237;-0.955690;,
  0.259016;-0.008257;-0.965838;,
  0.259016;-0.008262;0.965838;,
  -0.348511;0.000000;-0.937305;,
  -0.348510;0.000000;0.937305;,
  0.363205;0.000000;-0.931709;,
  0.363205;0.000000;0.931709;,
  -0.857685;0.514176;0.000000;,
  0.771246;0.636537;0.000000;,
  -0.044024;0.999030;0.000000;,
  -0.459510;0.888172;0.000000;,
  0.302646;0.953103;0.000000;,
  -0.986556;0.163423;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.875438;0.483330;0.000000;,
  -0.969923;0.243410;0.000000;,
  0.935381;0.353642;0.000000;,
  -0.989696;0.143182;0.000000;,
  0.726505;0.687161;0.000000;,
  -0.972334;-0.233593;0.000000;,
  -0.998777;0.049452;0.000000;,
  -0.055058;0.382273;-0.922408;,
  -0.055058;-0.382273;-0.922408;,
  -0.055058;0.382273;0.922408;,
  -0.055058;-0.382273;0.922408;,
  -0.022826;0.923709;-0.382414;,
  -0.022826;0.923709;0.382414;,
  -0.022826;-0.923709;-0.382413;,
  -0.022826;-0.923709;0.382413;,
  -0.049470;0.998776;0.000000;,
  -0.611935;-0.790908;0.000000;,
  -0.893080;0.000000;-0.449898;,
  -0.566751;0.000000;0.823889;,
  -0.893080;0.000000;0.449898;,
  -0.566751;0.000000;-0.823889;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.987266;0.159079;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.987266;-0.159079;,
  0.000000;-0.977717;-0.209925;,
  0.004191;-0.979257;-0.202578;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.977717;0.209926;,
  0.004191;-0.979257;0.202579;,
  0.501386;0.000000;-0.865223;,
  0.501388;0.000000;0.865222;,
  0.000000;0.000000;1.000000;,
  -0.991434;0.130610;0.000000;,
  0.633133;0.774043;0.000000;,
  -0.055058;0.382273;-0.922408;,
  -0.055058;-0.382273;-0.922408;,
  -0.022826;0.923709;-0.382414;,
  -0.022826;-0.923709;-0.382413;,
  -0.055058;-0.382273;0.922408;,
  -0.055058;0.382273;0.922408;,
  -0.022826;-0.923709;0.382413;,
  -0.022826;0.923709;0.382414;,
  0.008381;-0.983628;-0.180018;,
  0.008381;-0.983628;0.180018;,
  0.000000;0.980299;-0.197520;,
  0.000000;0.980299;0.197520;,
  0.000000;0.975433;-0.220299;,
  0.000000;0.975432;0.220300;,
  -0.022089;0.019664;0.999563;,
  -0.022089;0.019664;-0.999563;,
  0.112126;0.376134;0.919756;,
  0.112126;-0.376134;0.919756;,
  0.112126;0.376134;-0.919756;,
  0.112126;-0.376134;-0.919756;,
  0.218809;0.345916;-0.912395;,
  0.219062;-0.346968;-0.911935;,
  0.219127;0.346929;0.911934;,
  0.219217;-0.346369;0.912125;,
  0.215283;0.909187;0.356415;,
  0.215010;0.909564;-0.355618;,
  0.219062;-0.911935;-0.346968;,
  0.219062;-0.911935;0.346968;,
  0.563897;-0.201075;-0.800993;,
  0.559847;0.180864;-0.808616;,
  0.415614;0.618846;-0.666554;,
  0.418357;-0.642253;-0.642253;,
  0.912804;0.258417;-0.316244;,
  0.912038;0.260627;0.316638;,
  0.902209;-0.303805;0.306141;,
  0.902198;-0.303868;-0.306110;,
  0.589466;0.773421;0.233130;,
  0.590474;0.773162;-0.231435;,
  0.560689;-0.199077;0.803739;,
  0.557589;0.183868;0.809498;,
  0.562498;-0.801759;-0.201936;,
  0.561681;-0.802307;0.202033;,
  0.414674;0.619991;0.666075;,
  0.417061;-0.641074;0.644270;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.157035;0.388407;0.908009;,
  -0.194119;0.254777;0.947315;,
  -0.157035;0.388407;-0.908009;,
  -0.194119;0.254777;-0.947315;,
  0.234368;0.375888;-0.896538;,
  0.555804;0.739812;-0.379157;,
  0.234368;0.375888;0.896538;,
  0.555804;0.739812;0.379157;,
  -0.018853;0.325148;0.945475;,
  0.002869;-0.000426;0.999996;,
  -0.018853;0.325148;-0.945475;,
  0.002869;-0.000426;-0.999996;,
  0.071575;0.315965;-0.946067;,
  0.001918;0.000574;-0.999998;,
  0.071575;0.315965;0.946067;,
  0.001918;0.000574;0.999998;,
  -0.270428;0.727303;0.630792;,
  0.500023;0.740200;0.449534;,
  0.641865;0.717852;0.269625;,
  -0.049233;0.773339;0.632078;,
  -0.643764;0.607116;0.465809;,
  0.166887;0.758133;0.630384;,
  -0.270337;0.727035;-0.631140;,
  0.499953;0.740076;-0.449815;,
  0.641831;0.717821;-0.269789;,
  -0.049214;0.773045;-0.632439;,
  -0.643659;0.606974;-0.466139;,
  0.166828;0.757851;-0.630738;,
  -0.329120;0.944288;-0.000454;,
  -0.921674;0.387965;-0.000099;,
  0.585736;0.810502;-0.000306;,
  0.723879;0.689927;-0.000171;,
  -0.064256;0.997933;-0.000468;,
  -0.763019;0.646377;-0.000268;,
  0.213381;0.976969;-0.000465;,
  -0.918245;0.386521;0.086186;,
  -0.918228;0.386516;-0.086383;,
  0.001104;0.001723;-0.999998;,
  0.001104;0.001723;0.999998;;
  184;
  4;11,12,13,14;,
  4;31,12,11,32;,
  4;25,13,12,26;,
  4;34,14,13,35;,
  4;16,11,14,17;,
  3;16,32,11;,
  3;31,26,12;,
  3;25,35,13;,
  3;34,17,14;,
  4;19,15,18,20;,
  4;19,27,29,15;,
  4;33,37,20,18;,
  4;19,20,3,2;,
  3;3,20,37;,
  3;27,19,2;,
  4;21,0,1,22;,
  3;0,21,28;,
  3;38,22,1;,
  4;23,21,22,24;,
  4;23,30,28,21;,
  4;38,36,24,22;,
  4;27,75,75,28;,
  4;29,27,28,30;,
  4;37,33,36,38;,
  4;37,38,76,76;,
  4;40,10,10,40;,
  4;40,40,9,9;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;42,77,77,42;,
  4;78,78,78,78;,
  4;41,79,79,41;,
  4;80,80,80,80;,
  3;8,81,8;,
  3;8,8,8;,
  3;7,82,7;,
  3;7,7,7;,
  4;44,5,5,44;,
  4;44,44,39,39;,
  4;43,4,4,43;,
  4;43,43,39,39;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;83,83,84,84;,
  4;85,85,84,84;,
  4;86,87,87,86;,
  4;86,86,88,88;,
  4;89,90,90,89;,
  4;89,89,88,88;,
  4;46,5,5,46;,
  4;45,4,4,45;,
  4;47,91,91,47;,
  4;48,92,92,48;,
  4;49,77,77,49;,
  4;50,79,79,50;,
  4;51,9,9,51;,
  4;52,10,10,52;,
  4;8,8,8,8;,
  4;56,53,53,56;,
  4;56,56,55,55;,
  4;57,54,54,57;,
  4;57,57,55,55;,
  3;59,59,59;,
  3;93,93,93;,
  4;59,59,59,59;,
  4;93,93,93,93;,
  4;61,53,53,61;,
  4;61,61,58,58;,
  4;59,59,59,59;,
  4;59,59,59,59;,
  4;62,54,54,62;,
  4;62,62,60,60;,
  4;93,93,93,93;,
  4;93,93,93,93;,
  4;63,94,94,63;,
  4;63,63,58,58;,
  4;59,59,2,59;,
  4;59,59,59,59;,
  4;64,95,95,64;,
  4;64,64,60,60;,
  4;93,0,93,93;,
  4;93,93,93,93;,
  4;66,94,94,66;,
  4;66,66,65,65;,
  4;67,96,97,68;,
  4;67,68,18,15;,
  4;67,15,29,71;,
  4;67,71,98,96;,
  4;68,97,99,73;,
  4;68,73,33,18;,
  4;70,100,101,69;,
  4;70,69,23,24;,
  4;70,24,36,74;,
  4;70,74,102,100;,
  4;69,101,103,72;,
  4;69,72,30,23;,
  4;72,103,98,71;,
  4;72,71,29,30;,
  4;73,99,102,74;,
  4;73,74,36,33;,
  4;104,104,87,87;,
  4;90,90,105,105;,
  4;47,47,46,46;,
  4;45,45,48,48;,
  4;85,106,106,85;,
  4;83,107,107,83;,
  4;106,108,108,106;,
  4;107,109,109,107;,
  4;8,8,8,8;,
  4;52,50,50,52;,
  4;51,49,49,51;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;65,65,76,76;,
  4;0,110,110,1;,
  4;3,111,111,2;,
  4;8,8,8,8;,
  4;114,116,117,115;,
  3;121,116,114;,
  3;115,117,122;,
  4;118,112,113,119;,
  3;112,118,120;,
  3;123,119,113;,
  4;120,121,140,140;,
  4;141,141,122,123;,
  4;124,117,116,125;,
  3;117,124,127;,
  3;126,125,116;,
  4;131,124,125,128;,
  4;131,136,127,124;,
  4;126,133,128,125;,
  3;121,126,116;,
  3;133,126,121;,
  3;127,122,117;,
  3;122,127,136;,
  4;128,129,130,131;,
  4;132,129,128,133;,
  4;134,130,129,135;,
  4;136,131,130,137;,
  4;132,138,135,129;,
  4;134,139,137,130;,
  4;120,132,133,121;,
  3;138,132,120;,
  4;119,134,135,118;,
  3;139,134,119;,
  3;118,135,138;,
  4;122,136,137,123;,
  3;123,137,139;,
  3;120,118,138;,
  3;119,123,139;,
  4;152,153,145,144;,
  4;150,142,143,151;,
  4;154,155,153,152;,
  4;157,156,150,151;,
  4;158,142,150,161;,
  4;159,163,156,148;,
  4;163,161,150,156;,
  4;160,159,148,149;,
  4;167,152,144,164;,
  4;165,146,154,169;,
  4;169,154,152,167;,
  4;166,147,146,165;,
  4;170,158,161,174;,
  4;170,174,167,164;,
  4;175,162,158,170;,
  4;175,170,164,168;,
  4;176,163,159,172;,
  4;176,172,165,169;,
  4;174,161,163,176;,
  4;174,176,169,167;,
  4;172,159,160,173;,
  4;172,173,166,165;,
  4;162,175,171,177;,
  4;178,171,175,168;,
  4;142,158,162,143;,
  4;145,168,164,144;,
  3;146,179,155;,
  3;157,180,148;,
  3;155,154,146;,
  3;148,156,157;;
 }
}
