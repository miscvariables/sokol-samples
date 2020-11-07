//------------------------------------------------------------------------------
//  sokol-shape-test.c
//------------------------------------------------------------------------------
#include "sokol_gfx.h"
#define SOKOL_SHAPE_IMPL
#include "sokol_shape.h"
#include "utest.h"

#define T(b) EXPECT_TRUE(b)
#define TFLT(f0,f1,epsilon) {T(fabs((f0)-(f1))<=(epsilon));}

UTEST(sokol_shape, color4f) {
    T(sshape_color_4f(1.0f, 0.0f, 0.0f, 0.0f) == 0x000000FF);
    T(sshape_color_4f(0.0f, 1.0f, 0.0f, 0.0f) == 0x0000FF00);
    T(sshape_color_4f(0.0f, 0.0f, 1.0f, 0.0f) == 0x00FF0000);
    T(sshape_color_4f(0.0f, 0.0f, 0.0f, 1.0f) == 0xFF000000);
}

UTEST(sokol_shape, color3f) {
    T(sshape_color_3f(1.0f, 0.0f, 0.0f) == 0xFF0000FF);
    T(sshape_color_3f(0.0f, 1.0f, 0.0f) == 0xFF00FF00);
    T(sshape_color_3f(0.0f, 0.0f, 1.0f) == 0xFFFF0000);
}

UTEST(sokol_shape, color4b) {
    T(sshape_color_4b(255, 0, 0, 0) == 0x000000FF);
    T(sshape_color_4b(0, 255, 0, 0) == 0x0000FF00);
    T(sshape_color_4b(0, 0, 255, 0) == 0x00FF0000);
    T(sshape_color_4b(0, 0, 0, 255) == 0xFF000000);
}

UTEST(sokol_shape, color3b) {
    T(sshape_color_3b(255, 0, 0) == 0xFF0000FF);
    T(sshape_color_3b(0, 255, 0) == 0xFF00FF00);
    T(sshape_color_3b(0, 0, 255) == 0xFFFF0000);
}

UTEST(sokol_shape, mat4) {
    float values[16] = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    sshape_mat4_t m = sshape_mat4(values);
    T(m.v[0][0] == 1.0f);
    T(m.v[0][1] == 2.0f);
    T(m.v[0][2] == 3.0f);
    T(m.v[0][3] == 4.0f);
    T(m.v[1][0] == 5.0f);
    T(m.v[1][1] == 6.0f);
    T(m.v[1][2] == 7.0f);
    T(m.v[1][3] == 8.0f);
    T(m.v[2][0] == 9.0f);
    T(m.v[2][1] == 10.0f);
    T(m.v[2][2] == 11.0f);
    T(m.v[2][3] == 12.0f);
    T(m.v[3][0] == 13.0f);
    T(m.v[3][1] == 14.0f);
    T(m.v[3][2] == 15.0f);
    T(m.v[3][3] == 16.0f);
}

UTEST(sokol_shape, mat4_transpose) {
    float values[16] = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    sshape_mat4_t m = sshape_mat4_transpose(values);
    T(m.v[0][0] == 1.0f);
    T(m.v[1][0] == 2.0f);
    T(m.v[2][0] == 3.0f);
    T(m.v[3][0] == 4.0f);
    T(m.v[0][1] == 5.0f);
    T(m.v[1][1] == 6.0f);
    T(m.v[2][1] == 7.0f);
    T(m.v[3][1] == 8.0f);
    T(m.v[0][2] == 9.0f);
    T(m.v[1][2] == 10.0f);
    T(m.v[2][2] == 11.0f);
    T(m.v[3][2] == 12.0f);
    T(m.v[0][3] == 13.0f);
    T(m.v[1][3] == 14.0f);
    T(m.v[2][3] == 15.0f);
    T(m.v[3][3] == 16.0f);
}

UTEST(sokol_shape, plane_buffer_sizes) {
    sshape_buffer_sizes_t res;

    res = sshape_plane_buffer_sizes(1);
    T(4 == res.num_vertices);
    T(6 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);

    res = sshape_plane_buffer_sizes(2);
    T(9 == res.num_vertices);
    T(24 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);
}

UTEST(sokol_shape, box_buffer_sizes) {
    sshape_buffer_sizes_t res;

    res = sshape_box_buffer_sizes(1);
    T(24 == res.num_vertices);
    T(36 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);

    res = sshape_box_buffer_sizes(2);
    T(54 == res.num_vertices);
    T(144 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);
}

UTEST(sokol_shape, sphere_buffer_sizes) {
    sshape_buffer_sizes_t res;

    res = sshape_sphere_buffer_sizes(3, 2);
    T(12 == res.num_vertices);
    T(18 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);

    res = sshape_sphere_buffer_sizes(36, 12);
    T(481 ==  res.num_vertices);
    T(2376 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);
}

UTEST(sokol_shape, cylinder_buffer_sizes) {
    sshape_buffer_sizes_t res;

    res = sshape_cylinder_buffer_sizes(3, 1);
    T(24 == res.num_vertices);
    T(36 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);

    res = sshape_cylinder_buffer_sizes(5, 2);
    T(42 == res.num_vertices);
    T(90 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);
}

UTEST(sokol_shape, torus_buffer_sizes) {
    sshape_buffer_sizes_t res;

    res = sshape_torus_buffer_sizes(3, 3);
    T(16 == res.num_vertices);
    T(54 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);

    res = sshape_torus_buffer_sizes(4, 5);
    T(30 == res.num_vertices);
    T(120 == res.num_indices);
    T(res.num_vertices * sizeof(sshape_vertex_t) == res.vertex_buffer_size);
    T(res.num_indices * sizeof(uint16_t) == res.index_buffer_size);
}

