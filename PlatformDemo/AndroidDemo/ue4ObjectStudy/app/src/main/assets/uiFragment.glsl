#version 300 es
uniform sampler2D gposition;
uniform sampler2D gnormal;
uniform sampler2D gcolor;
uniform sampler2D gdepth;
uniform vec2 u_Viewport;
uniform vec3 lightPosition;
uniform vec3 eyePosition;
in vec2 vTexCoord;
out vec4 fragColor;
void main()
{
    vec2 tex_coord = gl_FragCoord.xy/u_Viewport;
    vec4 position = texture(gposition,tex_coord);
    vec4 normal = texture(gnormal,tex_coord);
    vec4 color = texture(gcolor,tex_coord);
    vec4 depth = texture(gdepth,tex_coord);
    vec3 lightAmbient = vec3(0.5,0.5,0.5);
    vec3 lightDiffuse = vec3(1.0,1.0,1.0);
    vec3 lightSpecular = vec3(1.0,1.0,1.0);
    vec3 materialAmbient = vec3(1.0,1.0,1.0);
    vec3 materialDiffuse = vec3(1.0,1.0,1.0);
    vec3 materialSpecular = vec3(1.0,1.0,1.0);
    vec3 eyevec = normalize(eyePosition - position.xyz);
    vec3 lightvec = normalize(lightPosition - position.xyz);
    vec3 normalvec = normalize(normal.xyz);
    vec3 refl = reflect(vec3(0.0,0.0,0.0) - lightvec,normalvec);
    vec3 ambient = lightAmbient * materialAmbient;
    vec3 diffuse = max(0.0,dot(lightvec,normalvec)) * lightDiffuse * materialDiffuse;
    vec3 specular = pow(max(0.0,dot(eyevec,refl)),32.0) * lightSpecular * materialSpecular;
    vec4 finalLight = vec4(ambient + diffuse + specular,1.0);
    fragColor = finalLight * color;
}