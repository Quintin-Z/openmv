#include "mp.h"
#include "imlib.h"
#include "py_helper.h"

int get_int_kw(mp_map_t *kw_args, mp_obj_t kw, int default_val)
{
    mp_map_elem_t *kw_arg = mp_map_lookup(kw_args, kw, MP_MAP_LOOKUP);

    if (kw_arg != NULL) {
        default_val = mp_obj_get_int(kw_arg->value);
    }
    return default_val;
}

float get_float_kw(mp_map_t *kw_args, mp_obj_t kw, float default_val)
{
    mp_map_elem_t *kw_arg = mp_map_lookup(kw_args, kw, MP_MAP_LOOKUP);

    if (kw_arg != NULL) {
        default_val = mp_obj_get_float(kw_arg->value);
    }
    return default_val;
}

int get_color_kw(mp_map_t *kw_args, int default_color)
{
    mp_map_elem_t *kw_color = mp_map_lookup(kw_args,
            MP_OBJ_NEW_QSTR(MP_QSTR_color), MP_MAP_LOOKUP);

    if (kw_color != NULL) {
        if (mp_obj_is_integer(kw_color->value)) {
            default_color = mp_obj_get_int(kw_color->value);
        } else {
            mp_obj_t *arg_color;
            mp_obj_get_array_fixed_n(kw_color->value, 3, &arg_color);
            default_color = IM_RGB565(IM_R825(mp_obj_get_int(arg_color[0])),
                                      IM_G826(mp_obj_get_int(arg_color[1])),
                                      IM_B825(mp_obj_get_int(arg_color[2])));
        }
    }
    return default_color;
}

void get_rectangle_kw(mp_map_t *kw_args, image_t *img, rectangle_t *r)
{
    mp_map_elem_t *kw_rectangle = mp_map_lookup(kw_args,
            MP_OBJ_NEW_QSTR(MP_QSTR_roi), MP_MAP_LOOKUP);

    if (kw_rectangle == NULL) {
        r->x = 0;
        r->y = 0;
        r->w = img->w;
        r->h = img->h;
    } else {
        mp_obj_t *arg_rectangle;
        mp_obj_get_array_fixed_n(kw_rectangle->value, 4, &arg_rectangle);
        r->x = mp_obj_get_int(arg_rectangle[0]);
        r->y = mp_obj_get_int(arg_rectangle[1]);
        r->w = mp_obj_get_int(arg_rectangle[2]);
        r->h = mp_obj_get_int(arg_rectangle[3]);
    }
}