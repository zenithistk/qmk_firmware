# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

VIA_ENABLE = yes

# DYNAMIC_TAPPING_TERM_ENABLE = yes
# KEY_OVERRIDE_ENABLE = yes

# POINTING_DEVICE_ENABLE = yes	# Enable Pimoroni Trackball on master (+2304)
# POINTING_DEVICE_DRIVER = pimoroni_trackball

PIMORONI_TRACKBALL_ENABLE = yes
ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    SRC += pimoroni_trackball.c
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
    POINTING_DEVICE_ENABLE := yes
endif