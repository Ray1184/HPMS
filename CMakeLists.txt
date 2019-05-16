cmake_minimum_required(VERSION 3.7)
project(HPMS)

set(CMAKE_CXX_STANDARD 14)

set(RT_SOURCE_FILES
        thirdparty/GLAD/src/glad.c
        code/common/Utils.h
        code/common/FileSystem.h
        code/core/Material.h
        code/core/Mesh.cpp
        code/core/Mesh.h
        code/core/Actor.h
        code/core/StdModelItem.cpp
        code/core/StdModelItem.h
        code/core/AdvModelItem.cpp
        code/core/AdvModelItem.h
        code/core/Animation.cpp
        code/core/Animation.h
        code/core/Renderer.h
        code/core/Texture.h
        code/core/ResourceCache.h
        code/common/FileSystem.cpp
        code/core/Transformation.h
        code/core/Camera.h
        code/core/Window.h
        code/core/gl/GLWindow.h
        code/core/Scene.h
        code/core/Shader.h
        code/core/gl/GLShader.h
        code/core/Names.h
        code/core/Pipeline.h
        code/core/Simulator.h
        code/core/CustomLogic.h
        code/core/CGAPIManager.h
        code/core/techniques/R25DPipeline.h
        code/core/PipelineUtils.h
        code/core/gl/GLRenderer.h
        code/core/gl/GLRenderer.cpp
        code/core/items/Entity.h
        code/core/RenderObject.h
        code/core/items/Picture.h
        code/core/SceneNode.h
        code/core/FrustumCullingCalculator.h
        code/runtime/vm/LuaVM.h
        code/runtime/vm/LuaRegister.h
        code/runtime/vm/LuaExtensions.h
        code/runtime/HPMSLogic.h
        code/runtime/GameState.h
        code/runtime/states/R25DGameState.h
        code/runtime/input/KeyEvent.h
        code/common/HPMSObject.h
        code/core/FrameBuffer.h
        code/core/PostFX.h
        code/core/gl/GLFrameBuffer.h
        code/core/gl/fx/GLDefaultPostFX.h
        code/common/Debug.h
        code/logic/Room.h
        code/logic/CalcUtils.h)

set(ROOM_TOOLS_SOURCE_FILES
        thirdparty/GLAD/src/glad.c
        code/common/Utils.h
        code/common/FileSystem.h
        code/core/Material.h
        code/core/Mesh.cpp
        code/core/Mesh.h
        code/core/Actor.h
        code/core/StdModelItem.cpp
        code/core/StdModelItem.h
        code/core/AdvModelItem.cpp
        code/core/AdvModelItem.h
        code/core/Animation.cpp
        code/core/Animation.h
        code/core/Renderer.h
        code/core/Texture.h
        code/core/ResourceCache.h
        code/common/FileSystem.cpp
        code/common/HPMSObject.h
        code/logic/Room.h
        code/logic/CalcUtils.h
        code/tools/RoomImporter.cpp
        code/tools/RoomImporter.h)

set(AI_TOOLS_SOURCE_FILES
        thirdparty/GLAD/src/glad.c
        code/common/Utils.h
        code/common/FileSystem.h
        code/core/Material.h
        code/core/Mesh.cpp
        code/core/Mesh.h
        code/tools/AssimpImporter.cpp
        code/tools/AssimpImporter.h
        code/core/Actor.h
        code/core/StdModelItem.cpp
        code/core/StdModelItem.h
        code/core/AdvModelItem.cpp
        code/core/AdvModelItem.h
        code/core/Animation.cpp
        code/core/Animation.h
        code/core/Renderer.h
        code/core/Texture.h
        code/core/ResourceCache.h
        code/common/FileSystem.cpp
        code/common/HPMSObject.h)


set(dir ${CMAKE_CURRENT_SOURCE_DIR})

# Setup bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/bin)

