
#ifndef __SCENE_H__
#define __SCENE_H__

#include <vbo.h>

#define VERTEX_TYPE     TEXTURE_VERTEX

const std::vector<ColorVertex> colorVertices =
{  			   //        positions          /            normals             /           colors           //
	ColorVertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Bottom side
	ColorVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Bottom side
	ColorVertex{glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Bottom side
	ColorVertex{glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Bottom side

	ColorVertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(-0.8f, 0.6f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Left Side
	ColorVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-0.8f, 0.6f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Left Side
	ColorVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.6f, 0.0f), glm::vec3(0.92f, 0.86f, 0.76f)}, // Left Side

	ColorVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.6f, -0.8f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Non-facing side
	ColorVertex{glm::vec3(0.5f,  0.0f, -0.5f), glm::vec3(0.0f, 0.6f, -0.8f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Non-facing side
	ColorVertex{glm::vec3(0.0f,  0.8f,  0.0f), glm::vec3(0.0f, 0.6f, -0.8f), glm::vec3(0.92f, 0.86f, 0.76f)}, // Non-facing side

	ColorVertex{glm::vec3(0.5f,  0.0f, -0.5f), glm::vec3(0.8f, 0.6f,  0.0f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Right side
	ColorVertex{glm::vec3(0.5f,  0.0f,  0.5f), glm::vec3(0.8f, 0.6f,  0.0f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Right side
	ColorVertex{glm::vec3(0.0f,  0.8f,  0.0f), glm::vec3(0.8f, 0.6f,  0.0f), glm::vec3(0.92f, 0.86f, 0.76f)}, // Right side

	ColorVertex{glm::vec3(0.5f,  0.0f,  0.5f), glm::vec3(0.0f, 0.6f,  0.8f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Facing side
	ColorVertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 0.6f,  0.8f), glm::vec3(0.83f, 0.70f, 0.44f)}, // Facing side
	ColorVertex{glm::vec3(0.0f,  0.8f,  0.0f), glm::vec3(0.0f, 0.6f,  0.8f), glm::vec3(0.92f, 0.86f, 0.76f)}, // Facing side
};

const std::vector<TextureVertex> textureVertices =
{  			      //        positions          /            normals           /       textures      //
	TextureVertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Bottom side
	TextureVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 5.0f)}, // Bottom side
	TextureVertex{glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 5.0f)}, // Bottom side
	TextureVertex{glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 0.0f)}, // Bottom side

	TextureVertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(-0.8f, 0.6f,  0.0f), glm::vec2(0.0f, 0.0f)}, // Left Side
	TextureVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-0.8f, 0.6f,  0.0f), glm::vec2(5.0f, 0.0f)}, // Left Side
	TextureVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.6f,  0.0f), glm::vec2(2.5f, 5.0f)}, // Left Side

	TextureVertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, 0.6f, -0.8f), glm::vec2(5.0f, 0.0f)}, // Non-facing side
	TextureVertex{glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, 0.6f, -0.8f), glm::vec2(0.0f, 0.0f)}, // Non-facing side
	TextureVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f, -0.8f), glm::vec2(2.5f, 5.0f)}, // Non-facing side

	TextureVertex{glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 0.8f, 0.6f,  0.0f), glm::vec2(0.0f, 0.0f)}, // Right side
	TextureVertex{glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 0.8f, 0.6f,  0.0f), glm::vec2(5.0f, 0.0f)}, // Right side
	TextureVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f, 0.6f,  0.0f), glm::vec2(2.5f, 5.0f)}, // Right side

	TextureVertex{glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, 0.6f,  0.8f), glm::vec2(5.0f, 0.0f)}, // Facing side
	TextureVertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, 0.6f,  0.8f), glm::vec2(0.0f, 0.0f)}, // Facing side
	TextureVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f,  0.8f), glm::vec2(2.5f, 5.0f)}, // Facing side
};

const std::vector<GLuint> indices =
{
	0, 1, 2,    // Bottom side
	0, 2, 3,    // Bottom side
	4, 6, 5,    // Left side
	7, 9, 8,    // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14  // Facing side
};

#endif // __SCENE_H__
