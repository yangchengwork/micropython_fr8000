
#include "py/builtin.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "py/binary.h"

STATIC const mp_rom_map_elem_t gump_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_gump)},
    {MP_ROM_QSTR(MP_QSTR_STR), MP_ROM_QSTR(MP_QSTR_My_string)},
};

STATIC MP_DEFINE_CONST_DICT(gump_globals, gump_globals_table);

const mp_obj_module_t gump_user_cmodule = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t*)&gump_globals,
};

MP_REGISTER_MODULE(MP_QSTR_gump, gump_user_cmodule);