# Setup assimp for converter
set(ENABLE_BOOST_WORKAROUND ON)
set(ASSIMP_BUILD_3DS_IMPORTER OFF CACHE BOOL "Disable 3DS" FORCE)
set(ASSIMP_BUILD_3D_IMPORTER OFF CACHE BOOL "Disable 3D" FORCE)
set(ASSIMP_BUILD_3MF_IMPORTER OFF CACHE BOOL "Disable 3MF" FORCE)
set(ASSIMP_BUILD_AC_IMPORTER OFF CACHE BOOL "Disable AC" FORCE)
set(ASSIMP_BUILD_AMF_IMPORTER OFF CACHE BOOL "Disable AMF" FORCE)
set(ASSIMP_BUILD_ASE_IMPORTER OFF CACHE BOOL "Disable ASE" FORCE)
set(ASSIMP_BUILD_B3D_IMPORTER OFF CACHE BOOL "Disable B3D" FORCE)
set(ASSIMP_BUILD_BLEND_IMPORTER OFF CACHE BOOL "Disbale Blend" FORCE)
set(ASSIMP_BUILD_BVH_IMPORTER OFF CACHE BOOL "Disable BVH" FORCE)
set(ASSIMP_BUILD_COB_IMPORTER OFF CACHE BOOL "Disable COB" FORCE)
set(ASSIMP_BUILD_CSM_IMPORTER OFF CACHE BOOL "Disable CSM" FORCE)
set(ASSIMP_BUILD_DXF_IMPORTER OFF CACHE BOOL "Disable DXF" FORCE)
set(ASSIMP_BUILD_HMP_IMPORTER OFF CACHE BOOL "Disable HMP" FORCE)
set(ASSIMP_BUILD_IFC_IMPORTER OFF CACHE BOOL "Disable IFC" FORCE)
set(ASSIMP_BUILD_IRRMESH_IMPORTER OFF CACHE BOOL "Disable IRRMESH" FORCE)
set(ASSIMP_BUILD_IRR_IMPORTER OFF CACHE BOOL "Disable IRR" FORCE)
set(ASSIMP_BUILD_LWO_IMPORTER OFF CACHE BOOL "Disable LWO" FORCE)
set(ASSIMP_BUILD_LWS_IMPORTER OFF CACHE BOOL "Disable LWS" FORCE)
set(ASSIMP_BUILD_NDO_IMPORTER OFF CACHE BOOL "Disable NDO" FORCE)
set(ASSIMP_BUILD_NFF_IMPORTER OFF CACHE BOOL "Disable NFF" FORCE)
set(ASSIMP_BUILD_NONFREE_C4D_IMPORTER OFF CACHE BOOL "Disable C4D" FORCE)
set(ASSIMP_BUILD_PLY_IMPORTER OFF CACHE BOOL "Disable PLY" FORCE)
set(ASSIMP_BUILD_SIB_IMPORTER OFF CACHE BOOL "Disable SIB" FORCE)
set(ASSIMP_BUILD_SMD_IMPORTER OFF CACHE BOOL "Disable SMD" FORCE)
set(ASSIMP_BUILD_STL_IMPORTER OFF CACHE BOOL "Disable STL" FORCE)
set(ASSIMP_BUILD_TERRAGEN_IMPORTER OFF CACHE BOOL "Disable Terragen" FORCE)
set(ASSIMP_BUILD_X3D_IMPORTER OFF CACHE BOOL "Disable X3D" FORCE)
set(ASSIMP_BUILD_XGL_IMPORTER OFF CACHE BOOL "Disable XGL" FORCE)
set(ASSIMP_BUILD_X_IMPORTER OFF CACHE BOOL "Disable X" FORCE)
set(ASSIMP_BUILD_ASSBIN_IMPORTER OFF CACHE BOOL "Disable ASSBIN" FORCE)
set(ASSIMP_BUILD_MD2_IMPORTER OFF CACHE BOOL "Disable MD2" FORCE)
set(ASSIMP_BUILD_MD3_IMPORTER OFF CACHE BOOL "Disable MD3" FORCE)
set(ASSIMP_BUILD_MD5_IMPORTER OFF CACHE BOOL "Disable MD5" FORCE)
set(ASSIMP_BUILD_MDC_IMPORTER OFF CACHE BOOL "Disable MDC" FORCE)
set(ASSIMP_BUILD_MDL_IMPORTER OFF CACHE BOOL "Disable MDL" FORCE)
set(ASSIMP_BUILD_MS3D_IMPORTER OFF CACHE BOOL "Disable MS3D" FORCE)
set(ASSIMP_BUILD_OFF_IMPORTER OFF CACHE BOOL "Disable OFF" FORCE)
set(ASSIMP_BUILD_OGRE_IMPORTER OFF CACHE BOOL "Disable OGRE" FORCE)
set(ASSIMP_BUILD_OPENGEX_IMPORTER OFF CACHE BOOL "Disable OPENGEX" FORCE)
set(ASSIMP_BUILD_Q3BSP_IMPORTER OFF CACHE BOOL "Disable Q3BSP" FORCE)
set(ASSIMP_BUILD_Q3D_IMPORTER OFF CACHE BOOL "Disable Q3D" FORCE)
set(ASSIMP_BUILD_RAW_IMPORTER OFF CACHE BOOL "Disable RAW" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER OFF CACHE BOOL "Disable GLTF" FORCE)
set(ASSIMP_BUILD_ASSXML_IMPORTER OFF CACHE BOOL "Disable ASSXML" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER OFF CACHE BOOL "Disable FBX" FORCE)
set(ASSIMP_BUILD_MMD_IMPORTER OFF CACHE BOOL "Disable MMD" FORCE)

# Include third party
include_directories(thirdparty/GLAD/include)
include_directories(thirdparty/GLM/include)
include_directories(thirdparty/STB/include)
include_directories(thirdparty/LUA/include)
include_directories(thirdparty/PHYSFS/include)
include_directories(thirdparty/PODS/include)
include_directories(thirdparty/ASSIMP/include)
include_directories(thirdparty/RAPIDJSON/include)
include_directories(thirdparty/LUABRIDGE/include)
include_directories(thirdparty/LIGHTCONF/include)
include_directories(thirdparty/IMGUI/include)
include_directories(thirdparty/PUGIXML/include)

# Copy all resources to bin folder
file(COPY data DESTINATION ${dir}/bin)

# Copy all default shared libraries in bin folder
file(GLOB DLLS ${dir}/libs/*.dll)
file(COPY ${DLLS} DESTINATION ${dir}/bin)

# Add libraries dependencies
add_subdirectory(dependencies)

# Build the main runtime
add_executable(HPMS ${RT_SOURCE_FILES} code/runtime/Main.cpp)
target_link_libraries(HPMS glfw physfs liblua)

# Build the tools runtimes
add_executable(AIToHMDATConverter ${AI_TOOLS_SOURCE_FILES} code/tools/AssimpToHDATConverter.cpp)
target_link_libraries(HPMS assimp physfs)

add_executable(RoomToHRDATConverter ${ROOM_TOOLS_SOURCE_FILES} code/tools/RoomToHDATConverter.cpp)
target_link_libraries(HPMS physfs)