struct vec2 {
    float x;
    float y;
};

typedef enum {
    SHAPE_SQUARE,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE
} shape_type_t;

typedef struct {
    shape_type_t type;
    struct vec2 origin;
} shape_t;

struct square {
    shape_t shape;
    float width;
    float height;
};

struct circle {
    shape_t shape;
    float radius;
};

struct triangle {
    shape_t shape;
    struct vec2 db;
    struct vec2 dc;
};

float test(shape_t *s) {
    struct square *square;
    struct circle *circle;
    struct triangle *triangle;

    switch (s->type) {
    case SHAPE_SQUARE:
        square = (struct square *)s;
        return square->shape.origin.x + square->width;
    case SHAPE_CIRCLE:
        circle = (struct circle *)s;
        return circle->shape.origin.x + circle->radius;
    case SHAPE_TRIANGLE:
        triangle = (struct triangle *)s;
        return triangle->shape.origin.x + triangle->db.x;
    }
    return 0.0f;
}
