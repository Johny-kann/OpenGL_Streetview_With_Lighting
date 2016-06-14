uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;
uniform vec4 lightPos;
uniform vec4 lightDiffuse;
uniform vec4 lightAmbient;
uniform vec4 lightModelAmbient;
uniform vec4 materialDiffuse;
uniform vec4 materialAmbient;

attribute vec4 posAttr;
attribute vec4 normalAttr;
attribute vec2 texCoordAttr;

varying vec2 texCoord;
varying vec4 frontColor;




void main()
{
    vec3 normal, lightDir;
    vec4 diffuse, ambient, globalAmbient;
    float NdotL;
    vec4 nn = vec4(normalAttr);
    normal = vec3(mvMatrix * nn);
//    vec4(normalAttr, 0.0));
    lightDir = normalize(vec3(lightPos));
    NdotL = max(dot(normal, lightDir), 0.0);
    diffuse = materialDiffuse * lightDiffuse;
    ambient = materialAmbient * lightAmbient;
    globalAmbient = materialAmbient * lightModelAmbient;
    frontColor =  NdotL * diffuse + globalAmbient + ambient;

    gl_Position = mvpMatrix * posAttr;
    texCoord = texCoordAttr;
}
