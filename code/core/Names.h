/*!
 * File Names.h
 */

#pragma once

// Main folders
#define CONFIG_FILE "data/HPMS.cfg"
#define SEPARATOR "/"
#ifndef DATA_ARCHIVE
#define MODELS_FOLDER "data/resources/models/"
#define TEXTURE_FOLDER "data/resources/textures/"
#define SCREENS_FOLDER "data/resources/screens/"
#define SHADERS_FOLDER "data/shaders/"
#define SCRIPTS_FOLDER "data/scripts/"
#else
#define MODELS_FOLDER "resources/models/"
#define TEXTURE_FOLDER "resources/textures/"
#define SCREENS_FOLDER "resources/screens/"
#define SHADERS_FOLDER "shaders/"
#define SCRIPTS_FOLDER "scripts/"
#endif

// Composite material shader uniform.
#define UNIFORM_DIFFUSE_SFX ".diffuse"
#define UNIFORM_HASTEXTURE_SFX ".hasTexture"

// Simple shader uniform list.
#define UNIFORM_VIEWMATRIX "viewMatrix"
#define UNIFORM_PROJMATRIX "projectionMatrix"
#define UNIFORM_PROJMODELMATRIX "projModelMatrix"
#define UNIFORM_MODELVIEWMATRIX "modelViewMatrix"
#define UNIFORM_TEXSAMPLER "textureSampler"
#define UNIFORM_NORMALSAMPLER "normalSampler"
#define UNIFORM_NUMCOLS "numCols"
#define UNIFORM_NUMROWS "numRows"
#define UNIFORM_AMBIENTLIGHT "ambientLight"
#define UNIFORM_COLOUR "colour"
#define UNIFORM_HASTEXTURE "hasTexture"
#define UNIFORM_MATERIAL "material"
#define UNIFORM_NONINSTMATRIX "modelNonInstancedMatrix"
#define UNIFORM_INSTANCED "instanced"
#define UNIFORM_JOINTSMATRIX "jointsMatrix"
#define UNIFORM_ZNEAR "zNear"
#define UNIFORM_ZFAR "zFar"
#define UNIFORM_ALPHA "alpha"
#define UNIFORM_DIFFUSEINTENSITY "diffuseIntensity"
#define UNIFORM_X "x"
#define UNIFORM_Y "y"
#define UNIFORM_GLOBALALPHA "globalAlpha"

#define SHADER_FILE_PARTICLES_VERT SHADERS_FOLDER "Particles.vert"
#define SHADER_FILE_PARTICLES_FRAG SHADERS_FOLDER "Particles.frag"
#define SHADER_FILE_PIXELFX_VERT SHADERS_FOLDER "PostFX.vert"
#define SHADER_FILE_PIXELFX_FRAG SHADERS_FOLDER "PostFX.frag"
#define SHADER_FILE_SCENE_VERT SHADERS_FOLDER "Scene.vert"
#define SHADER_FILE_SCENE_FRAG SHADERS_FOLDER "Scene.frag"
#define SHADER_FILE_PICTURE_VERT SHADERS_FOLDER "Picture.vert"
#define SHADER_FILE_PICTURE_FRAG SHADERS_FOLDER "Picture.frag"
#define SHADER_FILE_DEPTHMASK_VERT SHADERS_FOLDER "DepthMask.vert"
#define SHADER_FILE_DEPTHMASK_FRAG SHADERS_FOLDER "DepthMask.frag"