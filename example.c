#include "functions.h"

#include <stdio.h>

struct unsafe_iron_hook {
    void * data;
    void (*drop)(void*);
    struct unsafe_iron_hook *next;
    struct unsafe_iron_hook **prev_next;
};

// Item is expected to be something like '(foo) bar' and this macro returns foo
// Use _IRON_STARTS_WITH_PEREN to check if item is in correct form
#define _IRON_GET_TYPE_PART(...) _IRON_GET_THING_IN_PEREN_A __VA_ARGS__ )
#define _IRON_GET_THING_IN_PEREN_A(...) __VA_ARGS__ EXPAND_FALSE(

// Item is expected to be something like '(foo) bar' and this macro returns bar
#define _IRON_GET_THING_AFTER_PEREN(...) EXPAND_FALSE item

// Checks if item starts with parentheses (such as '(foo) bar')
#define _IRON_STARTS_WITH_PEREN(...) EXPAND_CAT(_IRON, _IRON_STARTS_WITH_PEREN_A __VA_ARGS__) )
#define _IRON_STARTS_WITH_PEREN_A(...) _STARTS_WITH_PEREN_B TRUE EXPAND_FALSE(
#define _IRON_IRON_STARTS_WITH_PEREN_A FALSE EXPAND_FALSE(
#define _IRON_STARTS_WITH_PEREN_B

// If the given item has an object type, insert it into the scope, else do nothing
#define _IRON_PUT_OBJECT_IN_SCOPE_FUNCTOR(item, _index) IF(_IRON_STARTS_WITH_PEREN(item))(unsafe_iron_hook_insert(&scope, CAT(unsafe_, _IRON_GET_THING_AFTER_PEREN(item)).scope);)

// Create a wrapper function to set up the scope, and call the wrapped function
// End with the header of the wrapped function
#define IRON_fn(return_type, fn_name, ...) \
    _IRON_FN_HEADER(return_type, fn_name, WRAPPED, __VA_ARGS__); /* Function prototype of the wrapped function */ \
    _IRON_FN_HEADER(return_type, fn_name, WRAPPER, __VA_ARGS__); /* Function prototype of the wrapper function */ \
        IF(HAS_PEREN(return_type))(__attribute__((warn_unused_result))); /* Warn if not using a returned object */ \
            /* Consuming objects is needed to prevent memory leaks */ \
    _IRON_FN_HEADER(return_type, fn_name, WRAPPER, __VA_ARGS__); /* The header of the wrapper function */ \
    { \
        struct unsafe_iron_hook *scope = NULL; \
        MAP(_IRON_PUT_OBJECT_IN_SCOPE_FUNCTOR, __VA_ARGS__) \
        IF(NOT(_IRON_STARTS_WITH_PEREN(return_type))) \
            (_GET_RETURN_TYPE(type) ret =) \
        unsafe_##fn_name(MAP(_GET_PARAM_NAMES_FUNCTOR, __VA_ARGS__) &scope); \
        IF(_DEBUG)(debug_msg("dropping scope");) \
        _Scope_list_drop(scope.next); \
        IF(_DEBUG)( \
            debug_msg("retuning"); \
            _stack_frame_count--; \
            _current_func = calling_func; \
        ) \
        return IF(NE(void, _GET_RETURN_TYPE(type)))(ret) ; \
    } \
    _FUNCTION_HEADER(type, name, TRUE, __VA_ARGS__) \

#define obj(...) typeof(__VA_ARGS__)

IRON_fn (int, add_numbers, (GdkWindow *) a, int b, (obj Window) win)
{
    var (a, create String("Test literal"));
    var (String) (sub, (inv a).substr(1, 3));
    int codepoint = (inv sh sub).at(0);
    return (mv a);
    set (a, get_window());
    (inv a).get_val();
    if ((get (inv sh a, sub).func()).prop == 3) {

    }
    get_val()
    local (Widget) (b, (inv a).get_root())
    return a + b;
}

int main()
{
    printf("Hello, World!\n");
    printf("4 + 7 = %d", add_numbers(4, 7));
    return 0;
}

