
#include <iostream>
#include "input_handler.h"
#include "scene.h"
#include "model.h"

#include "loadable_color_model.h"
#include "loadable_texture_model.h"

#include "point_light.h"
#include "directional_light.h"
#include "spot_light.h"

using namespace skate;

int main(int argc, char **argv)
{
    //-------------------------------------- INITIALIZATION --------------------------------------//

    if (glfwInit() == GLFW_FALSE)
        throw Exception("Failed to initialize GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#ifdef __FULL_SCREEN__
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    if (!monitor)
        throw Exception("Failed to Find the Primary Monitor!");

    const GLFWvidmode *videoMode = glfwGetVideoMode(monitor);
    if (!videoMode)
        throw Exception("Failed to Get the Video Mode of the Monitor!");

    GLFWwindow *window = glfwCreateWindow(videoMode->width, videoMode->height, "skate", monitor, NULL);
#else
    GLFWwindow *window = glfwCreateWindow(util::windowWidth, util::windowHeight, "skate", NULL, NULL);
#endif

    if (window == NULL)
    {
        glfwTerminate();
        throw Exception("Failed to create GLFW Window!");
    }
    glfwMakeContextCurrent(window);

    Camera::Instance().Initialize();
    InputHandler::Instance().Initialize(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw Exception("Failed to initialize GLAD!");
    }

#ifdef __FULL_SCREEN__
    glViewport(0, 0, videoMode->width, videoMode->height);
#else
    glViewport(0, 0, util::windowWidth, util::windowHeight);
#endif

    // Enable the depth buffer and face culling
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //-------------------------------- TEXTURES, LIGHTS, AND SHADERS -------------------------------//

    Texture::InitializeCommonTextures();

    const Texture brickTexture(
        util::texturesDir + "common/brick.png", 
        GL_REPEAT, GL_REPEAT, 
        GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST
    );
    const Texture woodContainerDiffuseMap(
        util::texturesDir + "container/albedo.png", 
        GL_REPEAT, GL_REPEAT, 
        GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST
    );
    const Texture woodContainerSpecularMap(
        util::texturesDir + "container/metallic.png", 
        GL_REPEAT, GL_REPEAT, 
        GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST
    );

    const DirectionalLight directionalLight(glm::vec3(0.0f, -0.8f, -0.6f));
    const PointLight pointLight(glm::vec3(0.0f, 2.0f, 0.0f));
    const SpotLight spotLight(glm::vec3(2.5f, 5.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));

    const std::vector<LightCaster*> lightCasters = 
    {
        (LightCaster*)&directionalLight,
        (LightCaster*)&pointLight,
        (LightCaster*)&spotLight,
    };

    const Shader colorShader(util::COLOR_VERTEX);
    const Shader materialShader(util::MATERIAL_VERTEX);
    const Shader textureShader(util::TEXTURE_VERTEX);

    // We are assuming that the light sources are constant 
    colorShader.UpdateLightCasters(lightCasters);
    materialShader.UpdateLightCasters(lightCasters);
    textureShader.UpdateLightCasters(lightCasters);

    const std::vector<Shader> shaders = { colorShader, materialShader, textureShader };

    //-------------------------------------- CONTAINER MODEL --------------------------------------//

    const std::vector<TextureMesh> containerMeshes = 
    {
        TextureMesh(
            containerTextureVertices, 
            containerIndices, 
            woodContainerDiffuseMap, 
            woodContainerSpecularMap, 
            Texture::black,
            16.0f, 
            GL_STATIC_DRAW
        ),
    };

    const glm::vec3 containerPosition = glm::vec3(2.5f, 0.0f, 0.0f);
    const Model container(containerMeshes, containerPosition);

    //----------------------------------- COLOR PYRAMID MODEL -----------------------------------//

    const std::vector<ColorMesh> colorPyramidMeshes = 
    {
        ColorMesh(pyramidColorVertices, pyramidIndices, GL_STATIC_DRAW),
    };

    const glm::vec3 colorPyramidPosition = glm::vec3(0.0f, 0.0f, -2.5f);
    const Model colorPyramid(colorPyramidMeshes, colorPyramidPosition);

    //---------------------------------- MATERIAL PYRAMID MODEL ---------------------------------//

    const std::vector<MaterialMesh> materialPyramidMeshes = 
    {
        MaterialMesh(pyramidMaterialVertices, pyramidIndices, material::bronze, GL_STATIC_DRAW),
    };

    const glm::vec3 materialPyramidPosition = glm::vec3(-2.5f, 0.0f, 0.0f);
    const Model materialPyramid(materialPyramidMeshes, materialPyramidPosition);

    //---------------------------------- TEXTURE PYRAMID MODEL ---------------------------------//

    const std::vector<TextureMesh> texturePyramidMeshes = 
    {
        TextureMesh(
            pyramidTextureVertices, 
            pyramidIndices, 
            brickTexture, 
            Texture::white,
            Texture::black, 
            16.0f, 
            GL_STATIC_DRAW
        ),
    };

    const glm::vec3 texturePyramidPosition = glm::vec3(0.0f, 0.0f, 2.5f);
    const Model texturePyramid(texturePyramidMeshes, texturePyramidPosition);

    //------------------------------------- OBJECT MODEL ------------------------------------//

    const glm::vec3 objectPosition = glm::vec3(20.0f, 0.0f, -20.0f);
    const glm::quat objectRotation = glm::angleAxis(-M_PIf/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::vec3 objectScalar = glm::vec3(0.1f, 0.1f, 0.1f);
    const LoadableColorModel object(util::modelsDir + "medieval_village/scene.gltf", objectPosition, objectRotation, objectScalar);

    //-------------------------------------- WHILE LOOP --------------------------------------//

    float currentTime;
    float lastFrameTime = glfwGetTime();
    float elapsedTimeSinceLastFrame;

#ifdef __FPS__
    float fpsDeltaTime = 0.0f;
    uint32_t frameCount = 0;
    glfwSwapInterval(0);
#endif

    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        elapsedTimeSinceLastFrame = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

#ifdef __FPS__
        frameCount++;
        fpsDeltaTime += elapsedTimeSinceLastFrame;
        if (fpsDeltaTime > 1.0f)
        {
            std::cout << "FPS: " << frameCount << std::endl;
            frameCount = 0;
            fpsDeltaTime = 0.0f;
        }
#endif

        Camera::Instance().UpdatePosition(elapsedTimeSinceLastFrame);
        const glm::mat4 projectionView = Camera::Instance().GetProjection() * Camera::Instance().GetView();
        const glm::vec3 &cameraPosition = Camera::Instance().GetPosition();

        glClearColor(util::backgroundColor.r, util::backgroundColor.g, util::backgroundColor.b, util::backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update shaders
        for (uint32_t i = 0; i < shaders.size(); i++) 
            shaders[i].UpdateView(projectionView, cameraPosition);

        container.Draw(textureShader);
        colorPyramid.Draw(colorShader);
        materialPyramid.Draw(materialShader);
        texturePyramid.Draw(textureShader);
        object.Draw(colorShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    container.Delete();
    colorPyramid.Delete();
    materialPyramid.Delete();
    texturePyramid.Delete();
    object.Delete();

    textureShader.Delete();
    colorShader.Delete();
    materialShader.Delete();

    Texture::DeleteCommonTextures();
    brickTexture.Delete();
    woodContainerDiffuseMap.Delete();
    woodContainerSpecularMap.Delete();

    glfwTerminate();
    return 0;
}
