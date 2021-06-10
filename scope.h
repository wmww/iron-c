#ifndef _IRON_SCOPE_H
#define _IRON_SCOPE_H

// A scope is a doubly-linked list of hooks, started by an unsafe_iron_hook**

// A hook is a single item hooked into a scope
// It consists of a data pointer, a drop function which recieves that data pointer and the linked list pointers
// The drop function is expected to manage destroying the data if needed
struct unsafe_iron_hook {
    void *data;
    void (*drop)(void*);
    struct unsafe_iron_hook *next;
    struct unsafe_iron_hook **prev_next;
};

// Insert a single hook into a scope
// hook should be currently unhooked
void unsafe_iron_hook_insert(struct unsafe_iron_hook **scope, struct unsafe_iron_hook *hook);

// Unhook the hook from its current scope, does not drop the data
void unsafe_iron_hook_unhook(struct unsafe_iron_hook *hook);

// Unhook, drop the data and free the hook, data is only freed if the drop function does that
void unsafe_iron_hook_destroy(struct unsafe_iron_hook *hook);

// Drop the scope, destroying all hooks in it
void unsafe_iron_scope_drop(struct unsafe_iron_hook **scope);

#endif // _IRON_SCOPE_H
