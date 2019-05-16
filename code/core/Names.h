/*!
 * File Names.h
 */

#pragma once

// Main folders

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
#define UNIFORM_MODELVIEWMATRIX "u_ModelViewMatrix"
#define UNIFORM_PROJMATRIX "u_ProjectionMatrix"
#define UNIFORM_TEXSAMPLER "u_TextureSampler"
#define UNIFORM_NORMALSAMPLER "u_NormalSampler"
#define UNIFORM_NUMCOLS "u_NumCols"
#define UNIFORM_NUMROWS "u_NumRows"
#define UNIFORM_AMBIENTLIGHT "u_AmbientLight"
#define UNIFORM_MATERIAL "u_Material"
#define UNIFORM_JOINTSMATRIX "u_JointsMatrix"
#define UNIFORM_ZNEAR "u_ZNear"
#define UNIFORM_ZFAR "u_ZFar"
#define UNIFORM_ALPHA "u_Alpha"
#define UNIFORM_DIFFUSEINTENSITY "u_DiffuseIntensity"
#define UNIFORM_X "u_X"
#define UNIFORM_Y "u_Y"
#define UNIFORM_GLOBALALPHA "u_GlobalAlpha"

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

// PostFX params.
#define PARAM_GLOBAL_ALPHA "p_Alpha"