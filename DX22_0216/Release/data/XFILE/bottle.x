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
 82;
 0.00000;3.19738;0.00000;,
 0.15700;3.19738;-0.15700;,
 0.00000;3.19738;-0.22203;,
 0.22203;3.19738;0.00000;,
 0.15700;3.19738;0.15700;,
 -0.00000;3.19738;0.22203;,
 -0.15700;3.19738;0.15700;,
 -0.22203;3.19738;-0.00000;,
 -0.15700;3.19738;-0.15700;,
 0.17202;2.95584;-0.17202;,
 0.00000;2.95584;-0.24327;,
 0.24327;2.95584;0.00000;,
 0.17202;2.95584;0.17202;,
 -0.00000;2.95584;0.24327;,
 -0.17202;2.95584;0.17202;,
 -0.24327;2.95584;-0.00000;,
 -0.17202;2.95584;-0.17202;,
 0.18660;2.22207;-0.18660;,
 0.00000;2.22207;-0.26390;,
 0.26390;2.22207;0.00000;,
 0.18660;2.22207;0.18660;,
 -0.00000;2.22207;0.26390;,
 -0.18660;2.22207;0.18660;,
 -0.26390;2.22207;-0.00000;,
 -0.18660;2.22207;-0.18660;,
 0.36411;1.93503;-0.36411;,
 0.00000;1.93503;-0.51493;,
 0.51493;1.93503;0.00000;,
 0.36411;1.93503;0.36411;,
 -0.00000;1.93503;0.51493;,
 -0.36411;1.93503;0.36411;,
 -0.51493;1.93503;-0.00000;,
 -0.36411;1.93503;-0.36411;,
 0.43156;1.65153;-0.43156;,
 0.00000;1.65153;-0.61032;,
 0.61032;1.65153;0.00000;,
 0.43156;1.65153;0.43156;,
 -0.00000;1.65153;0.61032;,
 -0.43156;1.65153;0.43156;,
 -0.61032;1.65153;-0.00000;,
 -0.43156;1.65153;-0.43156;,
 0.43156;0.19619;-0.43156;,
 0.00000;0.19619;-0.61032;,
 0.61032;0.19619;0.00000;,
 0.43156;0.19619;0.43156;,
 -0.00000;0.19619;0.61032;,
 -0.43156;0.19619;0.43156;,
 -0.61032;0.19619;-0.00000;,
 -0.43156;0.19619;-0.43156;,
 0.42499;0.12657;-0.42499;,
 0.00000;0.12657;-0.60103;,
 0.60103;0.12657;0.00000;,
 0.42499;0.12657;0.42499;,
 -0.00000;0.12657;0.60103;,
 -0.42499;0.12657;0.42499;,
 -0.60103;0.12657;-0.00000;,
 -0.42499;0.12657;-0.42499;,
 0.40628;0.06756;-0.40628;,
 0.00000;0.06756;-0.57457;,
 0.57457;0.06756;0.00000;,
 0.40628;0.06756;0.40628;,
 -0.00000;0.06756;0.57457;,
 -0.40628;0.06756;0.40628;,
 -0.57457;0.06756;-0.00000;,
 -0.40628;0.06756;-0.40628;,
 0.37828;0.02812;-0.37828;,
 0.00000;0.02812;-0.53497;,
 0.53497;0.02812;0.00000;,
 0.37828;0.02812;0.37828;,
 -0.00000;0.02812;0.53497;,
 -0.37828;0.02812;0.37828;,
 -0.53497;0.02812;-0.00000;,
 -0.37828;0.02812;-0.37828;,
 0.34525;0.01427;-0.34525;,
 0.00000;0.01427;-0.48826;,
 0.48826;0.01427;0.00000;,
 0.34525;0.01427;0.34525;,
 -0.00000;0.01427;0.48826;,
 -0.34525;0.01427;0.34525;,
 -0.48826;0.01427;-0.00000;,
 -0.34525;0.01427;-0.34525;,
 0.00000;0.01427;0.00000;;
 
 88;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;;
 
 MeshMaterialList {
  1;
  88;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\bottle.png";
   }
  }
 }
 MeshNormals {
  82;
  0.000000;1.000000;0.000000;,
  0.000000;0.057887;-0.998323;,
  0.705921;0.057887;-0.705921;,
  0.998323;0.057887;0.000000;,
  0.705921;0.057887;0.705921;,
  -0.000000;0.057887;0.998323;,
  -0.705921;0.057887;0.705921;,
  -0.998323;0.057886;-0.000000;,
  -0.705921;0.057886;-0.705921;,
  -0.000000;0.370200;-0.928952;,
  0.656868;0.370200;-0.656868;,
  0.928952;0.370200;0.000000;,
  0.656868;0.370200;0.656868;,
  -0.000000;0.370200;0.928952;,
  -0.656868;0.370200;0.656868;,
  -0.928952;0.370201;0.000000;,
  -0.656868;0.370200;-0.656868;,
  -0.000000;0.500435;-0.865774;,
  0.612195;0.500435;-0.612195;,
  0.865774;0.500435;0.000000;,
  0.612195;0.500435;0.612195;,
  -0.000000;0.500435;0.865774;,
  -0.612195;0.500435;0.612195;,
  -0.865774;0.500435;0.000000;,
  -0.612195;0.500435;-0.612195;,
  -0.000000;0.162185;-0.986760;,
  0.697745;0.162185;-0.697745;,
  0.986760;0.162185;0.000000;,
  0.697745;0.162185;0.697745;,
  -0.000000;0.162185;0.986760;,
  -0.697745;0.162185;0.697745;,
  -0.986760;0.162185;0.000000;,
  -0.697745;0.162185;-0.697745;,
  -0.000000;-0.066334;-0.997797;,
  0.705549;-0.066334;-0.705549;,
  0.997797;-0.066335;0.000000;,
  0.705549;-0.066335;0.705549;,
  -0.000000;-0.066334;0.997797;,
  -0.705549;-0.066334;0.705549;,
  -0.997797;-0.066334;0.000000;,
  -0.705549;-0.066334;-0.705549;,
  -0.000000;-0.274326;-0.961637;,
  0.679980;-0.274326;-0.679980;,
  0.961637;-0.274326;0.000000;,
  0.679980;-0.274326;0.679980;,
  -0.000000;-0.274326;0.961637;,
  -0.679980;-0.274326;0.679980;,
  -0.961637;-0.274326;-0.000000;,
  -0.679980;-0.274326;-0.679980;,
  -0.000000;-0.570302;-0.821435;,
  0.580842;-0.570302;-0.580842;,
  0.821435;-0.570302;0.000000;,
  0.580842;-0.570302;0.580842;,
  -0.000000;-0.570302;0.821435;,
  -0.580842;-0.570302;0.580842;,
  -0.821435;-0.570302;0.000000;,
  -0.580842;-0.570302;-0.580842;,
  -0.000000;-0.862080;-0.506773;,
  0.358343;-0.862080;-0.358343;,
  0.506773;-0.862080;0.000000;,
  0.358343;-0.862080;0.358343;,
  -0.000000;-0.862080;0.506773;,
  -0.358343;-0.862080;0.358343;,
  -0.506773;-0.862080;0.000000;,
  -0.358343;-0.862080;-0.358343;,
  -0.000000;-0.989708;-0.143105;,
  0.101190;-0.989708;-0.101190;,
  0.143105;-0.989708;0.000000;,
  0.101190;-0.989708;0.101190;,
  -0.000000;-0.989708;0.143105;,
  -0.101190;-0.989708;0.101190;,
  -0.143105;-0.989708;-0.000000;,
  -0.101190;-0.989708;-0.101190;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.087606;-0.996155;,
  0.704388;0.087606;-0.704388;,
  0.996155;0.087606;0.000000;,
  0.704388;0.087606;0.704388;,
  -0.000000;0.087606;0.996155;,
  -0.704388;0.087606;0.704388;,
  -0.996155;0.087606;-0.000000;,
  -0.704388;0.087606;-0.704388;;
  88;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;74,75,2,1;,
  4;75,76,3,2;,
  4;76,77,4,3;,
  4;77,78,5,4;,
  4;78,79,6,5;,
  4;79,80,7,6;,
  4;80,81,8,7;,
  4;81,74,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  3;65,66,73;,
  3;66,67,73;,
  3;67,68,73;,
  3;68,69,73;,
  3;69,70,73;,
  3;70,71,73;,
  3;71,72,73;,
  3;72,65,73;;
 }
 MeshTextureCoords {
  82;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}