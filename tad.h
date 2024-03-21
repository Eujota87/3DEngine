#ifndef TAD
#define TAD

typedef struct vector2 Vector2;
typedef struct vector3 Vector3;
typedef struct triangle Triangle;
typedef struct matrix4 Matrix4;
typedef struct mesh Mesh;

Vector3 MulMatrix4Vector3(Vector3 vecIn, Matrix4 mat4);


Mesh* CreateMesh(int triangleCount);

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

void PrintMeshData(Mesh* mesh);

#endif
