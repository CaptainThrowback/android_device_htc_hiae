## Specify phone tech before including full_phone
$(call inherit-product, vendor/omni/config/cdma.mk)

# Inherit device configuration
$(call inherit-product, device/htc/hiae/full_hiae.mk)
# Release name
PRODUCT_RELEASE_NAME := hiae

# Inherit some common DU stuff.
$(call inherit-product, vendor/omni/config/common.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := hiae
PRODUCT_NAME := omni_hiae
PRODUCT_BRAND := htc
PRODUCT_MANUFACTURER := htc
