#version 300 es
out vec4 fragColor;
in vec2 vTexCoords;
uniform sampler2D depthMap;
uniform float near_plane;
uniform float far_plane;
float linearizeDepth(float depth)
{
    //转换到屏幕空间
    float z = depth * 2.0 - 1.0;
    return (2.0 * near_plane * far_plane)/(far_plane + near_plane - z * (far_plane - near_plane));
}
void main()
{
    float depthValue = texture(depthMap,vTexCoords).r;
    fragColor = vec4(vec3(depthValue),1.0);
//    fragColor = texture(depthMap,vTexCoords);
}//