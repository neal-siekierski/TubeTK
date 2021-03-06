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

include_regular_expression( "^.*$" )

set( TEMP ${TubeTK_BINARY_DIR}/Temporary )

set( PROJ_EXE
 ${TubeTK_LAUNCHER} $<TARGET_FILE:${MODULE_NAME}> )

set( CompareTextFiles_EXE
 ${TubeTK_LAUNCHER} $<TARGET_FILE:CompareTextFiles> )

# Test1
ExternalData_Add_Test( TubeTKData
  NAME ${MODULE_NAME}-Test1
  COMMAND ${PROJ_EXE}
    DATA{${TubeTK_DATA_ROOT}/Branch-truth-new.tre}
    -w ${TEMP}/${MODULE_NAME}Test1.tre )

# Test1-Compare
ExternalData_Add_Test( TubeTKData
  NAME ${MODULE_NAME}-Test1-Compare
  COMMAND ${CompareTextFiles_EXE}
    -t ${TEMP}/${MODULE_NAME}Test1.tre
    -b DATA{${TubeTK_DATA_ROOT}/Branch-truth-new.tre}
    -d 0.01 )
set_tests_properties( ${MODULE_NAME}-Test1-Compare PROPERTIES DEPENDS
  ${MODULE_NAME}-Test1 )

# Test2
ExternalData_Add_Test( TubeTKData
  NAME ${MODULE_NAME}-Test2
  COMMAND ${PROJ_EXE}
    DATA{${TubeTK_DATA_ROOT}/Branch-truth-new.tre}
    -l R DATA{${TubeTK_DATA_ROOT}/Branch.n010.mha}
    -l M DATA{${TubeTK_DATA_ROOT}/Branch.n020.mha}
    -l B DATA{${TubeTK_DATA_ROOT}/Branch.n010.mha}
    -l r DATA{${TubeTK_DATA_ROOT}/Branch.n020.mha}
    -u
    -t 100
    -a
    -o
    -T
    -n
    -w ${TEMP}/${MODULE_NAME}Test2.tre )

# Test2-Compare
ExternalData_Add_Test( TubeTKData
  NAME ${MODULE_NAME}-Test2-Compare
  COMMAND ${CompareTextFiles_EXE}
    -t ${TEMP}/${MODULE_NAME}Test2.tre
    -B 2 DATA{${TubeTK_DATA_ROOT}/${MODULE_NAME}Test2.tre} DATA{${TubeTK_DATA_ROOT}/${MODULE_NAME}Test2-2.tre}
    -d 0.01 )
set_tests_properties( ${MODULE_NAME}-Test2-Compare PROPERTIES DEPENDS
  ${MODULE_NAME}-Test2 )
