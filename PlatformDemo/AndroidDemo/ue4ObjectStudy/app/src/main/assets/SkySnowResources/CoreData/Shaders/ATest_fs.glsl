#version 300 es
uniform sampler2D sDiffuseMap;
uniform vec4 cColor;
in vec2 vTexCoord;
in vec3 vNormal;
out vec4 fragColor;
void main()
{
    vec2 nTexCoor = vec2(vNormal.y - vTexCoord.x,vNormal.y - vTexCoord.y);
    vec4 color = texture(sDiffuseMap,nTexCoor);
    fragColor = color;
}//