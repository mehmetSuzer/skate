
#ifndef __SCENE_H__
#define __SCENE_H__

#include <common.h>
#include <light.h>
#include <model.h>

const std::vector<PNCVertex> pyramidColorVertices =
{  			 //         positions         /            normals            /              colors              //
	PNCVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // Bottom side
	PNCVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // Bottom side
	PNCVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // Bottom side
	PNCVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, // Bottom side

	PNCVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3(-0.8f,  0.6f,  0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // Left Side
	PNCVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3(-0.8f,  0.6f,  0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // Left Side
	PNCVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f,  0.6f,  0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}, // Left Side

	PNCVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f,  0.6f, -0.8f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}, // Non-facing side
	PNCVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f,  0.6f, -0.8f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // Non-facing side
	PNCVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f,  0.6f, -0.8f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}, // Non-facing side

	PNCVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.8f,  0.6f,  0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}, // Right side
	PNCVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.8f,  0.6f,  0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, // Right side
	PNCVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f,  0.6f,  0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}, // Right side

	PNCVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f,  0.6f,  0.8f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)}, // Facing side
	PNCVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f,  0.6f,  0.8f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}, // Facing side
	PNCVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f,  0.6f,  0.8f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}, // Facing side
};

const std::vector<PNTVertex> pyramidTextureVertices =
{  		     //        positions          /            normals           /       textures       //
	PNTVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Bottom side
	PNTVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 5.0f)}, // Bottom side
	PNTVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 5.0f)}, // Bottom side
	PNTVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 0.0f)}, // Bottom side

	PNTVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3(-0.8f, 0.6f,  0.0f), glm::vec2(0.0f, 0.0f)}, // Left Side
	PNTVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3(-0.8f, 0.6f,  0.0f), glm::vec2(5.0f, 0.0f)}, // Left Side
	PNTVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.6f,  0.0f), glm::vec2(2.5f, 5.0f)}, // Left Side

	PNTVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f), glm::vec2(5.0f, 0.0f)}, // Non-facing side
	PNTVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f), glm::vec2(0.0f, 0.0f)}, // Non-facing side
	PNTVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f, -0.8f), glm::vec2(2.5f, 5.0f)}, // Non-facing side

	PNTVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.8f, 0.6f,  0.0f), glm::vec2(0.0f, 0.0f)}, // Right side
	PNTVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.8f, 0.6f,  0.0f), glm::vec2(5.0f, 0.0f)}, // Right side
	PNTVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f, 0.6f,  0.0f), glm::vec2(2.5f, 5.0f)}, // Right side

	PNTVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f), glm::vec2(5.0f, 0.0f)}, // Facing side
	PNTVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f), glm::vec2(0.0f, 0.0f)}, // Facing side
	PNTVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f,  0.8f), glm::vec2(2.5f, 5.0f)}, // Facing side
};

const std::vector<PNVertex> pyramidNormalVertices =
{  		    //        positions          /            normals           //
	PNVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side
	PNVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side
	PNVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side
	PNVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, -1.0f, 0.0f)}, // Bottom side

	PNVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3(-0.8f, 0.6f,  0.0f)}, // Left Side
	PNVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3(-0.8f, 0.6f,  0.0f)}, // Left Side
	PNVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.6f,  0.0f)}, // Left Side

	PNVertex{glm::vec3(-0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f)}, // Non-facing side
	PNVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.0f, 0.6f, -0.8f)}, // Non-facing side
	PNVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f, -0.8f)}, // Non-facing side

	PNVertex{glm::vec3( 0.6f, 0.0f, -0.6f), glm::vec3( 0.8f, 0.6f,  0.0f)}, // Right side
	PNVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.8f, 0.6f,  0.0f)}, // Right side
	PNVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f, 0.6f,  0.0f)}, // Right side

	PNVertex{glm::vec3( 0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f)}, // Facing side
	PNVertex{glm::vec3(-0.6f, 0.0f,  0.6f), glm::vec3( 0.0f, 0.6f,  0.8f)}, // Facing side
	PNVertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.6f,  0.8f)}, // Facing side
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

// const std::vector<Texture2D> pyramidTextures = 
// {
// 	brickTexture
// };

// const std::vector<Mesh> pyramidMeshes = 
// {
// 	Mesh(pyramidTextureVertices, pyramidIndices, pyramidTextures, 16, GL_STATIC_DRAW),
// };

// const glm::vec3 pyramidPosition = glm::vec3(0.0f, -0.0f, -2.5f);
// const glm::quat pyramidRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
// const glm::vec3 pyramidScalar = glm::vec3(1.0f, 1.0f, 1.0f);

// const Model pyramid = Model(pyramidMeshes, pyramidPosition, pyramidRotation, pyramidScalar);

const std::vector<PNTVertex> containerTextureVertices = {
        	 //         positions          /             normals           /        textures       //
    PNTVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f,  0.0f)},
    PNTVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f,  0.0f)},
    PNTVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f,  1.0f)},
    PNTVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f,  1.0f)},

    PNTVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f,  0.0f)},
    PNTVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f,  0.0f)},
    PNTVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f,  1.0f)},
    PNTVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f,  1.0f)},

    PNTVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  0.0f)},
    PNTVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  1.0f)},
    PNTVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  1.0f)},
    PNTVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  0.0f)},

    PNTVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  0.0f)},
    PNTVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  1.0f)},
    PNTVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  1.0f)},
    PNTVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  0.0f)},

    PNTVertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f,  1.0f)},
    PNTVertex{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f,  1.0f)},
    PNTVertex{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f,  0.0f)},
    PNTVertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f,  0.0f)},

    PNTVertex{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f,  1.0f)},
    PNTVertex{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f,  1.0f)},
    PNTVertex{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f,  0.0f)},
    PNTVertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f,  0.0f)},
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

const std::vector<PVertex> lightVertices =
{ 		   //         positions         //
	PVertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	PVertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	PVertex{glm::vec3( 0.1f, -0.1f, -0.1f)},
	PVertex{glm::vec3( 0.1f, -0.1f,  0.1f)},
	PVertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	PVertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	PVertex{glm::vec3( 0.1f,  0.1f, -0.1f)},
	PVertex{glm::vec3( 0.1f,  0.1f,  0.1f)},
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
