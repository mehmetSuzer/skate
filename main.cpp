
#include <material.h>
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

#ifdef __FULL_SCREEN__
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) {
        throw Error("Failed to Find the Primary Monitor!");
    }

    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
    if (!videoMode) {
        throw Error("Failed to Get the Video Mode of the Monitor!");
    }

    GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "Learn OpenGL", monitor, NULL); 
#else
    GLFWwindow* window = glfwCreateWindow(Common::Instance().GetWindowWidth(), Common::Instance().GetWindowHeight(), "Learn OpenGL", NULL, NULL); 
#endif

    if (window == NULL) {
        glfwTerminate();
        throw Error("Failed to create GLFW Window!");
    }
    glfwMakeContextCurrent(window);

    Camera::Instance().Initialize();
    InputHandler::Instance().Initialize(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw Error("Failed to initialize GLAD!");
    }

#ifdef __FULL_SCREEN__
    glViewport(0, 0, videoMode->width, videoMode->height);
#else
    glViewport(0, 0, Common::Instance().GetWindowWidth(), Common::Instance().GetWindowHeight());
#endif

    // Enable the depth buffer
	glEnable(GL_DEPTH_TEST);

    /***************************************** LIGHT MODEL *****************************************/

    glm::vec3 lightPosition = glm::vec3(1.0f, 0.25f, -2.0f);
    float lightRadian = 0.0f;
    glm::quat lightRotation = glm::angleAxis(lightRadian, glm::vec3(0.0f, 1.0f, 0.0f));
    float lightScalar = 1.0f;

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPosition);
	lightModel = lightModel * glm::mat4_cast(lightRotation);
    lightModel = glm::scale(lightModel, glm::vec3(lightScalar));
    
    PointLight lightSource = PointLight(lightPosition, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.2f, 0.2f);

    VAO lightVAO = VAO();
    lightVAO.Bind();
    EBO lightEBO = EBO(lightIndices);
    VBO lightVBO = VBO(lightVertices, GL_STATIC_DRAW);

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), (void*)0); // position

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    Shader lightShader = Shader(
        Common::Instance().GetShaderProgramPath(FLAT_SHADING, VERTEX_SHADER, BASIC_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(FLAT_SHADING, FRAGMENT_SHADER, BASIC_VERTEX).c_str()
    );

    lightShader.Use();
    lightShader.SetUniformMat4(lightModel, "model");
    lightShader.SetUniformVec4(lightSource.GetColor(), "color");

    /***************************************** OBJECT MODEL *****************************************/

    glm::vec3 objectPosition = glm::vec3(0.0f, -0.25f, -2.5f);
    float objectRadian = 0.0f;
    glm::quat objectRotation = glm::angleAxis(objectRadian, glm::vec3(0.0f, 1.0f, 0.0f));
    float objectScalarX = 1.0f;
    float objectScalarY = 1.0f;
    float objectScalarZ = 1.0f;

    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel = glm::translate(objectModel, objectPosition);
	objectModel = objectModel * glm::mat4_cast(objectRotation);
    objectModel = glm::scale(objectModel, glm::vec3(objectScalarX, objectScalarY, objectScalarZ));
    glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(objectModel)));

    VAO objectVAO = VAO();
    objectVAO.Bind();
    EBO objectEBO = EBO(objectIndices);

#if __OBJECT_VERTEX_TYPE__ == __TEXTURE_VERTEX__
    VBO objectVBO = VBO(objectTextureVertices, GL_STATIC_DRAW);
    objectVAO.LinkAttrib(objectVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)0);                         // position
    objectVAO.LinkAttrib(objectVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)(sizeof(glm::vec3)));       // normal
    objectVAO.LinkAttrib(objectVBO, 2, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)(2 * sizeof(glm::vec3)));   // texture
