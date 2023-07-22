#shader vertex
#version 330 core
        
layout(location = 0) in vec4 VertexData;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;
        
void main()
{
    v_TexCoord = texCoord;
    gl_Position = u_MVP * VertexData;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_ColorMultiplier;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = u_ColorMultiplier * texColor;
};
