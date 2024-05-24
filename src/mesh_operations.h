#ifndef MESH_OPERATIONS
#define MESH_OPERATIONS

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix);
void ProjectObjMesh(Obj3D* obj, Matrix4 matrix);

void BackfaceCullingMesh2D(Obj3D* obj);
void ResizeMesh2D(Obj3D* obj);
void ZSortMesh2D(Obj3D* obj);
void PrintMeshData(Mesh* mesh);

#endif