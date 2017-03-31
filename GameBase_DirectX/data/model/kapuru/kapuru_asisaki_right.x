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
 98;
 0.13666;-0.00058;-0.13476;,
 0.24135;-0.45526;-0.39797;,
 -0.19992;-0.45526;-0.39797;,
 -0.09523;-0.00058;-0.13476;,
 -0.09523;-0.00058;-0.13476;,
 -0.19992;-0.45526;-0.39797;,
 -0.19992;-0.45526;0.17139;,
 -0.09523;-0.00058;0.07617;,
 -0.09523;-0.00058;0.07617;,
 -0.19992;-0.45526;0.17139;,
 0.24135;-0.45526;0.17139;,
 0.13666;-0.00058;0.07617;,
 0.13666;-0.00058;0.07617;,
 0.24135;-0.45526;0.17139;,
 0.24135;-0.45526;-0.39797;,
 0.13666;-0.00058;-0.13476;,
 0.24135;-0.45526;-0.39797;,
 -0.19992;-0.45526;-0.39797;,
 0.08926;-0.39658;-0.62065;,
 0.08926;-0.47885;-0.61345;,
 -0.07842;-0.47885;-0.61345;,
 -0.07842;-0.39658;-0.62065;,
 -0.07842;-0.39658;-0.62065;,
 -0.07842;-0.47885;-0.61345;,
 -0.13472;-0.47962;-0.30406;,
 -0.13472;-0.29576;-0.32015;,
 -0.13472;-0.29576;-0.32015;,
 -0.13472;-0.47962;-0.30406;,
 0.14556;-0.47962;-0.30406;,
 0.14556;-0.29576;-0.32015;,
 0.14556;-0.29576;-0.32015;,
 0.14556;-0.47962;-0.30406;,
 0.08926;-0.47885;-0.61345;,
 0.08926;-0.39658;-0.62065;,
 0.08926;-0.39658;-0.62065;,
 -0.07842;-0.39658;-0.62065;,
 0.08926;-0.47885;-0.61345;,
 -0.07842;-0.47885;-0.61345;,
 -0.39854;-0.40018;-0.22440;,
 -0.39041;-0.47753;-0.22305;,
 -0.42841;-0.47885;-0.06975;,
 -0.43654;-0.40150;-0.07110;,
 -0.43654;-0.40150;-0.07110;,
 -0.42841;-0.47885;-0.06975;,
 -0.15836;-0.47460;0.05186;,
 -0.12554;-0.30175;0.04885;,
 -0.12554;-0.30175;0.04885;,
 -0.15836;-0.47460;0.05186;,
 -0.09484;-0.47240;-0.20437;,
 -0.11301;-0.29954;-0.20739;,
 -0.11301;-0.29954;-0.20739;,
 -0.09484;-0.47240;-0.20437;,
 -0.39041;-0.47753;-0.22305;,
 -0.39854;-0.40018;-0.22440;,
 -0.39854;-0.40018;-0.22440;,
 -0.43654;-0.40150;-0.07110;,
 -0.39041;-0.47753;-0.22305;,
 -0.42841;-0.47885;-0.06975;,
 0.40391;-0.40013;-0.22458;,
 0.44184;-0.40479;-0.07133;,
 0.43236;-0.48200;-0.07133;,
 0.39443;-0.47735;-0.22458;,
 0.44184;-0.40479;-0.07133;,
 0.18357;-0.30263;0.05034;,
 0.16238;-0.47517;0.05034;,
 0.43236;-0.48200;-0.07133;,
 0.18357;-0.30263;0.05034;,
 0.12018;-0.29484;-0.20582;,
 0.09899;-0.46738;-0.20582;,
 0.16238;-0.47517;0.05034;,
 0.12018;-0.29484;-0.20582;,
 0.40391;-0.40013;-0.22458;,
 0.39443;-0.47735;-0.22458;,
 0.09899;-0.46738;-0.20582;,
 0.44184;-0.40479;-0.07133;,
 0.40391;-0.40013;-0.22458;,
 0.39443;-0.47735;-0.22458;,
 0.43236;-0.48200;-0.07133;,
 0.09946;-0.38963;0.33782;,
 -0.06823;-0.38963;0.33782;,
 -0.06823;-0.47902;0.41190;,
 0.09946;-0.47902;0.41190;,
 -0.06823;-0.38963;0.33782;,
 -0.12453;-0.29593;0.11859;,
 -0.12453;-0.47978;0.10251;,
 -0.06823;-0.47902;0.41190;,
 -0.12453;-0.29593;0.11859;,
 0.15576;-0.29593;0.11859;,
 0.15576;-0.47978;0.10251;,
 -0.12453;-0.47978;0.10251;,
 0.15576;-0.29593;0.11859;,
 0.09946;-0.38963;0.33782;,
 0.09946;-0.47902;0.41190;,
 0.15576;-0.47978;0.10251;,
 -0.06823;-0.38963;0.33782;,
 0.09946;-0.38963;0.33782;,
 0.09946;-0.47902;0.41190;,
 -0.06823;-0.47902;0.41190;;
 
 29;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,13,6,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;30,34,35,25;,
 4;36,31,24,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;50,54,55,45;,
 4;56,51,44,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;70,63,74,75;,
 4;76,77,64,73;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;90,83,94,95;,
 4;96,97,84,93;;
 
 MeshMaterialList {
  5;
  29;
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  0,
  3,
  3,
  3,
  3,
  3,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  0,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.225882;0.467451;0.241569;1.000000;;
   5.000000;
   0.200000;0.200000;0.200000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.445490;0.445490;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.440000;0.245020;0.245020;;
  }
  Material {
   0.254118;0.257255;0.263529;1.000000;;
   5.000000;
   0.740000;0.740000;0.740000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.200000;0.200000;0.200000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "kapuru.png";
   }
  }
 }
 MeshNormals {
  30;
  0.000000;0.500992;-0.865452;,
  -0.974502;0.224381;0.000000;,
  0.000000;0.204986;0.978765;,
  0.000000;-0.087155;-0.996195;,
  -0.983715;-0.015665;-0.179050;,
  0.000000;0.087154;0.996195;,
  -0.964979;-0.105632;-0.240120;,
  -0.397310;0.030842;0.917166;,
  0.988826;-0.036556;0.144520;,
  0.963062;-0.118252;-0.241925;,
  0.409303;-0.050255;0.911013;,
  -0.963063;0.118247;0.241923;,
  0.000000;0.801285;0.598282;,
  0.000000;0.638089;0.769962;,
  -0.975813;0.062982;0.209338;,
  0.000000;0.087154;-0.996195;,
  0.974502;0.224379;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.983716;-0.015664;-0.179044;,
  0.000000;0.948068;-0.318069;,
  0.000000;-0.999997;-0.002476;,
  0.063240;-0.010769;-0.997940;,
  -0.315573;0.948062;-0.039896;,
  0.017623;-0.999836;-0.004229;,
  -0.063116;0.007750;-0.997976;,
  0.344058;0.937237;-0.056666;,
  -0.035065;-0.999150;-0.021681;,
  0.975814;0.062981;0.209334;,
  0.000000;0.919524;0.393034;,
  0.000000;-0.999997;0.002479;;
  29;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;12,12,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;27,27,27,27;,
  4;28,28,12,12;,
  4;29,29,29,29;;
 }
 MeshTextureCoords {
  98;
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
 MeshVertexColors {
  98;
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
  97;1.000000;1.000000;1.000000;1.000000;;
 }
}
