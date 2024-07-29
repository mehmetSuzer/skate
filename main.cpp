
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

    Camera camera(glm::vec3(0.0f));
    InputHandler::Instance().Initialize(window);
    InputHandler::Instance().SelectCamera(&camera);

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

    // Global OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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

    DirectionalLight directionalLight = DirectionalLight(glm::vec3(0.0f, -0.8f, -0.6f));
    PointLight pointLight = PointLight(glm::vec3(0.0f, 2.0f, 0.0f));
    SpotLight spotLight = SpotLight(glm::vec3(2.5f, 5.0f, 0.0f), Transform::WorldDown);

    const std::vector<LightCaster*> lightCasters = 
    {
        (LightCaster*)&directionalLight,
        // (LightCaster*)&pointLight,
        // (LightCaster*)&spotLight,
    };

    const Shader colorShader(util::COLOR_SHADER);
    const Shader materialShader(util::MATERIAL_SHADER);
    const Shader textureShader(util::TEXTURE_SHADER);

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
    Model container(containerMeshes, glm::vec3(2.5f, 0.0f, 0.0f));

    //----------------------------------- COLOR PYRAMID MODEL -----------------------------------//

    const std::vector<ColorMesh> colorPyramidMeshes = 
    {
        ColorMesh(pyramidColorVertices, pyramidIndices, 1.0f, 0.0f, GL_STATIC_DRAW),
    };
    const Model colorPyramid(colorPyramidMeshes, glm::vec3(0.0f, 0.0f, -2.5f));

    //---------------------------------- MATERIAL PYRAMID MODEL ---------------------------------//

    const std::vector<MaterialMesh> materialPyramidMeshes = 
    {
        MaterialMesh(pyramidMaterialVertices, pyramidIndices, material::bronze, GL_STATIC_DRAW),
    };
    const Model materialPyramid(materialPyramidMeshes, glm::vec3(-2.5f, 0.0f, 0.0f));

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
    Model texturePyramid(texturePyramidMeshes, glm::vec3(0.0f, 0.0f, 2.5f));

    //------------------------------------- OBJECT MODEL ------------------------------------//

    const glm::vec3 objectPosition = glm::vec3(20.0f, 0.0f, -20.0f);
    const glm::quat objectRotation = glm::angleAxis(-M_PIf/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    LoadableColorModel object(util::modelsDir + "medieval_village/scene.gltf", objectPosition, objectRotation, 0.1f);
    object.Select();

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

        camera.UpdatePosition(elapsedTimeSinceLastFrame);
        const glm::mat4 projectionView = camera.GetProjection() * camera.GetView();
        const glm::vec3& cameraPosition = camera.transform.GetPosition();

        colorShader.UpdateLightCasters(lightCasters);
        materialShader.UpdateLightCasters(lightCasters);
        textureShader.UpdateLightCasters(lightCasters);

        // Update shaders
        for (uint32_t i = 0; i < shaders.size(); i++) 
            shaders[i].UpdateView(projectionView, cameraPosition);

        glStencilMask(0xFF);
        glClearColor(util::backgroundColor.r, util::backgroundColor.g, util::backgroundColor.b, util::backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Draw models
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glEnable(GL_DEPTH_TEST);

        for (uint32_t i = 0; i < shaders.size(); i++) 
        {
            shaders[i].Use();
            shaders[i].SetUniformBool(false, "drawBorder");
        }

        container.Draw(textureShader);
        object.Draw(colorShader);
        colorPyramid.Draw(colorShader);
        materialPyramid.Draw(materialShader);
        texturePyramid.Draw(textureShader);

        // Draw models' borders if they are selected
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        for (uint32_t i = 0; i < shaders.size(); i++) 
        {
            shaders[i].Use();
            shaders[i].SetUniformBool(true, "drawBorder");
        }

        container.DrawBorder(textureShader);
        object.DrawBorder(colorShader);
        colorPyramid.DrawBorder(colorShader);
        materialPyramid.DrawBorder(materialShader);
        texturePyramid.DrawBorder(textureShader);

        // texturePyramid.transform.Rotate(elapsedTimeSinceLastFrame, texturePyramid.transform.GetUp());
        // directionalLight.transform.Rotate(elapsedTimeSinceLastFrame, directionalLight.transform.GetRight());

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
