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
 28;
 0.16560;0.26563;-0.05601;,
 -0.02110;0.18829;-0.05601;,
 0.10790;0.18829;0.12155;,
 0.16560;0.26563;-0.05601;,
 0.10790;0.18829;-0.23357;,
 0.16560;0.26563;-0.05601;,
 0.31664;0.18829;-0.16575;,
 0.16560;0.26563;-0.05601;,
 0.31664;0.18829;0.05373;,
 0.16560;0.26563;-0.05601;,
 0.10790;0.18829;0.12155;,
 -0.09844;0.00159;-0.05601;,
 0.08401;0.00159;0.19510;,
 0.08401;0.00159;-0.30712;,
 0.37921;0.00159;-0.21121;,
 0.37921;0.00159;0.09918;,
 0.08401;0.00159;0.19510;,
 -0.02110;-0.18511;-0.05601;,
 0.10790;-0.18511;0.12155;,
 0.10790;-0.18511;-0.23357;,
 0.31664;-0.18511;-0.16575;,
 0.31664;-0.18511;0.05373;,
 0.10790;-0.18511;0.12155;,
 0.16560;-0.26244;-0.05601;,
 0.16560;-0.26244;-0.05601;,
 0.16560;-0.26244;-0.05601;,
 0.16560;-0.26244;-0.05601;,
 0.16560;-0.26244;-0.05601;;
 
 20;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 4;2,1,11,12;,
 4;1,4,13,11;,
 4;4,6,14,13;,
 4;6,8,15,14;,
 4;8,10,16,15;,
 4;12,11,17,18;,
 4;11,13,19,17;,
 4;13,14,20,19;,
 4;14,15,21,20;,
 4;15,16,22,21;,
 3;18,17,23;,
 3;17,19,24;,
 3;19,20,25;,
 3;20,21,26;,
 3;21,22,27;;
 
 MeshMaterialList {
  5;
  20;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  21;
  0.000001;1.000000;0.000000;,
  -0.211688;0.728505;0.651513;,
  -0.685038;0.728507;0.000000;,
  -0.211689;0.728506;-0.651511;,
  0.554208;0.728506;-0.402657;,
  0.554209;0.728505;0.402656;,
  -0.809015;0.000001;0.587788;,
  -0.809015;0.000000;-0.587788;,
  0.309014;0.000001;-0.951058;,
  1.000000;0.000000;-0.000000;,
  -0.376716;-0.794344;0.476553;,
  -0.569637;-0.794345;0.211019;,
  -0.376716;-0.794345;-0.476551;,
  0.336812;-0.794345;-0.505542;,
  0.584881;-0.794345;0.164108;,
  0.000001;-1.000000;0.000000;,
  0.309016;0.000001;0.951057;,
  -0.767090;-0.317742;-0.557327;,
  0.293000;-0.317742;-0.901771;,
  0.948178;-0.317740;-0.000000;,
  0.293002;-0.317740;0.901771;;
  20;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,1,5;,
  4;1,2,6,6;,
  4;2,3,7,7;,
  4;3,4,8,8;,
  4;4,5,9,9;,
  4;5,1,16,16;,
  4;6,6,11,10;,
  4;7,7,12,17;,
  4;8,8,13,18;,
  4;9,9,14,19;,
  4;16,16,20,20;,
  3;10,11,15;,
  3;11,12,15;,
  3;12,13,15;,
  3;13,14,15;,
  3;14,10,15;;
 }
 MeshTextureCoords {
  28;
  0.100000;0.000000;,
  0.200000;0.250000;,
  0.000000;0.250000;,
  0.300000;0.000000;,
  0.400000;0.250000;,
  0.500000;0.000000;,
  0.600000;0.250000;,
  0.700000;0.000000;,
  0.800000;0.250000;,
  0.900000;0.000000;,
  1.000000;0.250000;,
  0.200000;0.500000;,
  0.000000;0.500000;,
  0.400000;0.500000;,
  0.600000;0.500000;,
  0.800000;0.500000;,
  1.000000;0.500000;,
  0.200000;0.750000;,
  0.000000;0.750000;,
  0.400000;0.750000;,
  0.600000;0.750000;,
  0.800000;0.750000;,
  1.000000;0.750000;,
  0.100000;1.000000;,
  0.300000;1.000000;,
  0.500000;1.000000;,
  0.700000;1.000000;,
  0.900000;1.000000;;
 }
 MeshVertexColors {
  28;
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
  27;1.000000;1.000000;1.000000;1.000000;;
 }
}
