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
 80;
 0.08734;-0.36988;-0.29341;,
 0.28061;-0.36988;-0.29341;,
 0.41289;-0.85925;-0.31619;,
 0.08757;-0.46408;-0.31619;,
 0.08717;-0.04244;-0.27624;,
 0.18090;-0.00101;-0.27624;,
 0.30811;-0.36940;0.30372;,
 0.08137;-0.36940;0.30372;,
 0.07951;-0.67315;0.48986;,
 0.41289;-0.67315;0.48986;,
 0.18090;-0.00061;0.07773;,
 0.08363;-0.04523;0.07773;,
 -0.28208;-0.36987;-0.29341;,
 -0.06563;-0.36988;-0.29341;,
 -0.06540;-0.46408;-0.31619;,
 -0.41436;-0.85925;-0.31619;,
 -0.18237;-0.00101;-0.27624;,
 -0.06580;-0.04244;-0.27624;,
 -0.30958;-0.36940;0.30372;,
 -0.07160;-0.36940;0.30372;,
 -0.06934;-0.04523;0.07773;,
 -0.18237;-0.00061;0.07773;,
 -0.41436;-0.67315;0.48986;,
 -0.07346;-0.67315;0.48986;,
 0.08636;-0.00092;-0.19487;,
 0.18090;-0.04554;-0.19487;,
 0.18090;-0.00101;-0.27624;,
 0.08717;-0.04244;-0.27624;,
 0.08636;-0.49555;-0.19487;,
 0.08757;-0.46408;-0.31619;,
 0.41289;-0.85925;-0.31619;,
 0.32111;-0.46411;-0.03680;,
 -0.18237;-0.04554;-0.19487;,
 -0.06662;-0.00092;-0.19487;,
 -0.06580;-0.04244;-0.27624;,
 -0.18237;-0.00101;-0.27624;,
 -0.31748;-0.46411;-0.03680;,
 -0.41436;-0.85925;-0.31619;,
 -0.06540;-0.46408;-0.31619;,
 -0.06662;-0.49555;-0.19487;,
 -0.31748;-0.46411;-0.03680;,
 -0.28662;-0.36980;-0.19487;,
 -0.28208;-0.36987;-0.29341;,
 -0.41436;-0.85925;-0.31619;,
 -0.18237;-0.04554;-0.19487;,
 -0.18237;-0.00101;-0.27624;,
 0.32111;-0.46411;-0.03680;,
 0.41289;-0.85925;-0.31619;,
 0.28061;-0.36988;-0.29341;,
 0.28515;-0.36980;-0.19487;,
 0.18090;-0.00101;-0.27624;,
 0.18090;-0.04554;-0.19487;,
 0.18090;-0.04533;-0.01321;,
 0.08454;-0.00072;-0.01321;,
 0.08363;-0.04523;0.07773;,
 0.18090;-0.00061;0.07773;,
 0.08127;-0.62742;0.31356;,
 0.32111;-0.45982;-0.02864;,
 0.41289;-0.67315;0.48986;,
 0.07951;-0.67315;0.48986;,
 -0.06843;-0.00072;-0.01321;,
 -0.18237;-0.04533;-0.01321;,
 -0.18237;-0.00061;0.07773;,
 -0.06934;-0.04523;0.07773;,
 -0.31748;-0.45982;-0.02864;,
 -0.07170;-0.62742;0.31356;,
 -0.07346;-0.67315;0.48986;,
 -0.41436;-0.67315;0.48986;,
 -0.30384;-0.36950;0.17908;,
 -0.31748;-0.45982;-0.02864;,
 -0.30958;-0.36940;0.30372;,
 -0.18237;-0.04533;-0.01321;,
 0.32111;-0.45982;-0.02864;,
 0.30237;-0.36950;0.17908;,
 0.30811;-0.36940;0.30372;,
 0.18090;-0.04533;-0.01321;,
 0.12844;-0.41421;0.07617;,
 0.12844;-0.41421;-0.13476;,
 -0.10345;-0.41421;-0.13476;,
 -0.10345;-0.41421;0.07617;;
 
 43;
 4;0,1,2,3;,
 4;0,4,5,1;,
 4;6,7,8,9;,
 4;6,10,11,7;,
 4;12,13,14,15;,
 4;12,16,17,13;,
 4;13,0,3,14;,
 4;13,17,4,0;,
 4;18,19,20,21;,
 4;18,22,23,19;,
 4;19,7,11,20;,
 4;19,23,8,7;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;33,24,27,34;,
 4;36,37,38,39;,
 4;39,38,29,28;,
 4;40,41,42,43;,
 4;41,44,45,42;,
 4;46,47,48,49;,
 4;49,48,50,51;,
 4;52,53,54,55;,
 4;52,25,24,53;,
 4;56,57,58,59;,
 4;56,28,31,57;,
 4;60,61,62,63;,
 4;60,33,32,61;,
 4;53,60,63,54;,
 4;53,24,33,60;,
 4;64,65,66,67;,
 4;64,36,39,65;,
 4;65,56,59,66;,
 4;65,39,28,56;,
 4;68,69,67,70;,
 4;68,41,40,69;,
 4;71,68,70,62;,
 4;71,44,41,68;,
 4;72,73,74,58;,
 4;72,46,49,73;,
 4;73,75,55,74;,
 4;73,49,51,75;,
 4;76,77,78,79;;
 
 MeshMaterialList {
  5;
  43;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  75;
  -0.009181;0.046957;-0.998855;,
  0.042032;0.152646;-0.987387;,
  0.007540;0.047401;-0.998848;,
  -0.037953;0.151550;-0.987721;,
  0.053682;0.872985;0.484784;,
  0.000000;0.522498;0.852641;,
  -0.059917;0.871977;0.485866;,
  0.000000;0.522498;0.852641;,
  -0.004590;0.049664;-0.998756;,
  0.021040;0.194061;-0.980764;,
  -0.028527;0.817078;0.575820;,
  -0.000000;0.522498;0.852641;,
  0.003770;0.049885;-0.998748;,
  -0.018997;0.193509;-0.980915;,
  0.025577;0.817586;0.575238;,
  -0.000000;0.522498;0.852641;,
  0.016454;0.099976;-0.994854;,
  -0.015232;0.099638;-0.994907;,
  0.046367;0.522971;0.851088;,
  -0.052901;0.521186;0.851802;,
  0.008240;0.122157;-0.992477;,
  -0.026450;0.534563;0.844715;,
  -0.007628;0.121986;-0.992502;,
  0.023184;0.535402;0.844279;,
  0.529662;0.848208;-0.000612;,
  -0.656520;-0.690615;0.303369;,
  -0.189511;0.981862;0.005770;,
  0.632490;-0.708873;0.312177;,
  0.114314;0.986980;-0.113147;,
  -0.019722;-0.998548;-0.050127;,
  -0.096443;0.988683;-0.114910;,
  0.015693;-0.998748;-0.047500;,
  0.960241;0.278019;-0.025362;,
  -0.963304;0.267646;-0.020286;,
  -0.183736;0.982972;-0.002635;,
  -0.326945;-0.931863;-0.157285;,
  0.525477;0.850760;-0.008986;,
  0.333784;-0.929490;-0.156958;,
  0.110263;0.987405;0.113459;,
  0.164546;-0.964062;-0.208587;,
  -0.093282;0.989328;0.111934;,
  -0.161224;-0.964625;-0.208578;,
  -0.958902;0.277728;-0.058091;,
  0.955521;0.289221;-0.057711;,
  0.000000;1.000000;0.000000;,
  0.016218;0.999681;0.019356;,
  0.008360;0.974479;-0.224322;,
  -0.367889;-0.929408;0.029303;,
  -0.005546;0.973918;-0.226831;,
  -0.010766;0.999841;0.014199;,
  0.352716;-0.935110;0.034074;,
  -0.970342;0.235825;-0.053137;,
  -0.962534;0.271130;0.004179;,
  -0.964457;0.261361;-0.038911;,
  -0.954199;0.298905;0.012618;,
  -0.958728;0.280368;0.047261;,
  0.964441;0.256616;-0.063265;,
  0.963010;0.264324;-0.052383;,
  0.962097;0.272694;-0.002566;,
  0.958728;0.280369;0.047257;,
  0.041044;-0.945680;-0.322498;,
  0.020541;-0.957696;-0.287049;,
  0.588686;-0.807931;0.026375;,
  -0.019923;-0.957684;-0.287133;,
  -0.039811;-0.945674;-0.322671;,
  -0.578119;-0.815557;0.025402;,
  -0.965859;0.252011;-0.060067;,
  -0.954516;0.293463;-0.052705;,
  -0.953956;0.291330;-0.071378;,
  -0.951263;0.303240;-0.056073;,
  -0.953058;0.289094;-0.090026;,
  0.959571;0.275140;-0.059338;,
  0.953061;0.295209;-0.067272;,
  0.952536;0.301158;-0.044484;,
  0.953058;0.289096;-0.090022;;
  43;
  4;20,16,1,9;,
  4;20,8,0,16;,
  4;19,21,11,7;,
  4;19,6,10,21;,
  4;17,22,13,3;,
  4;17,2,12,22;,
  4;22,20,9,13;,
  4;22,12,8,20;,
  4;18,23,14,4;,
  4;18,5,15,23;,
  4;23,21,10,14;,
  4;23,15,11,21;,
  4;28,24,45,46;,
  4;29,47,25,25;,
  4;26,30,48,49;,
  4;30,28,46,48;,
  4;27,27,50,31;,
  4;31,50,47,29;,
  4;51,33,52,53;,
  4;33,54,55,52;,
  4;56,57,58,32;,
  4;32,58,59,59;,
  4;36,38,10,6;,
  4;36,24,28,38;,
  4;39,37,60,61;,
  4;39,29,62,37;,
  4;40,34,4,14;,
  4;40,30,26,34;,
  4;38,40,14,10;,
  4;38,28,30,40;,
  4;35,41,63,64;,
  4;35,65,31,41;,
  4;41,39,61,63;,
  4;41,31,29,39;,
  4;42,66,67,68;,
  4;42,33,51,66;,
  4;69,42,68,70;,
  4;69,54,33,42;,
  4;71,43,72,73;,
  4;71,56,32,43;,
  4;43,74,74,72;,
  4;43,32,24,36;,
  4;44,44,44,44;;
 }
 MeshTextureCoords {
  80;
  0.316130;0.429800;,
  0.000000;0.429800;,
  0.000000;1.000000;,
  0.393250;1.000000;,
  0.258010;0.000000;,
  0.000000;0.000000;,
  1.000000;0.548350;,
  0.658090;0.548350;,
  0.597010;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.732250;0.000000;,
  1.000000;0.429790;,
  0.635730;0.429790;,
  0.578170;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.679110;0.000000;,
  0.000000;0.548340;,
  0.366500;0.548350;,
  0.311150;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.412090;1.000000;,
  0.260250;0.770130;,
  0.000000;0.770130;,
  0.000000;1.000000;,
  0.258010;1.000000;,
  0.394720;0.150510;,
  0.393250;0.000000;,
  0.000000;0.000000;,
  0.000000;0.150510;,
  1.000000;0.770130;,
  0.681350;0.770130;,
  0.679110;1.000000;,
  1.000000;1.000000;,
  1.000000;0.150510;,
  1.000000;0.000000;,
  0.578170;0.000000;,
  0.579640;0.150510;,
  0.150510;1.000000;,
  0.165020;0.449360;,
  0.000000;0.429790;,
  0.000000;1.000000;,
  0.229870;0.000000;,
  0.000000;0.000000;,
  0.849490;1.000000;,
  1.000000;1.000000;,
  1.000000;0.429800;,
  0.834980;0.449360;,
  1.000000;0.000000;,
  0.770130;0.000000;,
  0.000000;0.256900;,
  0.265250;0.256900;,
  0.267750;0.000000;,
  0.000000;0.000000;,
  0.400860;0.781280;,
  0.000000;0.831180;,
  0.000000;1.000000;,
  0.402990;1.000000;,
  0.686350;0.256900;,
  1.000000;0.256900;,
  1.000000;0.000000;,
  0.688850;0.000000;,
  1.000000;0.831180;,
  0.585780;0.781280;,
  0.587910;1.000000;,
  1.000000;1.000000;,
  0.791260;0.523600;,
  0.831180;1.000000;,
  1.000000;0.548340;,
  0.743100;0.000000;,
  0.168820;1.000000;,
  0.208740;0.523600;,
  0.000000;0.548350;,
  0.256900;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;;
 }
 MeshVertexColors {
  80;
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
  79;1.000000;1.000000;1.000000;1.000000;;
 }
}