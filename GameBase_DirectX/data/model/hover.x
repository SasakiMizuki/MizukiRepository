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
 64;
 -10.08680;8.28840;10.24980;,
 -1.74630;6.14610;45.02730;,
 -2.80000;15.94610;25.45180;,
 -2.80000;17.09900;7.25180;,
 2.80000;15.94610;25.45180;,
 1.74630;6.14610;45.02730;,
 10.08680;8.28840;10.24980;,
 2.80000;17.09900;7.25180;,
 -6.98870;0.85910;18.38300;,
 -4.01820;1.94610;27.28020;,
 4.01820;1.94610;27.28020;,
 6.98870;0.85910;18.38300;,
 -24.27410;0.54610;5.22940;,
 -6.98870;0.85910;18.38300;,
 -10.08680;8.28840;10.24980;,
 -22.07500;6.54910;0.55090;,
 24.27410;0.54610;5.22940;,
 22.07500;6.54910;0.55090;,
 10.08680;8.28840;10.24980;,
 6.98870;0.85910;18.38300;,
 -21.97100;7.58870;-12.96310;,
 -23.95390;0.54610;-10.34030;,
 21.97100;7.58870;-12.96310;,
 23.95390;0.54610;-10.34030;,
 15.32990;10.34610;-16.34140;,
 -2.80000;12.22370;-0.03260;,
 -15.32990;10.34610;-16.34140;,
 -2.80000;12.22370;-0.03260;,
 -10.08680;8.28840;10.24980;,
 -2.80000;17.09900;7.25180;,
 2.80000;12.22370;-0.03260;,
 10.08680;8.28840;10.24980;,
 2.80000;12.22370;-0.03260;,
 2.80000;17.09900;7.25180;,
 -4.20000;14.92960;-17.48000;,
 -15.32990;10.34610;-16.34140;,
 -4.20000;14.92960;-17.48000;,
 -6.76370;8.94610;-27.95720;,
 15.32990;10.34610;-16.34140;,
 6.76370;8.94610;-27.95720;,
 4.20000;14.92960;-17.48000;,
 4.20000;14.92960;-17.48000;,
 -5.51990;-0.23000;-12.44660;,
 5.51990;-0.23000;-12.44660;,
 -4.30720;0.54610;-21.36580;,
 -6.76370;8.94610;-27.95720;,
 4.30720;0.54610;-21.36580;,
 6.76370;8.94610;-27.95720;,
 -1.74630;6.14610;45.02730;,
 1.74630;6.14610;45.02730;,
 2.80000;15.94610;25.45180;,
 -2.80000;15.94610;25.45180;,
 -2.80000;15.94610;25.45180;,
 2.80000;15.94610;25.45180;,
 4.30720;0.54610;-21.36580;,
 -4.30720;0.54610;-21.36580;,
 -6.76370;8.94610;-27.95720;,
 6.76370;8.94610;-27.95720;,
 4.01820;1.94610;27.28020;,
 -4.01820;1.94610;27.28020;,
 -6.98870;0.85910;18.38300;,
 6.98870;0.85910;18.38300;,
 1.74630;6.14610;45.02730;,
 -1.74630;6.14610;45.02730;;
 
 60;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,6;,
 3;4,6,7;,
 3;0,8,9;,
 3;0,9,1;,
 3;10,11,6;,
 3;10,6,5;,
 3;12,13,14;,
 3;12,14,15;,
 3;16,17,18;,
 3;16,18,19;,
 3;20,21,12;,
 3;20,12,15;,
 3;22,17,16;,
 3;22,16,23;,
 3;24,18,17;,
 3;24,17,22;,
 3;25,26,14;,
 3;27,28,29;,
 3;18,24,30;,
 3;31,32,33;,
 3;26,25,34;,
 3;35,36,37;,
 3;38,39,40;,
 3;24,41,30;,
 3;26,42,21;,
 3;26,21,20;,
 3;23,43,24;,
 3;23,24,22;,
 3;44,42,26;,
 3;44,26,45;,
 3;46,47,24;,
 3;46,24,43;,
 3;42,13,12;,
 3;42,12,21;,
 3;16,19,43;,
 3;16,43,23;,
 3;48,49,50;,
 3;48,50,51;,
 3;52,53,33;,
 3;52,33,29;,
 3;29,33,32;,
 3;29,32,27;,
 3;25,30,41;,
 3;25,41,34;,
 3;39,37,36;,
 3;39,36,40;,
 3;54,55,56;,
 3;54,56,57;,
 3;43,42,44;,
 3;43,44,46;,
 3;19,13,42;,
 3;19,42,43;,
 3;58,59,60;,
 3;58,60,61;,
 3;62,63,59;,
 3;62,59,58;,
 3;15,14,26;,
 3;15,26,20;;
 
 MeshMaterialList {
  1;
  60;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "hover.tga";
   }
  }
 }
 MeshNormals {
  52;
  0.159256;0.983468;-0.086190;,
  -0.159780;0.961004;-0.225702;,
  0.272667;0.943523;-0.188195;,
  -0.269438;0.961477;-0.054452;,
  0.354397;0.919492;-0.170107;,
  -0.354462;0.881229;-0.312717;,
  0.382296;0.878869;0.285373;,
  -0.382314;0.902852;0.196709;,
  0.971994;0.018718;0.234261;,
  -0.971994;0.018718;0.234261;,
  0.944505;-0.196120;0.263527;,
  -0.944505;-0.196120;0.263527;,
  0.799262;0.259913;0.541873;,
  -0.799262;0.259913;0.541873;,
  0.137474;-0.973535;-0.182565;,
  -0.137870;-0.976835;-0.163665;,
  0.317817;-0.795366;-0.516125;,
  -0.316931;-0.879276;-0.355568;,
  0.130645;0.874354;-0.467373;,
  -0.196425;0.871377;-0.449577;,
  -0.338437;0.940710;0.022919;,
  -0.787024;0.560633;0.257454;,
  0.338437;0.940710;0.022919;,
  0.787024;0.560633;0.257454;,
  -0.808078;0.483966;0.335838;,
  -0.964287;0.264117;-0.019831;,
  -0.822365;0.568392;0.025435;,
  -0.568811;0.794906;0.211139;,
  0.808078;0.483966;0.335838;,
  0.964287;0.264117;-0.019831;,
  0.822365;0.568392;0.025435;,
  0.568811;0.794906;0.211139;,
  -0.520436;-0.535893;-0.664805;,
  -0.244093;-0.341088;-0.907787;,
  -0.361791;-0.234193;-0.902364;,
  0.244093;-0.341088;-0.907787;,
  0.520436;-0.535893;-0.664805;,
  0.361791;-0.234193;-0.902364;,
  -0.250612;-0.641922;-0.724659;,
  0.379635;-0.637269;-0.670645;,
  -0.002117;-0.996931;0.078261;,
  -0.025320;-0.999534;0.017022;,
  -0.042163;-0.999110;-0.000867;,
  0.025320;-0.999534;0.017022;,
  0.002117;-0.998387;0.056735;,
  0.042163;-0.999110;-0.000867;,
  0.000000;0.894203;0.447661;,
  0.000000;0.894203;0.447661;,
  0.000000;-0.987467;0.157829;,
  0.000000;-0.980958;0.194220;,
  0.000000;-0.973120;0.230297;,
  0.000000;-0.973120;0.230297;;
  60;
  3;21,9,7;,
  3;21,7,5;,
  3;6,8,23;,
  3;6,23,4;,
  3;21,13,11;,
  3;21,11,9;,
  3;10,12,23;,
  3;10,23,8;,
  3;24,13,21;,
  3;24,21,27;,
  3;28,31,23;,
  3;28,23,12;,
  3;26,25,24;,
  3;26,24,27;,
  3;30,31,28;,
  3;30,28,29;,
  3;22,23,31;,
  3;22,31,30;,
  3;3,20,21;,
  3;3,21,5;,
  3;23,22,2;,
  3;23,2,4;,
  3;20,3,1;,
  3;20,1,19;,
  3;22,18,0;,
  3;22,0,2;,
  3;32,15,33;,
  3;32,33,34;,
  3;35,14,36;,
  3;35,36,37;,
  3;17,15,32;,
  3;17,32,38;,
  3;16,39,36;,
  3;16,36,14;,
  3;15,40,41;,
  3;15,41,42;,
  3;43,44,14;,
  3;43,14,45;,
  3;46,47,6;,
  3;46,6,7;,
  3;7,6,4;,
  3;7,4,5;,
  3;5,4,2;,
  3;5,2,3;,
  3;3,2,0;,
  3;3,0,1;,
  3;18,19,1;,
  3;18,1,0;,
  3;16,17,38;,
  3;16,38,39;,
  3;14,15,17;,
  3;14,17,16;,
  3;44,40,15;,
  3;44,15,14;,
  3;48,49,40;,
  3;48,40,44;,
  3;50,51,49;,
  3;50,49,48;,
  3;27,21,20;,
  3;27,20,26;;
 }
 MeshTextureCoords {
  64;
  -0.674020;0.499040;,
  -0.273120;0.355990;,
  -0.522720;0.326750;,
  -0.729510;0.331160;,
  -0.486200;0.325590;,
  -0.172430;0.358790;,
  -0.671440;0.489780;,
  -0.743700;0.349170;,
  -0.558060;0.488340;,
  -0.459950;0.428550;,
  -0.403170;0.448200;,
  -0.524700;0.503520;,
  -0.378120;0.721440;,
  -0.720400;0.532210;,
  -0.670220;0.658000;,
  -0.432250;0.794210;,
  -1.374360;0.687390;,
  -1.338240;0.763250;,
  -1.084200;0.643850;,
  -1.007220;0.522400;,
  -0.448170;0.978620;,
  -0.399670;0.931540;,
  -1.349890;0.947800;,
  -1.382770;0.897950;,
  -1.218930;1.003200;,
  -0.832600;0.799080;,
  -0.589770;1.024700;,
  -0.442700;0.469110;,
  -0.294140;0.321280;,
  -0.444590;0.378470;,
  -0.947520;0.795150;,
  -0.709680;0.323640;,
  -0.558050;0.469760;,
  -0.559940;0.379130;,
  -0.822700;1.040760;,
  0.026630;0.081270;,
  -0.202890;0.106140;,
  -0.147470;0.238020;,
  -0.604910;0.084840;,
  -0.426110;0.239590;,
  -0.375920;0.107120;,
  -0.995070;1.034870;,
  -0.779400;0.945630;,
  -1.005940;0.937890;,
  -0.813450;1.066710;,
  -0.775690;1.173020;,
  -0.990220;1.060670;,
  -1.053280;1.163530;,
  -0.806300;0.178380;,
  -0.877970;0.175930;,
  -0.925780;0.457780;,
  -0.810870;0.461710;,
  -0.447930;0.128550;,
  -0.563280;0.129210;,
  -0.902110;0.183560;,
  -0.781560;0.183710;,
  -0.741720;0.317450;,
  -0.931020;0.317220;,
  -0.376250;0.337220;,
  -0.274910;0.336300;,
  -0.236350;0.453120;,
  -0.412600;0.454730;,
  -0.349930;0.106770;,
  -0.305890;0.106370;;
 }
}
