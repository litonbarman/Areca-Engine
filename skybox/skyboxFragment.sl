/*
------------------------------------------------
 Arreca Engine
------------------------------------------------
 Author : Liton Barman
  
 This software is License under GNU General Public License
 version 3 ( GPLv3 )
 
 Redistribution and use of this software in source and binary forms, 
 with or without modification, are permitted provided that 
 the following conditions are met:
 
 . The source code must be made public whenever a distribution of
   the software is made.
 . Modifications of the software must be realised under the same license
 . Changes made to the Source Code must be documented


*/

#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main(){
  FragColor = texture(skybox, TexCoords);
}
