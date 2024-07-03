
#include <iostream>
#include "input_handler.h"
#include "scene.h"
#include "model.h"

int main(int argc, char **argv) {
    //-------------------------------------- INITIALIZATION --------------------------------------//

    if (glfwInit() == GLFW_FALSE) {
        throw Exception("Failed to initialize GLFW!");
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
        throw Exception("Failed to Get the Video Mode of the Monitor!");
    }

    GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "Learn OpenGL", monitor, NULL); 
#else
    GLFWwindow* window = glfwCreateWindow(Common::Instance().GetWindowWidth(), Common::Instance().GetWindowHeight(), "Learn OpenGL", NULL, NULL); 
#endif

    if (window == NULL) {
        glfwTerminate();
        throw Exception("Failed to create GLFW Window!");
    }
    glfwMakeContextCurrent(window);

    Camera::Instance().Initialize();
    InputHandler::Instance().Initialize(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw Exception("Failed to initialize GLAD!");
    }

#ifdef __FULL_SCREEN__
    glViewport(0, 0, videoMode->width, videoMode->height);
#else
    glViewport(0, 0, Common::Instance().GetWindowWidth(), Common::Instance().GetWindowHeight());
#endif

    // Enable the depth buffer
	glEnable(GL_DEPTH_TEST);

    const Texture2D brickTexture = Texture2D((Common::Instance().GetTexturesPath() + "brick.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    const Texture2D blackTexture = Texture2D((Common::Instance().GetTexturesPath() + "black.jpg").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);
    const Texture2D woodContainerDiffuseMap = Texture2D((Common::Instance().GetTexturesPath() + "wood_container2.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    const Texture2D woodContainerSpecularMap = Texture2D((Common::Instance().GetTexturesPath() + "wood_container2_specular.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    const Texture2D matrixEmissionMap = Texture2D((Common::Instance().GetTexturesPath() + "matrix.jpg").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);    

    //-------------------------------------- CONTAINER MODEL --------------------------------------//

    const std::vector<TextureMesh> containerMeshes = {
        TextureMesh(containerTextureVertices, containerIndices, woodContainerDiffuseMap, woodContainerSpecularMap, matrixEmissionMap, 16.0f, GL_STATIC_DRAW),
    };

    const glm::vec3 containerPosition = glm::vec3(-2.0f, 0.0f, -2.5f);
    const glm::quat containerRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::vec3 containerScalar = glm::vec3(1.0f, 1.0f, 1.0f);

    const Model container = Model(containerMeshes, containerPosition, containerRotation, containerScalar); 

    //----------------------------------- COLOR PYRAMID MODEL -----------------------------------//

    const std::vector<ColorMesh> colorPyramidMeshes = {
        ColorMesh(pyramidColorVertices, pyramidIndices, GL_STATIC_DRAW),
    };

    const glm::vec3 colorPyramidPosition = glm::vec3(0.0f, 0.0f, -2.5f);
    const glm::quat colorPyramidRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::vec3 colorPyramidScalar = glm::vec3(1.0f, 1.0f, 1.0f);

    const Model colorPyramid = Model(colorPyramidMeshes, colorPyramidPosition, colorPyramidRotation, colorPyramidScalar);

    //---------------------------------- MATERIAL PYRAMID MODEL ---------------------------------//

    const std::vector<MaterialMesh> materialPyramidMeshes = {
        MaterialMesh(pyramidMaterialVertices, pyramidIndices, material::bronze, GL_STATIC_DRAW),
    };

    const glm::vec3 materialPyramidPosition = glm::vec3(2.0f, 0.0f, -2.5f);
    const glm::quat materialPyramidRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::vec3 materialPyramidScalar = glm::vec3(1.0f, 1.0f, 1.0f);

    const Model materialPyramid = Model(materialPyramidMeshes, materialPyramidPosition, materialPyramidRotation, materialPyramidScalar);

    //---------------------------------- TEXTURE PYRAMID MODEL ---------------------------------//

    const std::vector<TextureMesh> texturePyramidMeshes = {
        TextureMesh(pyramidTextureVertices, pyramidIndices, brickTexture, brickTexture, blackTexture, 16.0f, GL_STATIC_DRAW),
    };

    const glm::vec3 texturePyramidPosition = glm::vec3(4.0f, 0.0f, -2.5f);
    const glm::quat texturePyramidRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::vec3 texturePyramidScalar = glm::vec3(1.0f, 1.0f, 1.0f);

    const Model texturePyramid = Model(texturePyramidMeshes, texturePyramidPosition, texturePyramidRotation, texturePyramidScalar);

    //--------------------------------------- SHADERS -----------------------------------------//

    const Shader textureShader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, TEXTURE_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, TEXTURE_VERTEX).c_str()
    );

    const Shader colorShader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, COLOR_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, COLOR_VERTEX).c_str()
    );
    const Shader materialShader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, MATERIAL_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, MATERIAL_VERTEX).c_str()
    );

    //-------------------------------------- WHILE LOOP --------------------------------------//

    float currentTime;
    float lastFrameTime = glfwGetTime();
    float elapsedTimeSinceLastFrame;

#ifdef __FPS__
    float fpsDeltaTime = 0.0f;
    uint32_t frameCount = 0;
	glfwSwapInterval(0);
#endif

    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        elapsedTimeSinceLastFrame = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

    #ifdef __FPS__
        frameCount++;
        fpsDeltaTime += elapsedTimeSinceLastFrame;
        if (fpsDeltaTime > 1.0f) {
            std::cout << "FPS: " << frameCount / fpsDeltaTime << std::endl;
            frameCount = 0;
            fpsDeltaTime = 0.0f;
        }
    #endif 
        
        Camera::Instance().UpdatePosition(elapsedTimeSinceLastFrame);
        const glm::mat4 projectionView = Camera::Instance().GetProjection() * Camera::Instance().GetView();
        const glm::vec3& cameraPosition = Camera::Instance().GetPosition();
        const Light light = Camera::Instance().GetFlashLight().GetLight();

        const glm::vec4& backgroundColor = Common::Instance().GetBackgroundColor();
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        container.Draw(textureShader, projectionView, cameraPosition, light);
        colorPyramid.Draw(colorShader, projectionView, cameraPosition, light);
        materialPyramid.Draw(materialShader, projectionView, cameraPosition, light);
        texturePyramid.Draw(textureShader, projectionView, cameraPosition, light);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    container.Delete();
    colorPyramid.Delete();
    materialPyramid.Delete();
    texturePyramid.Delete();

    textureShader.Delete();
    colorShader.Delete();
    materialShader.Delete();

    brickTexture.Delete();
    blackTexture.Delete();
    woodContainerDiffuseMap.Delete();
    woodContainerSpecularMap.Delete();
    matrixEmissionMap.Delete();

    glfwTerminate();
    return 0;
}
