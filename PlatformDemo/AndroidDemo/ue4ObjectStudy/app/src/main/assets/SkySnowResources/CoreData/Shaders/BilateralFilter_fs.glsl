#version 300 es
uniform sampler2D diffuseMap;
in vec2 vTexcoords;
uniform float radius;
uniform float sigmaSpace;
uniform float sigmaColor;
uniform vec2 imageSize;
out vec4 fragColor;

vec3 BilateralFilter(sampler2D cmap,vec2 uv,float r,float ss,float sc,vec2 imageS)
{
    int d = int(r);
    float ss2 = 2.0 * ss * ss;
    float sc2 = 2.0 * sc * sc;
    float i = uv.x;
    float j = uv.y;
    float weightSum = 0.0;
    vec3 filterValue = vec3(0.0);
    vec3 centerCol = texture(cmap,uv).rgb;

    for(int k = -d; k <= d;k++)
    {
       for(int l = -d; l <= d; l ++)
       {
            vec2 curUV = uv + vec2(k,l) * vec2(1.0/imageS.x,1.0/imageS.y);
            vec3 curCol = texture(cmap,curUV).rgb;
            float value_Square = dot(curCol - centerCol,curCol - centerCol);
            float distance_Square = distance(curUV,uv) * float(d);
            float weight = exp(-1.0 * (distance_Square/ss2 + value_Square/sc2));
            weightSum += weight;
            filterValue += (weight * curCol);
       }
    }
    filterValue = filterValue/weightSum;
    return filterValue;
}
void main()
{
    vec2 newTexcoord = vec2(vTexcoords.x,1.0 - vTexcoords.y);
    vec3 bColor = BilateralFilter(diffuseMap,newTexcoord,radius,sigmaSpace,sigmaColor,imageSize);
    fragColor = vec4(bColor,texture(diffuseMap,newTexcoord));
}