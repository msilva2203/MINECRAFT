#shader vertex
#version 330 core
        
layout(location = 0) in uint VertexData;

out vec3 v_Position;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

uint ExtractByte(uint Value, uint Offset)
{
    return uint((Value >> Offset) & 0xffu);
}

uint UseValueIfFlag(uint Value, uint FlagValue, uint Flags, uint Offset)
{
    uint flag = uint((Flags >> Offset) & 0x1u);
    return uint((Value * (uint(1) - flag)) + (FlagValue * flag));
}
        
void main()
{
    uint xzPos  = ExtractByte(VertexData, uint(8));
    uint xyUv   = ExtractByte(VertexData, uint(16));
    uint flags  = ExtractByte(VertexData, uint(24));

    uint xPos   = UseValueIfFlag((xzPos & 0xf0u) >> uint(4), uint(16), flags, uint(2));
    uint yPos   = UseValueIfFlag(ExtractByte(VertexData, uint(0)), uint(256), flags, uint(1));
    uint zPos   = UseValueIfFlag((xzPos & 0x0fu) >> uint(0), uint(16), flags, uint(0));

    uint xUv = (xyUv & 0xf0u) >> uint(4);
    uint yUv = (xyUv & 0x0fu) >> uint(0);

    v_Position = vec3(xPos, yPos, zPos);
    v_TexCoord = vec2(xUv, yUv);

    gl_Position = u_MVP * vec4(v_Position, uint(1));
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
