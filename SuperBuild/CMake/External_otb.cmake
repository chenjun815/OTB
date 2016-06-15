INCLUDE_ONCE_MACRO(OTB)

SETUP_SUPERBUILD(PROJECT OTB)

if(SUPERBUILD_IN_OTB_TREE)
  set(OTB_SB_SRC ${CMAKE_SOURCE_DIR}/..)
endif()

set(OTB_ADDITIONAL_CACHE)

#set(BUILD_EXAMPLES ON)

if(ENABLE_OTB_LARGE_INPUTS)
  set(OTB_SB_LARGEINPUT_CONFIG
    -DOTB_DATA_USE_LARGEINPUT:BOOL=ON
    -DOTB_DATA_LARGEINPUT_ROOT:PATH=${OTB_DATA_LARGEINPUT_ROOT}
    )
else()
  set(OTB_SB_LARGEINPUT_CONFIG
    -DOTB_DATA_USE_LARGEINPUT:BOOL=OFF
    )
endif()


ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB GDAL OSSIM ITK TINYXML BOOST)

##get_property(OTB_DEPENDENCIES GLOBAL PROPERTY GLOBAL_OTB_DEPENDENCIES)

if(OTB_USE_CURL)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB CURL)
endif()
if(OTB_USE_LIBKML)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB LIBKML)
endif()

if(OTB_USE_OPENCV)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB OPENCV)
endif()

if(OTB_USE_LIBSVM)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB LIBSVM)
endif()

if(OTB_USE_MUPARSER)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB MUPARSER)
endif()

if(OTB_USE_MUPARSERX)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB MUPARSERX)
endif()

if(OTB_WRAP_PYTHON OR OTB_WRAP_JAVA)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB SWIG)
endif()

if(OTB_USE_QT4)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB QT4)
endif()

if(OTB_USE_GLEW)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB GLEW)
endif()

if(OTB_USE_GLFW)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB GLFW)
endif()

if(OTB_USE_GLUT)
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OTB GLUT)
endif()

