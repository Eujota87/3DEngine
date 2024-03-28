#ifndef GEOMETRY_OPERTAIONS
#define GEOMETRY_OPERTAIONS

Vector3 MulMatrix4Vector3(Vector3 vecIn, Matrix4 mat4);

void TranslateTrianglesFromPivot(Mesh* meshIn, Mesh* meshOut);
void MeshToWorldCenter(Mesh* meshIn, Mesh* meshOut);

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix);
void ProjectMesh(Mesh* meshIn, Mesh* meshOut, Matrix4 matrix);

void InputMoveMesh(Mesh* mesh, float delta_time);
void InputMoveMeshPivot(Mesh* meshIn, float delta_time);
void TranslateMesh(Mesh* meshIn, Mesh* meshOut, float distance );
void RotateMesh(Mesh* meshIn, Mesh* meshOut, float degrees, char axis);

void PrintMeshData(Mesh* mesh);

#endif