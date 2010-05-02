varying vec3 normal;
varying vec3 position;

void main(void)
{
   gl_Position = ftransform();
   normal = (gl_NormalMatrix*gl_Normal).xyz;      //eye-space normal vector
   position = (gl_ModelViewMatrix*gl_Vertex).xyz; //eye-space position
}
