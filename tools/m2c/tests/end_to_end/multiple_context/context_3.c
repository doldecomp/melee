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

