APP_PLATFORM := android-14
NDK_TOOLCHAIN_VERSION := 4.8

## compile for all available platforms, use this for release
## with all binaries is the apk only around 4 MB larger
##APP_ABI := all
# best arm compatibility possible
APP_ABI := armeabi
##APP_STL := gnustl_shared
APP_STL := gnustl_static