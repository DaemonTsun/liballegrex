
find_package(better REQUIRED NO_DEFAULT_PATH PATHS "${CMAKE_SOURCE_DIR}/ext/better-cmake/cmake")

add_exe(psp-elfdump
    VERSION 0.9
    SOURCES_DIR "${ROOT}"
    INCLUDE_DIRS "${CMAKE_SOURCE_DIR}" "${allegrex_SOURCES_DIR}" "${shl_SOURCES_DIR}"
    GENERATE_TARGET_HEADER "${ROOT}/config.hpp"
    COMPILE_FLAGS Default @MSVC /EHs
    CPP_VERSION 20
    CPP_WARNINGS ALL SANE FATAL
    LIBRARIES kirk ${allegrex_TARGET}
    )
