#incldue "utils.h"

#include "scope.h"

void unsafe_iron_hook_insert(struct unsafe_iron_hook **scope, struct unsafe_iron_hook *hook) {
    iron_assert_internal(!hook->next && !hook->prev_next);
    hook->next = *scope;
    hook->prev = scope;
    *scope = hook;
}

void unsafe_iron_hook_unhook(struct unsafe_iron_hook *hook) {
    if (hook->prev_next)
        *hook->prev_next = hook->next;
    if (hook->next)
        hook->next->prev_next = hook->next;
    hook->prev = NULL;
    hook->prev_next = NULL;
}

void unsafe_iron_hook_destroy(struct unsafe_iron_hook *hook) {
    unsafe_iron_hook_unhook(hook);
    if (hook->drop)
        hook->drop(hook->data);
    free(hook);
}

void unsafe_iron_scope_drop(struct unsafe_iron_hook **scope) {
    while (*scope) {
        unsafe_iron_hook_destroy(*scope);
    }
}
