#ifndef abstract_data_types
#define abstract_data_types

typedef struct vector2 Vector2;
typedef struct vector3 Vector3;
typedef struct vector4 Vector4;
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
    float shadeColor;
    int sharedTrianglesCount;
    int sharedTrianglesIndex[30]; //make it a dynamic vector later
};

struct matrix4 {
    float m[4][4];
};

struct triangle {
    Vector4 vertex[3];
    Vector4 center;
    Vector4 normal;
    float shadeColor;
};

struct mesh {
    int triangleCount;
    Triangle* triangle;
    Vector4 pivot;
};

struct obj3D {
    Vector4 pivot;
    int triangleCount;
    Mesh* meshImported;
    Mesh* meshBufferIn;
    Mesh* meshBufferOut;
    Mesh* meshProjected;
    
    
    Mesh* mesh2DWindowSpace;
    Mesh* mesh2DWindowSpaceZSorted;
};

#endif
