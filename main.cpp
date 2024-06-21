
#include <ebo.h>
#include <vao.h>
#include <scene.h>
#include <input_handler.h>
#include <shader.h>
#include <texture2D.h>

int main(int argc, char **argv) {
    if (glfwInit() == GLFW_FALSE) {
        throw Error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(
        Common::Instance().GetWindowWidth(),
        Common::Instance().GetWindowHeight(),
        "Learn OpenGL", 
        NULL, 
        NULL
    ); 
    if (window == NULL) {
        glfwTerminate();
        throw Error("Failed to create GLFW Window!");
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, Common::Instance().GetWindowWidth(), Common::Instance().GetWindowHeight());

    Camera::Instance().Initialize();
    InputHandler::Instance().Initialize(window);

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
    Texture2D texture0 = Texture2D((Common::Instance().GetTexturesPath() + "brick.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    
#if VERTEX_TYPE == TEXTURE_VERTEX
    Shader shaderProgram = Shader(
        (Common::Instance().GetGLSLPath() + "texture_vertex.glsl").c_str(), 
        (Common::Instance().GetGLSLPath() + "texture_fragment.glsl").c_str()
    );
#else
    Shader shaderProgram = Shader(
        (Common::Instance().GetGLSLPath() + "color_vertex.glsl").c_str(), 
        (Common::Instance().GetGLSLPath() + "color_fragment.glsl").c_str()
    );
#endif

    shaderProgram.Use();
    shaderProgram.SetUniformInt(0, "textureImage");

    glm::vec3 position = glm::vec3(0.0f, -0.25f, -2.5f);
    float radian = 0.0f;
    glm::quat rotation = glm::angleAxis(radian, glm::vec3(0.0f, 1.0f, 0.0f));
    float scalar = 1.0f;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
	model = model * glm::mat4_cast(rotation);
    model = glm::scale(model, glm::vec3(scalar));

    // Enable the depth buffer
	glEnable(GL_DEPTH_TEST);

    float currentTime;
    float lastTime = glfwGetTime();
    float elapsedTimeSinceLastFrame;

    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        elapsedTimeSinceLastFrame = currentTime - lastTime;
        lastTime = currentTime;

        Camera::Instance().UpdatePosition(elapsedTimeSinceLastFrame);

        const glm::vec4& backgroundColor = Common::Instance().GetBackgroundColor();
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 transform = Camera::Instance().GetPerspective() * Camera::Instance().GetView() * model;
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
