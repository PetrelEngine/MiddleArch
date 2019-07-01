#version 300 es
uniform sampler2D colorMap;
uniform vec3 lightPos[4];
uniform vec3 lightColor[4];
uniform vec3 eyePos;
uniform bool gamma;
in vec2 vTexcoords;
in vec3 vPositions;
in vec3 vNormals;
out vec4 fragColor;
vec3 BlinnPhone(vec3 normal,vec3 wordPos,vec3 lPos,vec3 lColor)
{
    //diffuse
    vec3 lightDir = normalize(lPos - wordPos);
    float diffRadius = max(dot(lightDir,normal),0.0);
    vec3 diffuse = diffRadius * lColor;
    //specular
    vec3 eyeDir = normalize(eyePos - wordPos);
    vec3 reflectDir = reflect(-lightDir,normal);
    vec3 halfDir = normalize(lightDir + eyeDir);
    float specularRadius = 0.0;
    specularRadius = pow (max(dot(normal,halfDir),0.0),64.0);
    //specularRadius = pow (saturate(dot(normal,halfDir),0.0),64.0);
    vec3 specular = specularRadius * lColor;
    //simple attenuation
    float max_distance = 1.5;
    float dis = length(lPos - wordPos);
    float attenuation = 1.0/(gamma?(dis*dis):dis);
    diffuse *= attenuation;
    specular *= attenuation;
    return diffuse + specular;
}
void main()
{
    vec3 color = texture(colorMap,vTexcoords).rgb;
    if(gamma)
        color = pow(color,vec3(2.2));
    vec3 lighting = vec3(0.0,0.0,0.0);
    for(int i = 0; i < 4; i ++)
        lighting += BlinnPhone(vNormals,vPositions,lightPos[i],lightColor[i]);
    color *= lighting;
    if(gamma)
        color = pow(color,vec3(1.0/2.2));
    fragColor = vec4(color,1.0);
}