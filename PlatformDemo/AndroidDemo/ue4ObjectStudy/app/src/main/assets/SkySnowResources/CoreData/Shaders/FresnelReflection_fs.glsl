#version 300 es
uniform sampler2D diffuseMap;
uniform vec3 lightPosition;
uniform vec3 eyePosition;
in vec2 vTexcoords;
in vec3 vWNormals;
in vec3 vWPositions;
out vec4 fragColor;
float fresnelSchlick(float cosTheta,float F0)
{
    return F0 + (1.0 - F0)*pow(1.0 - cosTheta,5.0);
}
vec3 BlinnPhone(vec3 normal,vec3 position,vec3 lightPos,vec3 eyePos)
{
    //散射光计算
    vec3 lightColor = vec3(0.6,0.6,0.6);
    vec3 lightDir = normalize(lightPos - position);
    float diffuseRadius = max(dot(lightDir,normal),0.0);
    vec3 diffuse = diffuseRadius * lightColor;
    //镜面反射光计算
    vec3 eyeDir = normalize(eyePos - position);
    vec3 reflectDir = reflect(-lightDir,normal);
    vec3 halfDir = normalize(lightDir + eyeDir);
    float specularRadius = pow(max(dot(normal,halfDir),0.0),64.0);
    vec3 specular = specularRadius * lightColor;
    //gama矫正后的不需要进行除以非平方的操作
    float max_distance = 1.5;
    float dis = length(lightPos - position);
    if(max_distance < dis)
        dis = max_distance;
    float attenuation = 1.0/(dis*dis);
    diffuse *= attenuation;
    specular *= attenuation;
    //菲涅尔反射计算,只是对镜面反射光进行影响
    float F0 = 0.4;
    float fresnel = fresnelSchlick(max(dot(halfDir,eyeDir),0.0),F0);
    specular *= fresnel;

    //计算菲涅尔折射对于高光的影响


    return diffuse + specular;
}
void main()
{
    vec3 color = texture(diffuseMap,vTexcoords).rgb;
    color = pow(color,vec3(2.2));
    vec3 light = vec3(0.0,0.0,0.0);
    light = BlinnPhone(vWNormals,vWPositions,lightPosition,eyePosition);
    color *= light;
    color = pow(color,vec3(1.0/2.2));
    fragColor = vec4(color,texture(diffuseMap,vTexcoords).a);
}//