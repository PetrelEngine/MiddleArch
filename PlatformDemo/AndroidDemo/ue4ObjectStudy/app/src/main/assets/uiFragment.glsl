uniform sampler2D gposition;
uniform sampler2D gnormal;
uniform sampler2D gcolor;
uniform sampler2D gdepth;
uniform vec2 u_Viewport;
in vec2 vTexCoord;

void main()
{
    vec2 tex_coord = gl_FragCoord.xy/u_Viewport;
    vec4 position = texture2D(gposition, tex_coord);
    vec4 normal = texture2D(gnormal, tex_coord);
    vec4 color = texture2D(gcolor, vTexCoord);
    vec4 depth = texture2D(gdepth, tex_coord);
    gl_FragColor = vec4(vTexCoord.xy,0.0,1.0);
                          }