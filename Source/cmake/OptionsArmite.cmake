ADD_DEFINITIONS(-DWTF_PLATFORM_ARMITE=1)
ADD_DEFINITIONS(-DENABLE_CONTEXT_MENUS=0)

#SET(FONTCONFIG_INCLUDE_DIR ${THIRDPARTY_DIR}/fontconfig-2.9.0)
#SET(SQLITE_INCLUDE_DIR ${THIRDPARTY_DIR}/sqlite-autoconf-3071300)
#SET(LIBXML2_INCLUDE_DIR ${THIRDPARTY_DIR}/libxml2-2.9.0)
#SET(JPEG_INCLUDE_DIR ${THIRDPARTY_DIR}/jpeg-8d)
#SET(PNG_INCLUDE_DIRS ${THIRDPARTY_DIR}/libpng-1.5.9)
FIND_PACKAGE(Fontconfig 2.8.0 REQUIRED)
FIND_PACKAGE(Sqlite REQUIRED)
FIND_PACKAGE(LibXml2 2.6 REQUIRED)
FIND_PACKAGE(JPEG REQUIRED)
FIND_PACKAGE(PNG REQUIRED)

SET(WTF_USE_PTHREADS 1)
ADD_DEFINITIONS(-DWTF_USE_PTHREADS=1)

FIND_PACKAGE(ICU REQUIRED)
#SET(ICU_INCLUDE_DIRS ${THIRDPARTY_DIR}/icu)
SET(WTF_USE_ICU_UNICODE 1)
ADD_DEFINITIONS(-DWTF_USE_ICU_UNICODE=1)

FIND_PACKAGE(Cairo 1.10 REQUIRED)
#SET(CAIRO_INCLUDE_DIRS ${THIRDPARTY_DIR}/cairo-1.12.8)
SET(WTF_USE_CAIRO 1)
ADD_DEFINITIONS(-DWTF_USE_CAIRO=1)

FIND_PACKAGE(CURL REQUIRED)
#SET(CURL_INCLUDE_DIRS ${THIRDPARTY_DIR}/curl-7.27.0)
SET(WTF_USE_CURL 1)
ADD_DEFINITIONS(-DWTF_USE_CURL=1)

FIND_PACKAGE(Freetype REQUIRED)
#SET(FREETYPE_INCLUDE_DIRS ${THIRDPARTY_DIR}/freetype-2.4.9)
SET(WTF_USE_FREETYPE 1)
ADD_DEFINITIONS(-DWTF_USE_FREETYPE=1)

#ADD_DEFINITIONS(-DANDROID)
#SET(WTF_CPU_ARM 1)
#INCLUDE_DIRECTORIES(SYSTEM "${THIRDPARTY_DIR}/gnu-libstdc++/include")
#INCLUDE_DIRECTORIES(SYSTEM "${THIRDPARTY_DIR}/gnu-libstdc++/libs/armeabi-v7a/include")
#SET(CMAKE_CXX_FLAGS "-march=armv7-a -mfloat-abi=softfp -mthumb -MMD -MP -fpic -funwind-tables -fstack-protector -fomit-frame-pointer -fno-rtti -fno-exceptions -Wa,--noexecstack ${CMAKE_CXX_FLAGS}")
#SET(CMAKE_SHARED_LINKER_FLAGS "-fno-stack-protector -Wl,--fix-cortex-a8 -Wl,--no-undefined -Wl,-z,noexecstack -Wl,--gc-sections -Wl,-shared,-Bsymbolic")

SET(WTF_LIBRARY_NAME wtf)
SET(JavaScriptCore_LIBRARY_NAME javascriptcore)
SET(WebCore_LIBRARY_NAME webcore)
SET(WebKit_LIBRARY_NAME mywebkit)

WEBKIT_OPTION_BEGIN()
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DETAILS ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_JIT ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NETSCAPE_PLUGIN_API ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SQL_DATABASE ON)
WEBKIT_OPTION_END()



