#include "swapper.h"

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger_next,
    uint16_t trigger_prev,
    uint16_t trigger_actv,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger_next) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (keycode == trigger_prev) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(KC_LSFT);
            register_code(tabish);
        } else {
            unregister_code(tabish);
            unregister_code(KC_LSFT);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (keycode == trigger_actv) {
        tap_code(KC_LALT);
        unregister_code(cmdish);
        *active = false;
    } else if (*active) {
        unregister_code(cmdish);
        *active = false;
    }
}
