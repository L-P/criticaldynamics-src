#include "native_engine.h"
#include "native_math.h"

/* {{{ Methods to export, all are optional:

// Called when the entity is fired (ie. ::Use() is called).
// Returns an arbitrary status code, 0 = success, other values are logged.
int32_t on_fire(
    const entity_t* activator,
    const entity_t* caller,
    use_type_t use_type,
    float value
);

// Called every time the entity thinks.
// Returns delay before next think, < 0 to error out and quit thinking.
// dt is the time delta since last think.
float on_think(float time);

// Called when the entity is activated, either right after spawn or after loading.
// Requires SF_GAME_WASM_ACTIVATE to be set.
void on_activate(void);

// Called when used as the master of another entity. The activator is the
// entity that has the game_wasm as master.
// Any non-zero value will pass the master check.
int32_t on_master_check(const entity_t* activator, const entity_t* caller);

// Called when the entity is saving itself, you get a 1024 bytes buffer where
// to write data you wish to be persisted.
int32_t on_save(char* buf, size_t bufSize);

// Called when the entity is restoring itself, you get a 1024 bytes buffer of
// data you previously wrote in on_save.
int32_t on_restore(const char* buf, size_t bufSize);

}}} */
