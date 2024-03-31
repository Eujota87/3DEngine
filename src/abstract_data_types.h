#ifndef abstract_data_types
#define abstract_data_types

typedef struct vector2 Vector2;
typedef struct vector3 Vector3;
typedef struct triangle Triangle;
typedef struct matrix4 Matrix4;
typedef struct mesh Mesh;
typedef struct obj3D Obj3D;

Mesh* CreateMesh(int triangleCount);
Obj3D* CreateObj3D(Mesh* mesh);

struct vector2 {
    float x;
    float y;
};

struct vector3 {
    float x;
    float y;
    float z;
};

struct vector4 {
    float x;
    float y;
    float z;
    float w;
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

struct obj3D {
    Vector3 pivot;
    int triangleCount;
    Mesh* meshImported;
    Mesh* meshBufferIn;
    Mesh* meshBufferOut;
    Mesh* meshProjected;
};

#endif
