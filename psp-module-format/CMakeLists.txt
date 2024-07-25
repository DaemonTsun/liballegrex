
find_package(better REQUIRED NO_DEFAULT_PATH PATHS "${CMAKE_SOURCE_DIR}/ext/better-cmake/cmake")

add_exe(psp-module-format
    VERSION 1.0.0
    SOURCES_DIR "${ROOT}"
    INCLUDE_DIRS "${CMAKE_SOURCE_DIR}" "${allegrex_SOURCES_DIR}" "${shl_SOURCES_DIR}"
    GENERATE_TARGET_HEADER "${ROOT}/config.hpp"
    CPP_VERSION 20
    CPP_WARNINGS ALL SANE FATAL
    LIBRARIES kirk ${allegrex_TARGET}
    )
