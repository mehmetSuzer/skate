
#ifndef __SCENE_H__
#define __SCENE_H__

#include <vbo.h>

#define OBJECT_VERTEX_TYPE     TEXTURE_VERTEX

const std::vector<ColorVertex> objectColorVertices =
{  			   //         positions          /            normals            /               colors               //
	ColorVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Bottom side
	ColorVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Bottom side
	ColorVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Bottom side
	ColorVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Bottom side

	ColorVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3(-0.8f,  0.6f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Left Side
	ColorVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3(-0.8f,  0.6f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Left Side
	ColorVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f,  0.6f,  0.0f), glm::vec4(0.92f, 0.86f, 0.76f, 1.0f)}, // Left Side

	ColorVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f,  0.6f, -0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Non-facing side
	ColorVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f,  0.6f, -0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Non-facing side
	ColorVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f,  0.6f, -0.8f), glm::vec4(0.92f, 0.86f, 0.76f, 1.0f)}, // Non-facing side

	ColorVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.8f,  0.6f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Right side
	ColorVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.8f,  0.6f,  0.0f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Right side
	ColorVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f,  0.6f,  0.0f), glm::vec4(0.92f, 0.86f, 0.76f, 1.0f)}, // Right side

	ColorVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f,  0.6f,  0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Facing side
	ColorVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f,  0.6f,  0.8f), glm::vec4(0.83f, 0.70f, 0.44f, 1.0f)}, // Facing side
	ColorVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f,  0.6f,  0.8f), glm::vec4(0.92f, 0.86f, 0.76f, 1.0f)}, // Facing side
};

const std::vector<TextureVertex> objectTextureVertices =
{  			     //         positions          /            normals           /       textures      //
	TextureVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Bottom side
	TextureVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 5.0f)}, // Bottom side
	TextureVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 5.0f)}, // Bottom side
	TextureVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 0.0f)}, // Bottom side

	TextureVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3(-0.8f, 0.6f,  0.0f), glm::vec2(0.0f, 0.0f)}, // Left Side
	TextureVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3(-0.8f, 0.6f,  0.0f), glm::vec2(5.0f, 0.0f)}, // Left Side
	TextureVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.6f,  0.0f), glm::vec2(2.5f, 5.0f)}, // Left Side

	TextureVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f), glm::vec2(5.0f, 0.0f)}, // Non-facing side
	TextureVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f), glm::vec2(0.0f, 0.0f)}, // Non-facing side
	TextureVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f, -0.8f), glm::vec2(2.5f, 5.0f)}, // Non-facing side

	TextureVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.8f, 0.6f,  0.0f), glm::vec2(0.0f, 0.0f)}, // Right side
	TextureVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.8f, 0.6f,  0.0f), glm::vec2(5.0f, 0.0f)}, // Right side
	TextureVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f, 0.6f,  0.0f), glm::vec2(2.5f, 5.0f)}, // Right side

	TextureVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f), glm::vec2(5.0f, 0.0f)}, // Facing side
	TextureVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f), glm::vec2(0.0f, 0.0f)}, // Facing side
	TextureVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f,  0.8f), glm::vec2(2.5f, 5.0f)}, // Facing side
};

const std::vector<NormalVertex> objectNormalVertices =
{  			    //        positions          /            normals           //
	NormalVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side
	NormalVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side
	NormalVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side
	NormalVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side

	NormalVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3(-0.8f, 0.6f,  0.0f)}, // Left Side
	NormalVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3(-0.8f, 0.6f,  0.0f)}, // Left Side
	NormalVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.6f,  0.0f)}, // Left Side

	NormalVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f)}, // Non-facing side
	NormalVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f)}, // Non-facing side
	NormalVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f, -0.8f)}, // Non-facing side

	NormalVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.8f, 0.6f,  0.0f)}, // Right side
	NormalVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.8f, 0.6f,  0.0f)}, // Right side
	NormalVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f, 0.6f,  0.0f)}, // Right side

	NormalVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f)}, // Facing side
	NormalVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f)}, // Facing side
	NormalVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f,  0.8f)}, // Facing side
};

const std::vector<GLuint> objectIndices =
{
	0, 1, 2,    // Bottom side
	0, 2, 3,    // Bottom side
	4, 6, 5,    // Left side
	7, 9, 8,    // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14, // Facing side
};

const std::vector<BasicVertex> lightVertices =
{ 				//         positions         //
	BasicVertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	BasicVertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	BasicVertex{glm::vec3( 0.1f, -0.1f, -0.1f)},
	BasicVertex{glm::vec3( 0.1f, -0.1f,  0.1f)},
	BasicVertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	BasicVertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	BasicVertex{glm::vec3( 0.1f,  0.1f, -0.1f)},
	BasicVertex{glm::vec3( 0.1f,  0.1f,  0.1f)},
};

const std::vector<GLuint> lightIndices =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7,
};

#endif // __SCENE_H__
