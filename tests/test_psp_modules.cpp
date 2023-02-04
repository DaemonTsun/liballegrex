
#include <t1/t1.hpp>
#include <string.h>

#include "allegrex/psp_modules.hpp"

#define assert_str_equal(A, B) assert_equal(strcmp(A, B), 0)

define_test(get_psp_module_by_name)
{
    assert_equal(get_psp_module_by_name(nullptr), nullptr);
    assert_equal(get_psp_module_by_name(""), nullptr);
    assert_equal(get_psp_module_by_name("a"), nullptr);

    const psp_module *mod;

    mod = get_psp_module_by_name("Kernel_Library");

    assert_not_equal(mod, nullptr);
    assert_str_equal(mod->name, "Kernel_Library");
}

define_test(get_psp_function_by_nid)
{
    assert_equal(get_psp_function_by_nid(nullptr, 0), nullptr);
    assert_equal(get_psp_function_by_nid("", 0), nullptr);
    assert_equal(get_psp_function_by_nid("a", 0), nullptr);
    assert_equal(get_psp_function_by_nid("Kernel_Library", 0), nullptr);

    const psp_function *fun;
    fun = get_psp_function_by_nid("Kernel_Library", 0x092968f4);

    assert_not_equal(fun, nullptr);
    assert_str_equal(fun->name, "sceKernelCpuSuspendIntr");
    assert_equal(fun->nid, 0x092968f4);
}

define_test(get_psp_function_by_name)
{
    assert_equal(get_psp_function_by_name(nullptr, nullptr), nullptr);
    assert_equal(get_psp_function_by_name("", ""), nullptr);
    assert_equal(get_psp_function_by_name("a", "a"), nullptr);
    assert_equal(get_psp_function_by_name("Kernel_Library", "whatever"), nullptr);

    const psp_function *fun;
    fun = get_psp_function_by_name("Kernel_Library", "sceKernelTryLockLwMutex");
    assert_not_equal(fun, nullptr);
    assert_str_equal(fun->name, "sceKernelTryLockLwMutex");
    
    fun = get_psp_function_by_name("Kernel_Library", "Kernel_Library_A089ECA4");
    assert_not_equal(fun, nullptr);
    assert_str_equal(fun->name, "sceKernelMemset");
}

define_test(get_psp_function_nid_name)
{
    char nidname[256];

    const psp_function *fun;
    fun = get_psp_function_by_name("Kernel_Library", "sceKernelMemset");

    get_psp_function_nid_name(fun, nidname);
    assert_str_equal(nidname, "Kernel_Library_A089ECA4");
}

define_default_test_main();
