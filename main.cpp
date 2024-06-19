
#include <ebo.h>
#include <vao.h>
#include <texture2D.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH    800UL
#define WINDOW_HEIGHT   600UL
#define ASPECT_RATIO    (static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT))

#define VERTEX_TYPE     TEXTURE_VERTEX

std::vector<ColorVertex> colorVertices =
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

std::vector<TextureVertex> textureVertices =
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

std::vector<GLuint> indices =
{
	0, 1, 2,    // Bottom side
	0, 2, 3,    // Bottom side
	4, 6, 5,    // Left side
	7, 9, 8,    // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14  // Facing side
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(int argc, char **argv) {
    const std::string glslPath = "glsl/";
    const std::string modelsPath = "data/models/";
    const std::string texturesPath = "data/textures/";

    if (glfwInit() == GLFW_FALSE) {
        throw Error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Learn OpenGL", NULL, NULL); 
    if (window == NULL) {
        glfwTerminate();
        throw Error("Failed to create GLFW Window!");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw Error("Failed to initialize GLAD!");
    }

    VAO VAO;
    VAO.Bind();
    EBO EBO(indices);

#if VERTEX_TYPE == TEXTURE_VERTEX
    VBO VBO(textureVertices, GL_STATIC_DRAW);
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)0);                         // position
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)(sizeof(glm::vec3)));       // normal
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)(2 * sizeof(glm::vec3)));   // texture
#else
    VBO VBO(colorVertices);
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);                           // position
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)(sizeof(glm::vec3)));         // normal
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)(2 * sizeof(glm::vec3)));     // color
#endif

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
    
    Texture2D::SetBorderColor(1.0f, 1.0f, 1.0f, 1.0f);
    Texture2D texture0 = Texture2D((texturesPath + "awesomeface.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    
#if VERTEX_TYPE == TEXTURE_VERTEX
    Shader shaderProgram = Shader(
        (glslPath + "texture_vertex.glsl").c_str(), 
        (glslPath + "texture_fragment.glsl").c_str()
    );
#else
    Shader shaderProgram = Shader(
        (glslPath + "color_vertex.glsl").c_str(), 
        (glslPath + "color_fragment.glsl").c_str()
    );
#endif

    shaderProgram.Use();
    shaderProgram.SetUniformInt(0, "textureImage");

    glm::vec3 position = glm::vec3(0.0f, -0.25f, 2.5f);
    float radian = 0.0f;
    float scalar = 1.0f;

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);

    float FOVradian = M_PIf / 4.0f;
    float near = 0.1f;
    float far = 100.0f;
    glm::mat4 projection = glm::perspective(FOVradian, ASPECT_RATIO, near, far);

    // Enable the depth buffer
	glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        radian = glfwGetTime();
        glm::quat rotation = glm::angleAxis(radian, glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
	    model = model * glm::mat4_cast(rotation);
        model = glm::scale(model, glm::vec3(scalar));

        glm::mat4 transform = projection * view * model;
        shaderProgram.SetUniformMat4(transform, "transform");

        texture0.Bind(0);
        shaderProgram.Use();
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    texture0.Delete();
    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}