ADD_SUPERBUILD_CMAKE_VAR(OTB GDAL_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OTB GDAL_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(OTB OSSIM_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OTB OSSIM_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(OTB ITK_DIR)

ADD_SUPERBUILD_CMAKE_VAR(OTB MUPARSER_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OTB MUPARSER_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(OTB MUPARSERX_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OTB MUPARSERX_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(OTB TINYXML_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OTB TINYXML_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(OTB Boost_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OTB Boost_LIBRARY_DIR)

ADD_SUPERBUILD_CMAKE_VAR(OTB LIBKML_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OTB LIBKML_BASE_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(OTB LIBKML_CONVENIENCE_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(OTB LIBKML_DOM_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(OTB LIBKML_ENGINE_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(OTB LIBKML_REGIONATOR_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(OTB LIBKML_XSD_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(OTB LIBKML_MINIZIP_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(OTB OpenCV_DIR)

ADD_SUPERBUILD_CMAKE_VAR(OTB LIBSVM_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OTB LIBSVM_LIBRARY)

if(OTB_USE_CURL)
  ADD_SUPERBUILD_CMAKE_VAR(OTB CURL_INCLUDE_DIR)
  ADD_SUPERBUILD_CMAKE_VAR(OTB CURL_LIBRARY)
endif()

if(MSVC)
  ADD_SUPERBUILD_CMAKE_VAR(OTB JPEG_LIBRARY)
endif()

ADD_SUPERBUILD_CMAKE_VAR(OTB SWIG_EXECUTABLE)

if(OTB_USE_GLEW)
  ADD_SUPERBUILD_CMAKE_VAR(OTB GLEW_INCLUDE_DIR)
  ADD_SUPERBUILD_CMAKE_VAR(OTB GLEW_LIBRARY)
endif()
if(OTB_USE_GLFW)
  ADD_SUPERBUILD_CMAKE_VAR(OTB GLFW_INCLUDE_DIR)
  ADD_SUPERBUILD_CMAKE_VAR(OTB GLFW_LIBRARY)
endif()
if(OTB_USE_GLUT)
  ADD_SUPERBUILD_CMAKE_VAR(OTB GLUT_INCLUDE_DIR)
  ADD_SUPERBUILD_CMAKE_VAR(OTB GLUT_LIBRARY)
endif()

if(SUPERBUILD_IN_OTB_TREE)
  set(OTB_HG_SOURCES DOWNLOAD_COMMAND "")
else()
  set(OTB_HG_SOURCES
    HG_REPOSITORY "http://hg.orfeo-toolbox.org/OTB"
    HG_TAG tip
    )
endif()

# forward compilation flags
set(OTB_SB_C_FLAGS "${SB_PRIOR_INCLUDE_FLAGS} ${CMAKE_C_FLAGS}")
set(OTB_SB_CXX_FLAGS "${SB_PRIOR_INCLUDE_FLAGS} ${CMAKE_CXX_FLAGS}")
set(OTB_SB_COMPILATION_FLAGS
  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  -DCMAKE_C_FLAGS:STRING=${OTB_SB_C_FLAGS}
  -DCMAKE_CXX_FLAGS:STRING=${OTB_SB_CXX_FLAGS}
  -DCMAKE_EXE_LINKER_FLAGS:STRING=${CMAKE_EXE_LINKER_FLAGS}
  -DCMAKE_MODULE_LINKER_FLAGS:STRING=${CMAKE_MODULE_LINKER_FLAGS}
  -DCMAKE_SHARED_LINKER_FLAGS:STRING=${CMAKE_SHARED_LINKER_FLAGS}
  -DCMAKE_STATIC_LINKER_FLAGS:STRING=${CMAKE_STATIC_LINKER_FLAGS}
  )

ExternalProject_Add(OTB
  DEPENDS ${OTB_DEPENDENCIES}
  PREFIX OTB
  ${OTB_HG_SOURCES}
  SOURCE_DIR ${OTB_SB_SRC}
  BINARY_DIR ${OTB_SB_BUILD_DIR}
  INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
  DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
  CMAKE_CACHE_ARGS
  ${SB_CMAKE_CACHE_ARGS}
  ${OTB_SB_COMPILATION_FLAGS}
  -DBUILD_TESTING:BOOL=${BUILD_TESTING}
  -DBUILD_EXAMPLES:BOOL=${BUILD_EXAMPLES}
  -DOTB_DATA_ROOT:STRING=${OTB_DATA_ROOT}
  -DOTB_USE_6S:BOOL=${OTB_USE_6S}
  -DOTB_USE_CURL:BOOL=${OTB_USE_CURL}
  -DOTB_USE_LIBKML:BOOL=${OTB_USE_LIBKML}
  -DOTB_USE_LIBSVM:BOOL=${OTB_USE_LIBSVM}
  -DOTB_USE_MAPNIK:BOOL=${OTB_USE_MAPNIK}
  -DOTB_USE_MUPARSER:BOOL=${OTB_USE_MUPARSER}
  -DOTB_USE_MUPARSERX:BOOL=${OTB_USE_MUPARSERX}
  -DOTB_USE_OPENCV:BOOL=${OTB_USE_OPENCV}
  -DOTB_USE_OPENJPEG:BOOL=OFF
  -DOTB_USE_QT4:BOOL=${OTB_USE_QT4}
  -DOTB_USE_SIFTFAST:BOOL=${OTB_USE_SIFTFAST}
  -DOTB_USE_OPENGL:BOOL=${OTB_USE_OPENGL}
  -DOTB_USE_GLEW:BOOL=${OTB_USE_GLEW}
  -DOTB_USE_GLFW:BOOL=${OTB_USE_GLFW}
  -DOTB_USE_GLUT:BOOL=${OTB_USE_GLUT}
  ${OTB_SB_CONFIG}
  ${OTB_SB_LARGEINPUT_CONFIG}
  -DOTB_WRAP_PYTHON:BOOL=${OTB_WRAP_PYTHON}
  -DOTB_WRAP_JAVA:BOOL=${OTB_WRAP_JAVA}
  ${OTB_ADDITIONAL_CACHE}
  CMAKE_COMMAND ${SB_CMAKE_COMMAND}
  )

ExternalProject_Add_Step(OTB install_copyright
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${OTB_SB_SRC}/Copyright ${CMAKE_INSTALL_PREFIX}/share/copyright
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Copyright ${CMAKE_INSTALL_PREFIX}/share/copyright
  DEPENDEES install)

# detect OTB version number
if (SUPERBUILD_OTB_VERSION)
  set(_SB_OTB_DIR ${SB_INSTALL_PREFIX}/lib/cmake/OTB-${SUPERBUILD_OTB_VERSION_MAJOR}.${SUPERBUILD_OTB_VERSION_MINOR})
else()
  set(_SB_OTB_DIR ${SB_INSTALL_PREFIX})
endif()
