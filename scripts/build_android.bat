cmake^
    -DCMAKE_TOOLCHAIN_FILE="%NDK%/build/cmake/android.toolchain.cmake"^
    -DCMAKE_MAKE_PROGRAM="%NDK_CMAKE%/bin/ninja"^
    -DANDROID_ABI=%2^
    -DCMAKE_ANDROID_ARCH_ABI=%2^
    -DCMAKE_SYSTEM_NAME=Android^
    -DCMAKE_SYSTEM_VERSION=23^
    -DANDROID_PLATFORM=android-23^
    -DANDROID_STL=c++_static^
    -DCMAKE_BUILD_TYPE=%3^
    -S%1^
    -B%1/android_build^
    -GNinja

cd %1/android_build
call "%NDK_CMAKE%/bin/ninja"