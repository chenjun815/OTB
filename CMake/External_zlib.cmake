message(STATUS "Setup Zlib ...")

set(proj ZLIB)

set(DEFAULT_USE_SYSTEM_ZLIB  OFF)

option(USE_SYSTEM_ZLIB "  Use a system build of Zlib." ${DEFAULT_USE_SYSTEM_ZLIB})
mark_as_advanced(USE_SYSTEM_ZLIB)

if(USE_SYSTEM_ZLIB)
  message(STATUS "  Using Zlib system version")
else()
  
  set(ZLIB_SB_BUILD_DIR ${CMAKE_BINARY_DIR}/${proj}/build)
  set(ZLIB_SB_SRC ${CMAKE_BINARY_DIR}/${proj}/src/${proj})
  
  if(NOT DEFINED git_protocol)
    set(git_protocol "git")
  endif()
  
  ExternalProject_Add(${proj}
    PREFIX ${proj}
    GIT_REPOSITORY "${git_protocol}://github.com/commontk/zlib.git"
    GIT_TAG "66a753054b356da85e1838a081aa94287226823e"
    BINARY_DIR ${ZLIB_SB_BUILD_DIR}
    INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
    CMAKE_CACHE_ARGS
      ## CXX should not be needed, but it a cmake default test
      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
      -DCMAKE_BUILD_TYPE:STRING=Release
      -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
      -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
      #-DCMAKE_C_FLAGS:STRING=${ep_common_c_flags}
      -DZLIB_MANGLE_PREFIX:STRING=otb_zlib_
      -DBUILD_SHARED_LIBS:BOOL=ON
    )


endif()
