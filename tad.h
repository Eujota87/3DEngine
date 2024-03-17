#ifndef TAD
#define TAD

typedef struct vector2 Vector2;
typedef struct vector3 Vector3;
typedef struct matrix4 Matrix4;
typedef struct triangle Triangle;

Vector3 MulMatrix4Vector3(Vector3 vecIn, Matrix4 mat4);

struct matrix4 {
    float m[4][4];
};

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
    Vector3 point[3];
};


#endif
