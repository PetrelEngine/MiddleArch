#version 300 es
uniform sampler2D diffuseMap;
uniform sampler2D dispMap;
uniform sampler2D normalMap;
uniform float heightScale;
in vec2 vTexCoords;
in vec3 vPosition;
in vec3 vEyePos;
in vec3 vLightPos;
out vec4 fragColor;
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    float height =  texture(dispMap, texCoords).r;
    return texCoords - viewDir.xy/viewDir.z * (height * heightScale);
}
void main()
{
    vec3 eyeDir = normalize(vEyePos - vPosition);
    vec2 texCoords = vTexCoords;
    texCoords = ParallaxMapping(vTexCoords,eyeDir);
    if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
        discard;
    vec3 normal = texture(normalMap, texCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    // get diffuse color
    vec3 color = texture(diffuseMap, texCoords).rgb;
    // ambient
    vec3 ambient = 0.1 * color;
    // diffuse
    vec3 lightDir = normalize(vLightPos - vPosition);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + eyeDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = color * spec;
    fragColor = vec4(ambient + diffuse + specular,1.0);
}//