#elif __OBJECT_VERTEX_TYPE__ == __COLOR_VERTEX__
    VBO objectVBO = VBO(objectColorVertices, GL_STATIC_DRAW);
    objectVAO.LinkAttrib(objectVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);                           // position
    objectVAO.LinkAttrib(objectVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)(sizeof(glm::vec3)));         // normal
    objectVAO.LinkAttrib(objectVBO, 2, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)(2 * sizeof(glm::vec3)));     // color
#elif __OBJECT_VERTEX_TYPE__ == __NORMAL_VERTEX__ || __OBJECT_VERTEX_TYPE__ == __MATERIAL_VERTEX__
    VBO objectVBO = VBO(objectNormalVertices, GL_STATIC_DRAW);
    objectVAO.LinkAttrib(objectVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(NormalVertex), (void*)0);                          // position
    objectVAO.LinkAttrib(objectVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(NormalVertex), (void*)(sizeof(glm::vec3)));        // normal
#else
#endif

    objectVAO.Unbind();
    objectVBO.Unbind();
    objectEBO.Unbind();

    Texture2D objectTexture = Texture2D((Common::Instance().GetTexturesPath() + "brick.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    
#if __OBJECT_VERTEX_TYPE__ == __TEXTURE_VERTEX__
    Shader objectShader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, TEXTURE_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, TEXTURE_VERTEX).c_str()
    );
#elif __OBJECT_VERTEX_TYPE__ == __COLOR_VERTEX__
    Shader objectShader = Shader(
        Common::Instance().GetShaderProgramPath(GOURAUD_SHADING, VERTEX_SHADER, COLOR_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(GOURAUD_SHADING, FRAGMENT_SHADER, COLOR_VERTEX).c_str()
    );
#elif __OBJECT_VERTEX_TYPE__ == __NORMAL_VERTEX__
    glm::vec4 objectColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    Shader objectShader = Shader(
        Common::Instance().GetShaderProgramPath(GOURAUD_SHADING, VERTEX_SHADER, NORMAL_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(GOURAUD_SHADING, FRAGMENT_SHADER, NORMAL_VERTEX).c_str()
    );
#elif __OBJECT_VERTEX_TYPE__ == __MATERIAL_VERTEX__
    const Material& objectMaterial = material::cyanPlastic;
    Shader objectShader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, MATERIAL_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, MATERIAL_VERTEX).c_str()
    );
#else
#endif

    objectShader.Use();
    objectShader.SetUniformMat3(normalMatrix, "normalMatrix");
    objectShader.SetUniformMat4(objectModel, "model");
    objectShader.SetUniformVec4(lightSource.GetColor(), "light.color");
    objectShader.SetUniformVec3(lightSource.GetPosition(), "light.position");

#if __OBJECT_VERTEX_TYPE__ == __TEXTURE_VERTEX__
    objectShader.SetUniformInt(0, "textureImage");
#elif __OBJECT_VERTEX_TYPE__ == __NORMAL_VERTEX__
    objectShader.SetUniformVec4(objectColor, "color");
#elif __OBJECT_VERTEX_TYPE__ == __MATERIAL_VERTEX__
    objectShader.SetUniformVec3(objectMaterial.ambient, "material.ambient");
    objectShader.SetUniformVec3(objectMaterial.diffuse, "material.diffuse");
    objectShader.SetUniformVec3(objectMaterial.specular, "material.specular");
    objectShader.SetUniformFloat(objectMaterial.shininess, "material.shininess");
#else
#endif

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
        glm::mat4 projectionView = Camera::Instance().GetProjection() * Camera::Instance().GetView();
        objectShader.SetUniformMat4(projectionView, "projectionView");
        objectShader.SetUniformVec3(Camera::Instance().GetPosition(), "cameraPosition");
        objectTexture.Bind(0);
        objectVAO.Bind();
        glDrawElements(GL_TRIANGLES, objectIndices.size(), GL_UNSIGNED_INT, (void*)0);
        objectTexture.Unbind();
        objectVAO.Unbind();

        lightShader.Use();
        lightShader.SetUniformMat4(projectionView, "projectionView");
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
