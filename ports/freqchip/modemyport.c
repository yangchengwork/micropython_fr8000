#include "py/runtime.h"

static mp_obj_t myport_info(void) {
    mp_printf(&mp_plat_print, "info about my port\n");
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(myport_info_obj, myport_info);

static const mp_rom_map_elem_t myport_module_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_myport) },
};

static MP_DEFINE_CONST_DICT(myport_module_globals, myport_module_globals_table);

const mp_obj_module_t myport_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_t)&myport_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_myport, myport_user_cmodule);

