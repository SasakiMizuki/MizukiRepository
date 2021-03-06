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
 40;
 -200.00000;818.60168;-160.00000;,
 -160.00000;818.60168;-200.00000;,
 -160.00000;-1.39830;-200.00000;,
 -200.00000;-1.39830;-160.00000;,
 -160.00000;-1.39830;200.00000;,
 160.00000;-1.39830;200.00000;,
 160.00000;818.60168;200.00000;,
 -160.00000;818.60168;200.00000;,
 160.00000;-1.39830;200.00000;,
 200.00000;-1.39830;160.00000;,
 200.00000;818.60168;160.00000;,
 160.00000;818.60168;200.00000;,
 200.00000;818.60168;160.00000;,
 200.00000;-1.39830;160.00000;,
 200.00000;-1.39830;-160.00000;,
 200.00000;818.60168;-160.00000;,
 200.00000;818.60168;-160.00000;,
 200.00000;-1.39830;-160.00000;,
 160.00000;-1.39830;-200.00000;,
 160.00000;818.60168;-200.00000;,
 -160.00000;-1.39830;200.00000;,
 -160.00000;818.60168;200.00000;,
 -200.00000;818.60168;160.00000;,
 -200.00000;-1.39830;160.00000;,
 -200.00000;-1.39830;160.00000;,
 -200.00000;818.60168;160.00000;,
 -200.00000;818.60168;-160.00000;,
 -200.00000;-1.39830;-160.00000;,
 -160.00000;818.60168;-200.00000;,
 160.00000;818.60168;-200.00000;,
 160.00000;-1.39830;-200.00000;,
 -160.00000;-1.39830;-200.00000;,
 -160.00000;818.60168;200.00000;,
 -200.00000;818.60168;-160.00000;,
 -200.00000;818.60168;160.00000;,
 -160.00000;818.60168;-200.00000;,
 160.00000;818.60168;200.00000;,
 160.00000;818.60168;-200.00000;,
 200.00000;818.60168;160.00000;,
 200.00000;818.60168;-160.00000;;
 
 14;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 3;32,33,34;,
 3;32,35,33;,
 3;36,35,32;,
 3;36,37,35;,
 3;37,38,39;,
 3;38,37,36;;
 
 MeshMaterialList {
  1;
  14;
  0,
  0,
  0,
  0,
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
    "obj00.tga";
   }
  }
 }
 MeshNormals {
  9;
  -0.382683;0.000000;0.923880;,
  0.382683;0.000000;0.923880;,
  0.923880;0.000000;0.382683;,
  -0.923880;0.000000;0.382683;,
  0.923880;0.000000;-0.382683;,
  -0.923880;0.000000;-0.382683;,
  -0.382683;0.000000;-0.923880;,
  0.382683;0.000000;-0.923880;,
  0.000000;1.000000;0.000000;;
  14;
  4;5,6,6,5;,
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,2,4,4;,
  4;4,4,7,7;,
  4;0,0,3,3;,
  4;3,3,5,5;,
  4;6,7,7,6;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;;
 }
 MeshTextureCoords {
  40;
  -0.997690;0.004220;,
  -0.967330;0.004450;,
  -0.969890;0.501820;,
  -1.000250;0.501600;,
  -0.499560;0.500030;,
  -0.974730;0.500030;,
  -0.974730;-0.002410;,
  -0.499560;-0.002410;,
  -0.969350;0.495070;,
  -0.997540;0.495070;,
  -0.997540;0.002560;,
  -0.969350;0.002560;,
  -0.523650;0.000210;,
  -0.523650;0.500150;,
  -0.968680;0.500150;,
  -0.968680;0.000210;,
  -0.969430;-0.001020;,
  -0.969430;0.496250;,
  -1.000770;0.496250;,
  -1.000770;-0.001020;,
  -0.998690;0.493060;,
  -0.998690;0.000540;,
  -0.969490;0.000540;,
  -0.969490;0.493060;,
  -0.973250;0.498220;,
  -0.973250;0.000770;,
  -0.512140;0.000770;,
  -0.512140;0.498220;,
  -0.969380;0.001510;,
  -0.507180;0.001510;,
  -0.507180;0.488960;,
  -0.969380;0.488960;,
  -0.450920;0.007670;,
  -0.499170;0.440310;,
  -0.500380;0.055860;,
  -0.449400;0.488220;,
  -0.053980;0.006530;,
  -0.052470;0.487090;,
  -0.004210;0.054450;,
  -0.003000;0.438890;;
 }
}
