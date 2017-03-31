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
 81;
 -300.00000;0.03686;400.00001;,
 -300.00000;0.07686;300.00000;,
 -400.00001;0.03686;300.00000;,
 -400.00001;0.00000;400.00001;,
 -200.00000;0.00000;400.00001;,
 -200.00000;0.03686;300.00000;,
 -100.00000;-0.09940;400.00001;,
 -100.00000;-0.07720;300.00000;,
 0.00000;-0.23482;400.00001;,
 0.00000;-0.23658;300.00000;,
 100.00000;-0.29552;400.00001;,
 100.00000;-0.31436;300.00000;,
 200.00000;-0.30856;400.00001;,
 200.00000;62.78133;300.00000;,
 300.00000;-0.25522;400.00001;,
 300.00000;62.80571;300.00000;,
 400.00001;-0.11988;400.00001;,
 400.00001;-0.22218;300.00000;,
 -300.00000;10.27109;200.00000;,
 -400.00001;0.00000;200.00000;,
 -200.00000;42.64256;200.00000;,
 -100.00000;-0.10750;200.00000;,
 0.00000;-0.24846;200.00000;,
 100.00000;-0.27794;200.00000;,
 200.00000;-0.28580;200.00000;,
 300.00000;20.17692;200.00000;,
 400.00001;-0.24482;200.00000;,
 -300.00000;10.15461;100.00000;,
 -400.00001;-0.09178;100.00000;,
 -200.00000;-0.13976;100.00000;,
 -100.00000;-0.22324;100.00000;,
 0.00000;-0.25712;100.00000;,
 100.00000;18.57450;100.00000;,
 200.00000;20.30948;100.00000;,
 300.00000;13.42190;100.00000;,
 400.00001;-0.21864;100.00000;,
 -300.00000;-0.28022;0.00000;,
 -400.00001;-0.22238;0.00000;,
 -200.00000;-0.36416;0.00000;,
 -100.00000;-0.39588;0.00000;,
 0.00000;-8.89892;-0.00000;,
 100.00000;-0.34862;-0.00000;,
 200.00000;-0.25552;-0.00000;,
 300.00000;13.43084;0.00000;,
 400.00001;-0.19864;-0.00000;,
 -300.00000;-0.41244;-100.00000;,
 -400.00001;-0.32360;-100.00000;,
 -200.00000;-29.48446;-100.00000;,
 -100.00000;-9.03992;-100.00000;,
 0.00000;-8.97900;-100.00000;,
 100.00000;-0.35670;-100.00000;,
 200.00000;-0.25232;-100.00000;,
 300.00000;-0.19614;-100.00000;,
 400.00001;-0.17124;-100.00000;,
 -300.00000;-0.47202;-200.00000;,
 -400.00001;-0.42296;-200.00000;,
 -200.00000;-0.56706;-200.00000;,
 -100.00000;19.88268;-200.00000;,
 0.00000;14.82781;-200.00000;,
 100.00000;14.96779;-200.00000;,
 200.00000;-0.19484;-200.00000;,
 300.00000;35.72423;-200.00000;,
 400.00001;-0.06920;-200.00000;,
 -300.00000;-0.34872;-300.00000;,
 -400.00001;-0.35770;-300.00000;,
 -200.00000;-9.07551;-300.00000;,
 -100.00000;-9.10049;-300.00000;,
 0.00000;14.83817;-300.00000;,
 100.00000;-0.37896;-300.00000;,
 200.00000;35.64606;-300.00000;,
 300.00000;-0.01568;-300.00000;,
 400.00001;0.02826;-300.00000;,
 -300.00000;-0.33962;-400.00001;,
 -400.00001;-0.31612;-400.00001;,
 -200.00000;-0.50128;-400.00001;,
 -100.00000;-0.48086;-400.00001;,
 0.00000;-0.43158;-400.00001;,
 100.00000;-0.33386;-400.00001;,
 200.00000;-0.15442;-400.00001;,
 300.00000;0.01408;-400.00001;,
 400.00001;0.06678;-400.00001;;
 
 128;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,1;,
 3;4,1,0;,
 3;6,7,5;,
 3;6,5,4;,
 3;8,9,7;,
 3;8,7,6;,
 3;10,11,9;,
 3;10,9,8;,
 3;12,13,11;,
 3;12,11,10;,
 3;14,15,13;,
 3;14,13,12;,
 3;16,17,15;,
 3;16,15,14;,
 3;1,18,19;,
 3;1,19,2;,
 3;5,20,18;,
 3;5,18,1;,
 3;7,21,20;,
 3;7,20,5;,
 3;9,22,21;,
 3;9,21,7;,
 3;11,23,22;,
 3;11,22,9;,
 3;13,24,23;,
 3;13,23,11;,
 3;15,25,24;,
 3;15,24,13;,
 3;17,26,25;,
 3;17,25,15;,
 3;18,27,28;,
 3;18,28,19;,
 3;20,29,27;,
 3;20,27,18;,
 3;21,30,29;,
 3;21,29,20;,
 3;22,31,30;,
 3;22,30,21;,
 3;23,32,31;,
 3;23,31,22;,
 3;24,33,32;,
 3;24,32,23;,
 3;25,34,33;,
 3;25,33,24;,
 3;26,35,34;,
 3;26,34,25;,
 3;27,36,37;,
 3;27,37,28;,
 3;29,38,36;,
 3;29,36,27;,
 3;30,39,38;,
 3;30,38,29;,
 3;31,40,39;,
 3;31,39,30;,
 3;32,41,40;,
 3;32,40,31;,
 3;33,42,41;,
 3;33,41,32;,
 3;34,43,42;,
 3;34,42,33;,
 3;35,44,43;,
 3;35,43,34;,
 3;36,45,46;,
 3;36,46,37;,
 3;38,47,45;,
 3;38,45,36;,
 3;39,48,47;,
 3;39,47,38;,
 3;40,49,48;,
 3;40,48,39;,
 3;41,50,49;,
 3;41,49,40;,
 3;42,51,50;,
 3;42,50,41;,
 3;43,52,51;,
 3;43,51,42;,
 3;44,53,52;,
 3;44,52,43;,
 3;45,54,55;,
 3;45,55,46;,
 3;47,56,54;,
 3;47,54,45;,
 3;48,57,56;,
 3;48,56,47;,
 3;49,58,57;,
 3;49,57,48;,
 3;50,59,58;,
 3;50,58,49;,
 3;51,60,59;,
 3;51,59,50;,
 3;52,61,60;,
 3;52,60,51;,
 3;53,62,61;,
 3;53,61,52;,
 3;54,63,64;,
 3;54,64,55;,
 3;56,65,63;,
 3;56,63,54;,
 3;57,66,65;,
 3;57,65,56;,
 3;58,67,66;,
 3;58,66,57;,
 3;59,68,67;,
 3;59,67,58;,
 3;60,69,68;,
 3;60,68,59;,
 3;61,70,69;,
 3;61,69,60;,
 3;62,71,70;,
 3;62,70,61;,
 3;63,72,73;,
 3;63,73,64;,
 3;65,74,72;,
 3;65,72,63;,
 3;66,75,74;,
 3;66,74,65;,
 3;67,76,75;,
 3;67,75,66;,
 3;68,77,76;,
 3;68,76,67;,
 3;69,78,77;,
 3;69,77,68;,
 3;70,79,78;,
 3;70,78,69;,
 3;71,80,79;,
 3;71,79,70;;
 
 MeshMaterialList {
  1;
  128;
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
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
   TextureFilename {
    "land.jpg";
   }
  }
 }
 MeshNormals {
  82;
  -0.000369;1.000000;0.000369;,
  -0.000133;1.000000;0.000390;,
  0.000588;1.000000;0.000379;,
  0.001163;0.999999;0.000271;,
  0.001185;0.999999;0.000062;,
  0.000505;1.000000;-0.000131;,
  -0.167105;0.919357;0.356173;,
  -0.000601;0.845822;0.533465;,
  0.287327;0.913640;0.287586;,
  -0.000390;1.000000;0.000133;,
  -0.016912;0.999282;0.033914;,
  -0.047960;0.987785;0.148256;,
  0.068156;0.995436;0.066790;,
  0.001127;0.999999;-0.000127;,
  -0.175849;0.980945;0.082611;,
  -0.230195;0.945564;0.230041;,
  0.164477;0.985677;-0.037252;,
  0.423226;0.898484;-0.116641;,
  -0.068232;0.997114;0.033280;,
  -0.152219;0.983541;0.097349;,
  0.047847;0.998853;0.001573;,
  0.130908;0.989376;-0.063231;,
  0.000754;1.000000;-0.000201;,
  -0.125676;0.991645;-0.029084;,
  -0.071170;0.985361;-0.154915;,
  0.103547;0.987812;-0.116211;,
  0.178470;0.983699;-0.022022;,
  -0.102011;0.994783;-0.001124;,
  -0.053605;0.993296;-0.102417;,
  0.096436;0.984264;-0.148066;,
  0.000679;0.999999;-0.001350;,
  -0.047265;0.998881;0.001658;,
  -0.082180;0.996432;0.019238;,
  -0.016255;0.998919;-0.043547;,
  0.079020;0.995293;-0.056097;,
  0.135118;0.990830;0.000182;,
  -0.033671;0.998804;-0.035448;,
  0.017629;0.999212;-0.035555;,
  0.045964;0.994508;-0.094032;,
  -0.005012;0.995870;-0.090649;,
  -0.031058;0.996748;-0.074352;,
  -0.045864;0.994313;-0.096115;,
  -0.034720;0.997111;-0.067558;,
  0.022256;0.998732;-0.045162;,
  0.089907;0.994950;-0.044626;,
  0.000785;0.999999;-0.001109;,
  0.093140;0.994575;-0.046324;,
  0.027399;0.999518;-0.014573;,
  -0.085454;0.990136;0.111030;,
  -0.034785;0.991647;0.124203;,
  -0.029130;0.995570;0.089396;,
  0.001866;0.999994;0.002964;,
  -0.032295;0.997227;0.067048;,
  0.115167;0.986536;0.116117;,
  0.000623;1.000000;-0.000312;,
  0.047507;0.997758;0.047141;,
  -0.084566;0.990124;0.111820;,
  -0.051062;0.998392;0.024616;,
  -0.037713;0.997653;0.057145;,
  0.074624;0.997212;0.000607;,
  -0.115755;0.983181;0.141266;,
  0.061031;0.996189;0.062305;,
  0.224183;0.968507;-0.108335;,
  0.000104;1.000000;0.000767;,
  0.029134;0.999483;-0.013584;,
  -0.004050;0.998914;-0.046408;,
  -0.070793;0.996171;-0.051302;,
  -0.028683;0.997656;-0.062126;,
  -0.037322;0.999054;-0.022338;,
  -0.063132;0.996114;-0.061415;,
  0.163381;0.972870;-0.163801;,
  -0.000469;1.000000;0.000552;,
  0.000073;1.000000;0.000253;,
  0.029643;0.999152;0.028584;,
  0.000552;0.996331;0.085579;,
  -0.078526;0.996893;0.006231;,
  0.049346;0.993720;-0.100430;,
  -0.116909;0.986455;-0.115056;,
  0.107626;0.968560;-0.224294;,
  -0.000884;1.000000;0.000327;,
  -0.000527;1.000000;0.000385;,
  0.000066;0.845835;-0.533444;;
  128;
  3;1,10,9;,
  3;1,9,0;,
  3;2,11,10;,
  3;2,10,1;,
  3;3,12,11;,
  3;3,11,2;,
  3;4,13,12;,
  3;4,12,3;,
  3;5,14,13;,
  3;5,13,4;,
  3;6,15,14;,
  3;6,14,5;,
  3;7,16,15;,
  3;7,15,6;,
  3;8,17,16;,
  3;8,16,7;,
  3;10,19,18;,
  3;10,18,9;,
  3;11,20,19;,
  3;11,19,10;,
  3;12,21,20;,
  3;12,20,11;,
  3;13,22,21;,
  3;13,21,12;,
  3;14,23,22;,
  3;14,22,13;,
  3;81,24,23;,
  3;15,23,14;,
  3;16,25,24;,
  3;16,24,15;,
  3;17,26,25;,
  3;17,25,16;,
  3;19,28,27;,
  3;19,27,18;,
  3;20,29,28;,
  3;20,28,19;,
  3;21,30,29;,
  3;21,29,20;,
  3;22,31,30;,
  3;22,30,21;,
  3;23,32,31;,
  3;23,31,22;,
  3;24,33,32;,
  3;24,32,23;,
  3;25,34,33;,
  3;25,33,24;,
  3;26,35,34;,
  3;26,34,25;,
  3;28,37,36;,
  3;28,36,27;,
  3;29,38,37;,
  3;29,37,28;,
  3;30,39,38;,
  3;30,38,29;,
  3;31,40,39;,
  3;31,39,30;,
  3;32,41,40;,
  3;32,40,31;,
  3;33,42,41;,
  3;33,41,32;,
  3;34,43,42;,
  3;34,42,33;,
  3;35,44,43;,
  3;35,43,34;,
  3;37,46,45;,
  3;37,45,36;,
  3;38,47,46;,
  3;38,46,37;,
  3;39,48,47;,
  3;39,47,38;,
  3;40,49,48;,
  3;40,48,39;,
  3;41,50,49;,
  3;41,49,40;,
  3;42,51,50;,
  3;42,50,41;,
  3;43,52,51;,
  3;43,51,42;,
  3;44,53,52;,
  3;44,52,43;,
  3;46,55,54;,
  3;46,54,45;,
  3;47,56,55;,
  3;47,55,46;,
  3;48,57,56;,
  3;48,56,47;,
  3;49,58,57;,
  3;49,57,48;,
  3;50,59,58;,
  3;50,58,49;,
  3;51,60,59;,
  3;51,59,50;,
  3;52,61,60;,
  3;52,60,51;,
  3;53,62,61;,
  3;53,61,52;,
  3;55,64,63;,
  3;55,63,54;,
  3;56,65,64;,
  3;56,64,55;,
  3;57,66,65;,
  3;57,65,56;,
  3;58,67,66;,
  3;58,66,57;,
  3;59,68,67;,
  3;59,67,58;,
  3;60,69,68;,
  3;60,68,59;,
  3;61,70,69;,
  3;61,69,60;,
  3;62,71,70;,
  3;62,70,61;,
  3;64,73,72;,
  3;64,72,63;,
  3;65,74,73;,
  3;65,73,64;,
  3;66,75,74;,
  3;66,74,65;,
  3;67,76,75;,
  3;67,75,66;,
  3;68,77,76;,
  3;68,76,67;,
  3;69,78,77;,
  3;69,77,68;,
  3;70,79,78;,
  3;70,78,69;,
  3;71,80,79;,
  3;71,79,70;;
 }
 MeshTextureCoords {
  81;
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;;
 }
 MeshVertexColors {
  81;
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
  80;1.000000;1.000000;1.000000;1.000000;;
 }
}
