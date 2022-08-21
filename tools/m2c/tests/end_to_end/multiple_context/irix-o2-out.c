f32 test(shape_t *s) {
    s32 temp_v0;

    temp_v0 = s->type;
    switch (temp_v0) {                              /* irregular */
    case SHAPE_SQUARE:
        return s->origin.x + s->unkC;
    case SHAPE_CIRCLE:
        return s->origin.x + s->unkC;
    case SHAPE_TRIANGLE:
        return s->origin.x + s->unkC;
    default:
        return 0.0f;
    }
}
