// Use typedefs in this file to mix things up

typedef enum {
    SHAPE_SQUARE,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE
} shape_type_t;

typedef struct {
    shape_type_t type;
    struct vec2 origin;
} shape_t;

float test(shape_t *s);
