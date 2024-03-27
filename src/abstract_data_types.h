#ifndef abstract_data_types
#define abstract_data_types

typedef struct vector2 Vector2;
typedef struct vector3 Vector3;
typedef struct triangle Triangle;
typedef struct matrix4 Matrix4;
typedef struct mesh Mesh;

Vector3 MulMatrix4Vector3(Vector3 vecIn, Matrix4 mat4);

Mesh* CreateMesh(int triangleCount);

Triangle ProjectTriangle(Triangle triangleIn, Matrix4 matrix);
void ProjectMesh(Mesh* meshIn, Mesh* meshOut, Matrix4 matrix);

void InputMoveMesh(Mesh* mesh, float delta_time);
void TranslateMesh(Mesh* meshIn, Mesh* meshOut, float distance );
void RotateMesh(Mesh* meshIn, Mesh* meshOut, float degrees, char axis);

void PrintMeshData(Mesh* mesh);

struct vector2 {
    float x;
    float y;
};

struct vector3 {
    float x;
    float y;
    float z;
};

struct triangle {
    Vector3 vertex[3];
    Vector3 normal;
};

struct matrix4 {
    float m[4][4];
};

struct mesh {
    int triangleCount;
    Triangle* triangle;
    Vector3 pivot;
};


#endif
