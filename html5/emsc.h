#pragma once
/* common emscripten platform helper functions */
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

const char* _emsc_canvas_name = 0;
bool _emsc_is_webgl2 = false;
double _emsc_width = 0;
double _emsc_height = 0;

enum {
    EMSC_NONE = 0,
    EMSC_TRY_WEBGL2 = (1<<0),
    EMSC_ANTIALIAS = (1<<1)
};

/* track CSS element size changes and update the WebGL canvas size */
EM_BOOL _emsc_size_changed(int event_type, const EmscriptenUiEvent* ui_event, void* user_data) {
    emscripten_get_element_css_size(_emsc_canvas_name, &_emsc_width, &_emsc_height);
    emscripten_set_canvas_element_size(_emsc_canvas_name, _emsc_width, _emsc_height);
    return true;
}

/* initialize WebGL context and canvas */
void emsc_init(const char* canvas_name, int flags) {
    _emsc_canvas_name = canvas_name;
    _emsc_is_webgl2 = false;
    emscripten_get_element_css_size(canvas_name, &_emsc_width, &_emsc_height);
    emscripten_set_canvas_element_size(canvas_name, _emsc_width, _emsc_height);
    emscripten_set_resize_callback(0, 0, false, _emsc_size_changed);
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.antialias = flags & EMSC_ANTIALIAS;
    if (flags & EMSC_TRY_WEBGL2) {
        attrs.majorVersion = 2;
    }
    ctx = emscripten_webgl_create_context(0, &attrs);
    if ((flags & EMSC_TRY_WEBGL2) && ctx) {
        _emsc_is_webgl2 = true;
    }
    if (!ctx) {
        /* WebGL2 not supported, fall back to WebGL */
        attrs.majorVersion = 1;
        ctx = emscripten_webgl_create_context(0, &attrs);
    }
    emscripten_webgl_make_context_current(ctx);
}

int emsc_width() {
    return (int) _emsc_width;
}

int emsc_height() {
    return (int) _emsc_height;
}

bool emsc_webgl_fallback() {
    return !_emsc_is_webgl2;
}