attribute vec3 aPostionVertex; //Vector3 to store position
//runs once for every vertex


void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * aPositionVertex;
}