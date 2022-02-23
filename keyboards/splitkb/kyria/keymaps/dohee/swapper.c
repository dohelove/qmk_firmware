#include "swapper.h"


static bool swapper_active = false;

bool update_swapper(
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
            if (!swapper_active) {
                swapper_active = true;
                register_mods(MOD_BIT(cmdish));
            }
            register_code16(tabish);
        } else {
            unregister_code16(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (keycode == trigger_prev) {
        if (record->event.pressed) {
            if (!swapper_active) {
                swapper_active = true;
                register_mods(MOD_BIT(cmdish));
            }
            register_mods(MOD_BIT(KC_LSFT));
            register_code16(tabish);
        } else {
            unregister_mods(MOD_BIT(KC_LSFT));
            unregister_code16(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (swapper_active && keycode == trigger_actv) {
        if (record->event.pressed) {
            unregister_mods(MOD_BIT(cmdish));
            swapper_active = false;
        }
    } else if (swapper_active) {
        unregister_mods(MOD_BIT(cmdish));
        swapper_active = false;
        return true;
    }
    else {
        return true;
    }
    return false;
}
