#version 300 es
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];
uniform vec3 eyePos;
in vec2 vTexcoords;
in vec3 vNormals;
in vec3 vPositions;
out vec4 fragColor;
float PI = 3.14159265359;
vec3 getNormalFromMap()
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
    return normalize(TBN * tangentNormal);
}
float DistributionGGX(vec3 N, vec3 H,float roughness)
{
    float a = roughness * roughness;
    float a2 = a* a;
    float NdotH = max(dot(N,H),0.0);
    float Ndoth2 = NdotH * NdotH;
    float nom = a2;
    float denom = (Ndoth2 * (a2 - 1.0) + 1.0);
    denom = PI * denom *denom;
    return nom/denom;
}
float GeometrySchlickGGX(float NdotV,float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) /8.0;
    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    return nom/denom;
}
float GeometrySmity(vec3 N ,vec3 V, vec3 L,float roughness)
{
    float NdotV = max(dot(N,V),0.0);
    float NdotL = max(dot(N,L),0.0);
    float ggx2 = GeometrySchlickGGX(NdotV,roughness);
    float ggx1 = GeometrySchlickGGX(NdotL,roughness);
    return ggx1 * ggx2;
}
vec3 fresnelSchlick(float cosTheta,vec3 F0)
{
    return F0 + (1.0 - F0)*pow(1.0 - cosTheta,5.0);
}

void main()
{
    fragColor = texture(albedoMap,vTexcoords);
}