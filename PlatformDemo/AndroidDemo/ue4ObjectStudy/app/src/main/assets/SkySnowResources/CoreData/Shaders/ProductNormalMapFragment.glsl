#version 300 es
uniform sampler2D colorMap;
uniform vec2 imageSize;
in vec2 vTexCoord;
out vec4 fragColor;
float clamp1(float pX, float pMax)
{
    if (pX > pMax)
    return pMax;
    else if (pX < 0.0)
    return 0.0;
    else
    return pX;
}
float intensity(vec4 col)
{
    return 0.3 * col.x + 0.59 * col.y + 0.11 * col.z;
}
void main()
{
    float ws = 1.0/imageSize.x;
    float hs = 1.0/imageSize.y;
    float c[10];
    vec2 sTexCoord = vec2(vTexCoord.x,1.0 - vTexCoord.y);
    vec4 col = texture(colorMap,sTexCoord);
    c[3] = intensity(texture(colorMap, vec2(clamp1(sTexCoord.x+ws,imageSize.x), clamp1(sTexCoord.y+hs,imageSize.y))));
    c[6] = intensity(texture(colorMap, vec2(clamp1(sTexCoord.x+ws,imageSize.x), clamp1(sTexCoord.y,imageSize.y))));
    c[9] = intensity(texture(colorMap, vec2(clamp1(sTexCoord.x+ws,imageSize.x), clamp1(sTexCoord.y-hs,imageSize.y))));
    c[2] = intensity(texture(colorMap, vec2(clamp1(sTexCoord.x,imageSize.x), clamp1(sTexCoord.y+hs,imageSize.y))));
    c[8] = intensity(texture(colorMap, vec2(clamp1(sTexCoord.x,imageSize.x), clamp1(sTexCoord.y-hs,imageSize.y))));
    c[1] = intensity(texture(colorMap, vec2(clamp1(sTexCoord.x-ws,imageSize.x), clamp1(sTexCoord.y+hs,imageSize.y))));
    c[4] = intensity(texture(colorMap, vec2(clamp1(sTexCoord.x-ws,imageSize.x), clamp1(sTexCoord.y,imageSize.y))));
    c[7] = intensity(texture(colorMap, vec2(clamp1(sTexCoord.x-ws,imageSize.x), clamp1(sTexCoord.y-hs,imageSize.y))));
    float dx = -(c[3]+2.0*c[6]+c[9])+(c[1]+2.0*c[4]+c[7]);
    float dy = c[7]+2.0*c[8]+c[9]-(c[1]+2.0*c[2]+c[3]);
    float tempvalue = sqrt(dx * dx + dy * dy + 1.0);
    float dz = 1.0/tempvalue;
    float zx = (-dx/tempvalue + 1.0)/2.0;
    float zy = (-dy/tempvalue + 1.0)/2.0;

    fragColor = vec4(zx,zy,dz,col.a);
}