#version 300 es
uniform sampler2D sDiffuseMap;
uniform vec4 cColor;
in vec2 vTexCoord;
in vec3 vNormal;
out vec4 fragColor;
void main()
{
    vec3 color = cColor.rgb;
    fragColor = texture(sDiffuseMap,vTexCoord);
}//