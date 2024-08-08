
#include "input_handler.h"
#include "scene.h"
#include "model.h"

#include "loadable_color_model.h"
#include "loadable_texture_model.h"

#include "point_light.h"
#include "directional_light.h"
#include "spot_light.h"

using namespace skate;

int main()
{
    //-------------------------------------- INITIALIZATION --------------------------------------//

    assert(glfwInit());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#ifdef __FULL_SCREEN__
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    assert(monitor != NULL);
    const GLFWvidmode *videoMode = glfwGetVideoMode(monitor);
    assert(videoMode != NULL);
    GLFWwindow *window = glfwCreateWindow(videoMode->width, videoMode->height, "skate", monitor, NULL);
#else
    GLFWwindow *window = glfwCreateWindow(Camera::windowWidth, Camera::windowHeight, "skate", NULL, NULL);
#endif

    assert(window != NULL);
    glfwMakeContextCurrent(window);

    Camera camera(glm::vec3(0.0f));
    InputHandler::Instance().Initialize(window);
    InputHandler::Instance().SelectCamera(&camera);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

#ifdef __FULL_SCREEN__
    glViewport(0, 0, videoMode->width, videoMode->height);
#else
    glViewport(0, 0, Camera::windowWidth, Camera::windowHeight);
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
    const Texture brickTexture("data/textures/common/brick.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    const Texture woodContainerDiffuseMap("data/textures/container/albedo.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    const Texture woodContainerSpecularMap("data/textures/container/metallic.png", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);

    const glm::vec4 backgroundColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);
    DirectionalLight directionalLight(glm::vec3(0.0f, -0.8f, -0.6f));
    PointLight pointLight(glm::vec3(0.0f, 2.0f, 0.0f));
    SpotLight spotLight(glm::vec3(2.5f, 5.0f, 0.0f), Transform::WorldDown);

    const std::vector<LightCaster*> lightCasters = 
    {
        (LightCaster*)&directionalLight,
        // (LightCaster*)&pointLight,
        // (LightCaster*)&spotLight,
    };

    const Shader colorShader("vertex/color_shader.glsl", "fragment/color_shader.glsl");
    const Shader materialShader("vertex/material_shader.glsl", "fragment/material_shader.glsl");
    const Shader textureShader("vertex/texture_shader.glsl", "fragment/texture_shader.glsl");
    const Shader borderShader("vertex/border_shader.glsl", "fragment/border_shader.glsl");
    const std::vector<Shader> shaders = { colorShader, materialShader, textureShader, borderShader };

    //-------------------------------------- UNIFORM BUFFER --------------------------------------//

    // Generate a uniform buffer object
    GLuint uniformGlobal;
    glGenBuffers(1, &uniformGlobal);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformGlobal);
    glBufferData(GL_UNIFORM_BUFFER, 96 + 80*MAX_LIGHT_CASTER_NUMBER, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Bind the shaders to a binding points
    const GLuint uniformBlockBinding = 0;
    for (uint32_t i = 0; i < shaders.size(); i++)
    {
        GLuint uniformBlockIndex = glGetUniformBlockIndex(shaders[i].GetID(), "Global");
        glUniformBlockBinding(shaders[i].GetID(), uniformBlockIndex, uniformBlockBinding);
    }

    // Bind the uniform buffer object to the same binding point
    glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlockBinding, uniformGlobal);

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
    Model colorPyramid(colorPyramidMeshes, glm::vec3(0.0f, 0.0f, -2.5f));

    //---------------------------------- MATERIAL PYRAMID MODEL ---------------------------------//

    const std::vector<MaterialMesh> materialPyramidMeshes = 
    {
        MaterialMesh(pyramidMaterialVertices, pyramidIndices, material::cyanPlastic, GL_STATIC_DRAW),
    };
    Model materialPyramid(materialPyramidMeshes, glm::vec3(-2.5f, 0.0f, 0.0f));

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
    LoadableColorModel object("data/models/medieval_village/scene.gltf", objectPosition, objectRotation, 0.1f);
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

        int lightCasterNumber = (lightCasters.size() < MAX_LIGHT_CASTER_NUMBER) ? lightCasters.size() : MAX_LIGHT_CASTER_NUMBER;
        glBindBuffer(GL_UNIFORM_BUFFER, uniformGlobal);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, 4, &lightCasterNumber);
        glBufferSubData(GL_UNIFORM_BUFFER, 16, 12, glm::value_ptr(cameraPosition));
        glBufferSubData(GL_UNIFORM_BUFFER, 32, 64, glm::value_ptr(projectionView));

        for (uint32_t i = 0; i < lightCasterNumber; i++) 
        {
            const LightCaster::Light light = lightCasters[i]->GetLight();

            glBufferSubData(GL_UNIFORM_BUFFER, 96 + 80*i,        4, &(light.type));
            glBufferSubData(GL_UNIFORM_BUFFER, 96 + 80*i + 4,    4, &(light.intensity));
            glBufferSubData(GL_UNIFORM_BUFFER, 96 + 80*i + 8,    4, &(light.linear));
            glBufferSubData(GL_UNIFORM_BUFFER, 96 + 80*i + 12,   4, &(light.quadratic));
            glBufferSubData(GL_UNIFORM_BUFFER, 96 + 80*i + 16,   4, &(light.cosInnerCutOff));
            glBufferSubData(GL_UNIFORM_BUFFER, 96 + 80*i + 20,   4, &(light.cosOuterCutOff));
            glBufferSubData(GL_UNIFORM_BUFFER, 96 + 80*i + 32,  12, &(light.color));
            glBufferSubData(GL_UNIFORM_BUFFER, 96 + 80*i + 48,  12, &(light.position));
            glBufferSubData(GL_UNIFORM_BUFFER, 96 + 80*i + 64,  12, &(light.direction));
        }
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        glStencilMask(0xFF);
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Draw models
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glEnable(GL_DEPTH_TEST);

        container.Draw(textureShader);
        object.Draw(colorShader);
        colorPyramid.Draw(colorShader);
        materialPyramid.Draw(materialShader);
        texturePyramid.Draw(textureShader);

        // Draw models' borders if they are selected
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        container.DrawBorder(borderShader);
        object.DrawBorder(borderShader);
        colorPyramid.DrawBorder(borderShader);
        materialPyramid.DrawBorder(borderShader);
        texturePyramid.DrawBorder(borderShader);

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

    for (uint32_t i = 0; i < shaders.size(); i++)
        shaders[i].Delete();

    Texture::DeleteCommonTextures();
    brickTexture.Delete();
    woodContainerDiffuseMap.Delete();
    woodContainerSpecularMap.Delete();

    glfwTerminate();
    return 0;
}
