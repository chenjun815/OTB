#
# Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
#
# This file is part of Orfeo Toolbox
#
#     https://www.orfeo-toolbox.org/
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

INCLUDE_ONCE_MACRO(HDF5)

SETUP_SUPERBUILD(HDF5)

# declare dependencies
ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(HDF5 ZLIB)

set(HDF5_SB_CONFIG)
ADD_SUPERBUILD_CMAKE_VAR(HDF5 ZLIB_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(HDF5 ZLIB_LIBRARY)

ExternalProject_Add(HDF5
  PREFIX HDF5
  URL "https://www.hdfgroup.org/package/gzip/?wpdmdl=4301"
  URL_MD5 43a2f9466702fb1db31df98ae6677f15
  DOWNLOAD_NAME "hdf5-1.10.1.tar.gz"
  SOURCE_DIR ${HDF5_SB_SRC}
  BINARY_DIR ${HDF5_SB_BUILD_DIR}
  INSTALL_DIR ${SB_INSTALL_PREFIX}
  DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
  DEPENDS ${HDF5_DEPENDENCIES}
  CMAKE_CACHE_ARGS
  ${SB_CMAKE_CACHE_ARGS}
    -DBUILD_TESTING:BOOL=OFF
    -DHDF5_BUILD_CPP_LIB:BOOL=OFF
    -DHDF5_BUILD_EXAMPLES:BOOL=ON
    -DHDF5_BUILD_FORTRAN:BOOL=OFF
    -DHDF5_BUILD_HL_LIB:BOOL=ON                                                                                                                                        
    -DHDF5_BUILD_JAVA:BOOL=OFF                                                                                                                                       
    -DHDF5_BUILD_TOOLS:BOOL=OFF
    -DHDF5_ENABLE_SZIP_SUPPORT:BOOL=OFF
    -DHDF5_ENABLE_Z_LIB_SUPPORT:BOOL=ON
    ${HDF5_SB_CONFIG}
  CMAKE_COMMAND ${SB_CMAKE_COMMAND}
  LOG_DOWNLOAD 1
  LOG_CONFIGURE 1
  LOG_BUILD 1
  LOG_INSTALL 1
  )

set(_SB_HDF5_INCLUDE_DIR ${SB_INSTALL_PREFIX}/include)
if(WIN32)
  set(_SB_HDF5_LIBRARY ${SB_INSTALL_PREFIX}/lib/hdf5_i.lib)
  set(_SB_HDF5_HL_LIBRARY ${SB_INSTALL_PREFIX}/lib/hdf5_hl_i.lib)
elseif(UNIX)
  set(_SB_HDF5_LIBRARY ${SB_INSTALL_PREFIX}/lib/libhdf5${CMAKE_SHARED_LIBRARY_SUFFIX})
  set(_SB_HDF5_HL_LIBRARY ${SB_INSTALL_PREFIX}/lib/libhdf5_hl${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()
