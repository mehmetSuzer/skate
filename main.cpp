
#include <iostream>

#include <ebo.h>
#include <vao.h>
#include <scene.h>
#include <input_handler.h>
#include <shader.h>
#include <texture2D.h>

#include <point_light.h>
#include <spot_light.h>
#include <directional_light.h>

int main(int argc, char **argv) {
    /***************************************** INITIALIZATION *****************************************/

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

    Camera::Instance().Initialize();
    InputHandler::Instance().Initialize(window);
    Texture2D::SetBorderColor(1.0f, 1.0f, 1.0f, 1.0f);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw Error("Failed to initialize GLAD!");
    }
    glViewport(0, 0, Common::Instance().GetWindowWidth(), Common::Instance().GetWindowHeight());

    // Enable the depth buffer
	glEnable(GL_DEPTH_TEST);

    /***************************************** OBJECT MODEL *****************************************/

    glm::vec3 objectPosition = glm::vec3(0.0f, -0.25f, -2.5f);
    float objectRadian = 0.0f;
    glm::quat objectRotation = glm::angleAxis(objectRadian, glm::vec3(0.0f, 1.0f, 0.0f));
    float objectScalar = 1.0f;

    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel = glm::translate(objectModel, objectPosition);
	objectModel = objectModel * glm::mat4_cast(objectRotation);
    objectModel = glm::scale(objectModel, glm::vec3(objectScalar));

    VAO objectVAO = VAO();
    objectVAO.Bind();
    EBO objectEBO = EBO(objectIndices);

#if OBJECT_VERTEX_TYPE == TEXTURE_VERTEX
    VBO objectVBO = VBO(objectTextureVertices, GL_STATIC_DRAW);
    objectVAO.LinkAttrib(objectVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)0);                         // position
    objectVAO.LinkAttrib(objectVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)(sizeof(glm::vec3)));       // normal
    objectVAO.LinkAttrib(objectVBO, 2, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)(2 * sizeof(glm::vec3)));   // texture
#else
    VBO objectVBO = VBO(objectColorVertices);
    objectVAO.LinkAttrib(objectVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);                           // position
    objectVAO.LinkAttrib(objectVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)(sizeof(glm::vec3)));         // normal
    objectVAO.LinkAttrib(objectVBO, 2, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)(2 * sizeof(glm::vec3)));     // color
#endif

    objectVAO.Unbind();
    objectVBO.Unbind();
    objectEBO.Unbind();

    Texture2D objectTexture = Texture2D((Common::Instance().GetTexturesPath() + "brick.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    
#if OBJECT_VERTEX_TYPE == TEXTURE_VERTEX
    Shader objectShader = Shader(
        (Common::Instance().GetGLSLPath() + "texture_vertex.glsl").c_str(), 
        (Common::Instance().GetGLSLPath() + "texture_fragment.glsl").c_str()
    );
#else
    Shader objectShader = Shader(
        (Common::Instance().GetGLSLPath() + "color_vertex.glsl").c_str(), 
        (Common::Instance().GetGLSLPath() + "color_fragment.glsl").c_str()
    );
#endif

    objectShader.Use();
    objectShader.SetUniformInt(0, "textureImage");

    /***************************************** LIGHT MODEL *****************************************/

    glm::vec3 lightPosition = glm::vec3(1.0f, 0.25f, -2.0f);
    float lightRadian = 0.0f;
    glm::quat lightRotation = glm::angleAxis(lightRadian, glm::vec3(0.0f, 1.0f, 0.0f));
    float lightScalar = 1.0f;

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPosition);
	lightModel = lightModel * glm::mat4_cast(lightRotation);
    lightModel = glm::scale(lightModel, glm::vec3(lightScalar));
    
    PointLight lightSource = PointLight(lightPosition, glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 0.2f);

    VAO lightVAO = VAO();
    lightVAO.Bind();
    EBO lightEBO = EBO(lightIndices);
    VBO lightVBO = VBO(lightVertices, GL_STATIC_DRAW);

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), (void*)0); // position

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    Shader lightShader = Shader(
        (Common::Instance().GetGLSLPath() + "basic_vertex.glsl").c_str(), 
        (Common::Instance().GetGLSLPath() + "basic_fragment.glsl").c_str()
    );

    lightShader.Use();
    lightShader.SetUniformVec3(lightSource.GetColor(), "color");

    /*********************************************************************************/

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

        objectShader.Use();
        glm::mat4 objectTransform = Camera::Instance().GetPerspective() * Camera::Instance().GetView() * objectModel;
        objectShader.SetUniformMat4(objectTransform, "transform");
        objectTexture.Bind(0);
        objectVAO.Bind();
        glDrawElements(GL_TRIANGLES, objectIndices.size(), GL_UNSIGNED_INT, (void*)0);
        objectTexture.Unbind();
        objectVAO.Unbind();

        lightShader.Use();
        glm::mat4 lightTransform = Camera::Instance().GetPerspective() * Camera::Instance().GetView() * lightModel;
        lightShader.SetUniformMat4(lightTransform, "transform");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, lightIndices.size(), GL_UNSIGNED_INT, (void*)0);
        lightVAO.Unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    objectVAO.Delete();
    objectVBO.Delete();
    objectEBO.Delete();
    objectTexture.Delete();
    objectShader.Delete();

    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    lightShader.Delete();

    glfwTerminate();
    return 0;
}
