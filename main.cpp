
#include <material.h>
#include <input_handler.h>
#include <shader.h>
#include <texture2D.h>
#include <light.h>
#include <model.h>
#include <scene.h>

int main(int argc, char **argv) {
    //-------------------------------------- INITIALIZATION --------------------------------------//

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

    const Texture2D brickTexture = Texture2D((Common::Instance().GetTexturesPath() + "brick.png").c_str(), "diffuse", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    const Texture2D woodContainerDiffuseMap = Texture2D((Common::Instance().GetTexturesPath() + "wood_container2.png").c_str(), "diffuse", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    const Texture2D woodContainerSpecularMap = Texture2D((Common::Instance().GetTexturesPath() + "wood_container2_specular.png").c_str(), "specular", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    const Texture2D matrixEmissionMap = Texture2D((Common::Instance().GetTexturesPath() + "matrix.jpg").c_str(), "emission", GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);    

    const std::vector<Texture2D> containerTextures = 
    {
        woodContainerDiffuseMap,
        woodContainerSpecularMap,
        matrixEmissionMap,
    };

    const std::vector<Mesh> containerMeshes = {
        Mesh(containerTextureVertices, containerIndices, containerTextures, GL_STATIC_DRAW),
    };

    const glm::vec3 containerPosition = glm::vec3(2.0f, -0.0f, -2.5f);
    const glm::quat containerRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::vec3 containerScalar = glm::vec3(1.0f, 1.0f, 1.0f);

    const Model container = Model(containerMeshes, containerPosition, containerRotation, containerScalar);

    //-------------------------------------- PYRAMID MODEL --------------------------------------//

#if __PYRAMID_VERTEX_TYPE__ == __PNT_VERTEX__
    Shader pyramidShader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, TEXTURE_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, TEXTURE_VERTEX).c_str()
    );
#elif __PYRAMID_VERTEX_TYPE__ == __PNC_VERTEX__
    Shader pyramidShader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, COLOR_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, COLOR_VERTEX).c_str()
    );
#elif __PYRAMID_VERTEX_TYPE__ == __PN_VERTEX__
    const Material& pyramidMaterial = material::gold;
    Shader pyramidShader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, MATERIAL_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, MATERIAL_VERTEX).c_str()
    );
#else
#endif

#if __PYRAMID_VERTEX_TYPE__ == __PNT_VERTEX__
    pyramidShader.SetUniformInt(0, "textureImage");
#elif __PYRAMID_VERTEX_TYPE__ == __PN_VERTEX__
    pyramidShader.SetUniformVec3(pyramidMaterial.ambient, "material.ambient");
    pyramidShader.SetUniformVec3(pyramidMaterial.diffuse, "material.diffuse");
    pyramidShader.SetUniformVec3(pyramidMaterial.specular, "material.specular");
    pyramidShader.SetUniformFloat(pyramidMaterial.shininess, "material.shininess");
#else
#endif

    Shader shader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, LIGHTING_MAP_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, LIGHTING_MAP_VERTEX).c_str()
    );

    //-------------------------------------- WHILE LOOP --------------------------------------//

    float currentTime;
    float lastTime = glfwGetTime();
    float elapsedTimeSinceLastFrame;

    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        elapsedTimeSinceLastFrame = currentTime - lastTime;
        lastTime = currentTime;

        Camera::Instance().UpdatePosition(elapsedTimeSinceLastFrame);
        glm::mat4 projectionView = Camera::Instance().GetProjection() * Camera::Instance().GetView();
        const glm::vec3& cameraPosition = Camera::Instance().GetPosition();
        const Light light = Camera::Instance().GetFlashLight().GetLight();

        const glm::vec4& backgroundColor = Common::Instance().GetBackgroundColor();
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        container.Draw(shader, projectionView, cameraPosition, light);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    container.Delete();
    shader.Delete();

    glfwTerminate();
    return 0;
}
