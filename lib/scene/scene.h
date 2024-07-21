
#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "vertex.h"
#include "light.h"

const std::vector<ColorVertex> pyramidColorVertices =
{  			   //         positions         /            normals            /              colors              //
	ColorVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // Bottom side
	ColorVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // Bottom side
	ColorVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // Bottom side
	ColorVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, // Bottom side

	ColorVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3(-0.8f,  0.6f,  0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // Left Side
	ColorVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3(-0.8f,  0.6f,  0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // Left Side
	ColorVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f,  0.6f,  0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}, // Left Side

	ColorVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f,  0.6f, -0.8f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // Non-facing side
	ColorVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f,  0.6f, -0.8f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // Non-facing side
	ColorVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f,  0.6f, -0.8f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}, // Non-facing side

	ColorVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.8f,  0.6f,  0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // Right side
	ColorVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.8f,  0.6f,  0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, // Right side
	ColorVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f,  0.6f,  0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}, // Right side

	ColorVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f,  0.6f,  0.8f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, // Facing side
	ColorVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f,  0.6f,  0.8f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // Facing side
	ColorVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f,  0.6f,  0.8f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}, // Facing side
};

const std::vector<TextureVertex> pyramidTextureVertices =
{  		         //        positions          /            normals           /       textures       //
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

const std::vector<MaterialVertex> pyramidMaterialVertices =
{  		          //        positions          /            normals           //
	MaterialVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side
	MaterialVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side
	MaterialVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side
	MaterialVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side

	MaterialVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3(-0.8f, 0.6f,  0.0f)}, // Left Side
	MaterialVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3(-0.8f, 0.6f,  0.0f)}, // Left Side
	MaterialVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.6f,  0.0f)}, // Left Side

	MaterialVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f)}, // Non-facing side
	MaterialVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f)}, // Non-facing side
	MaterialVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f, -0.8f)}, // Non-facing side

	MaterialVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.8f, 0.6f,  0.0f)}, // Right side
	MaterialVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.8f, 0.6f,  0.0f)}, // Right side
	MaterialVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f, 0.6f,  0.0f)}, // Right side

	MaterialVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f)}, // Facing side
	MaterialVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f)}, // Facing side
	MaterialVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f,  0.8f)}, // Facing side
};

const std::vector<GLuint> pyramidIndices =
{
	0, 1, 2,    // Bottom side
	0, 2, 3,    // Bottom side
	4, 6, 5,    // Left side
	7, 9, 8,    // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14, // Facing side
};

const std::vector<TextureVertex> containerTextureVertices = {
        	     //         positions          /             normals           /        textures       //
	TextureVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f,  0.0f)},
	TextureVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f,  1.0f)},
	TextureVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f,  1.0f)},
	TextureVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f,  0.0f)},

    TextureVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f,  0.0f)},
    TextureVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f,  0.0f)},
    TextureVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f,  1.0f)},
    TextureVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f,  1.0f)},

    TextureVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  0.0f)},
    TextureVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  1.0f)},
    TextureVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  1.0f)},
    TextureVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  0.0f)},

	TextureVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  0.0f)},
	TextureVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  0.0f)},
	TextureVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  1.0f)},
	TextureVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  1.0f)},

    TextureVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f,  1.0f)},
    TextureVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f,  1.0f)},
    TextureVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f,  0.0f)},
    TextureVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f,  0.0f)},

	TextureVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f,  1.0f)},
	TextureVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f,  0.0f)},
	TextureVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f,  0.0f)},
	TextureVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f,  1.0f)},
};

const std::vector<GLuint> containerIndices =
{
	0, 1, 2,
	0, 2, 3,
	4, 5, 6,
	4, 6, 7,
	8, 9, 10,
	8, 10, 11,
	12, 13, 14,
	12, 14, 15,
	16, 17, 18,
	16, 18, 19,
	20, 21, 22,
	20, 22, 23,
};

const std::vector<MaterialVertex> lightVertices =
{ 		          //         positions          /                    normals                           //
	MaterialVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::sqrt(1.0f/3.0f) * glm::vec3(-1.0f, -1.0f, -1.0f)},
	MaterialVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::sqrt(1.0f/3.0f) * glm::vec3(-1.0f,  1.0f, -1.0f)},
	MaterialVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::sqrt(1.0f/3.0f) * glm::vec3( 1.0f,  1.0f, -1.0f)},
	MaterialVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::sqrt(1.0f/3.0f) * glm::vec3( 1.0f, -1.0f, -1.0f)},
	
	MaterialVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::sqrt(1.0f/3.0f) * glm::vec3(-1.0f, -1.0f,  1.0f)},
	MaterialVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::sqrt(1.0f/3.0f) * glm::vec3( 1.0f, -1.0f,  1.0f)},
	MaterialVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::sqrt(1.0f/3.0f) * glm::vec3( 1.0f,  1.0f,  1.0f)},
	MaterialVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::sqrt(1.0f/3.0f) * glm::vec3(-1.0f,  1.0f,  1.0f)},
};

const std::vector<GLuint> lightIndices =
{
	0, 1, 2,
	0, 2, 3,
	4, 5, 6,
	4, 6, 7,
	0, 3, 6, 
	0, 6, 5,
	1, 4, 7,
	1, 7, 2,
	0, 5, 4,
	0, 4, 1,
	2, 7, 6,
	2, 6, 3,
};

#endif // __SCENE_H__
