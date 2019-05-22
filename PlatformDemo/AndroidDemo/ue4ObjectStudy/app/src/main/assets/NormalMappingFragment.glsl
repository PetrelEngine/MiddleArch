#version 300 es
#ifdef GL_OES_standard_derivatives
#extension GL_OES_standard_derivatives : enable
#endif
precision highp float;
uniform sampler2D normalMap;
uniform sampler2D colorMap;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 eyePosition;
uniform float normalScale;
in vec2 vTexcoords;
in vec3 vPositions;
in vec3 vNormals;
in vec3 mPosition;
out vec4 fragColor;
void main()
{
    vec3 tangentNormal = texture(normalMap,vTexcoords).xyz * 2.0 - 1.0;
    vec3 Q1 = dFdx(vPositions);
    vec3 Q2 = dFdy(vPositions);
    vec2 st1 = dFdx(vTexcoords);
    vec2 st2 = dFdy(vTexcoords);
    vec3 N = normalize(vNormals);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = -normalize(cross(N,T));
    mat3 TBN = mat3(T,B,N);
    vec3 wnormal = normalize(TBN * tangentNormal * vec3(normalScale,normalScale,1.0));
    vec3 lightDir = normalize(lightPosition - vPositions);
    float diffRadius = max(dot(lightDir,wnormal),0.0);
    vec3 diffuse = diffRadius * lightColor;
    vec3 eyeDir = normalize(eyePosition - vPositions);
    vec3 reflectDir = reflect(-lightDir,wnormal);
    vec3 halfDir = normalize(lightDir + eyeDir);
    float specularRadius = 0.0;
    specularRadius = pow (max(dot(wnormal,halfDir),0.0),64.0);
    vec3 specular = specularRadius * lightColor;
    float dis = length(lightPosition - vPositions);
    float attenuation = 1.0/(dis*dis);
    diffuse  *= attenuation;
    specular *= attenuation;
    vec3 color = texture(colorMap,vTexcoords).xyz;
    color = pow(color,vec3(2.2));
    color = color * (diffuse + specular);
    color = pow(color,vec3(1.0/2.2));
    fragColor = vec4(color,1.0);
}//