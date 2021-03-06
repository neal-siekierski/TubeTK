##############################################################################
#
# Library:   TubeTK
#
# Copyright 2010 Kitware Inc. 28 Corporate Drive,
# Clifton Park, NY, 12065, USA.
#
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
##############################################################################

# See https://github.com/KitwareMedical/TubeTK/wiki/Dependencies

# Sanity checks
set(expected_nonempty_vars github_protocol git_protocol)
foreach(varname ${expected_nonempty_vars})
  if("${${varname}}" STREQUAL "")
    message(FATAL_ERROR "Variable '${varname}' is empty")
  endif()
endforeach()

# Cppcheck
set( Cppcheck_URL ${github_protocol}://github.com/KitwareMedical/cppcheck.git )
set( Cppcheck_HASH_OR_TAG bb0c8cbe7667615bca37ea2a02e2652642a5112e )

# JsonCpp
# http://midas3.kitware.com/midas/download/bitstream/366544/JsonCpp_r276.tar.gz
set( JsonCpp_URL ${git_protocol}://github.com/KitwareMedical/jsoncpp.git )
set( JsonCpp_HASH_OR_TAG 110d054227e9eb63faad48a1fb6a828ad0670e61 )

# KWStyle
set( KWStyle_URL ${git_protocol}://github.com/Kitware/KWStyle.git )
set( KWStyle_HASH_OR_TAG e03980ff514d5248a9f95ea355dcd9eff78c62d3 )

# LIBSVM
set( LIBSVM_URL ${git_protocol}://github.com/KitwareMedical/libsvm.git )
set( LIBSVM_HASH_OR_TAG 9bc3630f0f15fed7a5119c228c4d260574b4b6b2 )

# RandomForest
set( RandomForest_URL
  ${git_protocol}://github.com/KitwareMedical/random-forest.git )
set( RandomForest_HASH_OR_TAG 6e1d0e271fea967487655555b8f26915aa1004d4 )

###########################################################
# ITK Modules
###########################################################

# TubeTKITK: Source already available in TubeTK project
set( TubeTKITK_URL ${TubeTK_SOURCE_DIR}/ITKModules/TubeTKITK )
set( TubeTKITK_HASH_OR_TAG "")

# MinimalPathExtraction
set( MinimalPathExtraction_URL
  ${git_protocol}://github.com/InsightSoftwareConsortium/ITKMinimalPathExtraction.git )
set( MinimalPathExtraction_HASH_OR_TAG 5a2017ef5d5c25db518ecae49408598f906dd307 )

set( TubeTK_ITK_MODULES
  TubeTKITK
  MinimalPathExtraction
  )

# Insight Segmentation and Registration Toolkit
set( ITK_URL ${github_protocol}://github.com/InsightSoftwareConsortium/ITK.git )
set( ITK_HASH_OR_TAG v4.12.0 )

# Slicer Execution Model
set( SlicerExecutionModel_URL
  ${github_protocol}://github.com/Slicer/SlicerExecutionModel.git )
set( SlicerExecutionModel_HASH_OR_TAG b6f14387f71a15c054d73b8bbb8f32974c975489 )

# Visualization Toolkit (3D Slicer fork)
set( VTK_URL ${github_protocol}://github.com/Slicer/VTK.git )
set( VTK_HASH_OR_TAG a024cefc2acf25350734e6f04d2562f9a6a3b124 )
