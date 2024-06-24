
#include <material.h>
#include <ebo.h>
#include <vao.h>
#include <scene.h>
#include <input_handler.h>
#include <shader.h>
#include <texture2D.h>
#include <light.h>

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

    //-------------------------------------- LIGHT MODEL --------------------------------------//

    glm::vec3 lightPosition = glm::vec3(1.0f, 0.25f, -2.0f);
    float lightRadian = 0.0f;
    glm::quat lightRotation = glm::angleAxis(lightRadian, glm::vec3(0.0f, 1.0f, 0.0f));
    float lightScalar = 1.0f;

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPosition);
	lightModel = lightModel * glm::mat4_cast(lightRotation);
    lightModel = glm::scale(lightModel, glm::vec3(lightScalar));
    
    // DirectionalLight lightSource = DirectionalLight(glm::vec3(0.0f, 0.0f, -1.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    PointLight lightSource = PointLight(lightPosition, 0.09f, 0.32f, glm::vec3(1.0f, 1.0f, 1.0f));
    // SpotLight lightSource = SpotLight(lightPosition, 0.09f, 0.32f, glm::vec3(1.0f, 0.0f, 0.0f), M_PIf/12.0f, M_PIf/6.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    const Light light = lightSource.GetLight();

    VAO lightVAO = VAO();
    lightVAO.Bind();
    EBO lightEBO = EBO(lightIndices);
    VBO lightVBO = VBO(lightVertices, GL_STATIC_DRAW);

    lightVAO.LinkAttribute(lightVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(PVertex), (void*)0); // position

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    Shader lightShader = Shader(
        Common::Instance().GetShaderProgramPath(FLAT_SHADING, VERTEX_SHADER, BASIC_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(FLAT_SHADING, FRAGMENT_SHADER, BASIC_VERTEX).c_str()
    );

    lightShader.Use();
    lightShader.SetUniformMat4(lightModel, "model");
    lightShader.SetUniformVec3(lightSource.GetColor(), "color");

    //-------------------------------------- PYRAMID MODEL --------------------------------------//

    glm::vec3 pyramidPosition = glm::vec3(0.0f, -0.0f, -2.5f);
    float pyramidRadian = 0.0f;
    glm::quat pyramidRotation = glm::angleAxis(pyramidRadian, glm::vec3(0.0f, 1.0f, 0.0f));
    float pyramidScalarX = 1.0f;
    float pyramidScalarY = 1.0f;
    float pyramidScalarZ = 1.0f;

    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPosition);
	pyramidModel = pyramidModel * glm::mat4_cast(pyramidRotation);
    pyramidModel = glm::scale(pyramidModel, glm::vec3(pyramidScalarX, pyramidScalarY, pyramidScalarZ));
    glm::mat3 pyramidNormalMatrix = glm::mat3(glm::transpose(glm::inverse(pyramidModel)));

    VAO pyramidVAO = VAO();
    pyramidVAO.Bind();
    EBO pyramidEBO = EBO(pyramidIndices);

#if __PYRAMID_VERTEX_TYPE__ == __PNT_VERTEX__
    VBO pyramidVBO = VBO(pyramidTextureVertices, GL_STATIC_DRAW);
    pyramidVAO.LinkAttribute(pyramidVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(PNTVertex), (void*)0);                         // position
    pyramidVAO.LinkAttribute(pyramidVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(PNTVertex), (void*)(sizeof(glm::vec3)));       // normal
    pyramidVAO.LinkAttribute(pyramidVBO, 2, 2, GL_FLOAT, GL_FALSE, sizeof(PNTVertex), (void*)(2 * sizeof(glm::vec3)));   // texture
#elif __PYRAMID_VERTEX_TYPE__ == __PNC_VERTEX__
    VBO pyramidVBO = VBO(pyramidColorVertices, GL_STATIC_DRAW);
    pyramidVAO.LinkAttribute(pyramidVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(PNCVertex), (void*)0);                         // position
    pyramidVAO.LinkAttribute(pyramidVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(PNCVertex), (void*)(sizeof(glm::vec3)));       // normal
    pyramidVAO.LinkAttribute(pyramidVBO, 2, 4, GL_FLOAT, GL_FALSE, sizeof(PNCVertex), (void*)(2 * sizeof(glm::vec3)));   // color
#elif __PYRAMID_VERTEX_TYPE__ == __PN_VERTEX__
    VBO pyramidVBO = VBO(pyramidNormalVertices, GL_STATIC_DRAW);
    pyramidVAO.LinkAttribute(pyramidVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(PNVertex), (void*)0);                          // position
    pyramidVAO.LinkAttribute(pyramidVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(PNVertex), (void*)(sizeof(glm::vec3)));        // normal
#else
#endif

    pyramidVAO.Unbind();
    pyramidVBO.Unbind();
    pyramidEBO.Unbind();

    Texture2D pyramidTexture = Texture2D((Common::Instance().GetTexturesPath() + "brick.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    
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

    pyramidShader.Use();
    pyramidShader.SetUniformMat3(pyramidNormalMatrix, "normalMatrix");
    pyramidShader.SetUniformMat4(pyramidModel, "model");

    pyramidShader.SetUniformInt(light.type, "light.type");
    pyramidShader.SetUniformVec3(light.color, "light.color");
    pyramidShader.SetUniformVec3(light.position, "light.position");
    pyramidShader.SetUniformVec3(light.direction, "light.direction");
    pyramidShader.SetUniformFloat(light.intensity, "light.intensity");
    pyramidShader.SetUniformFloat(light.linear, "light.linear");
    pyramidShader.SetUniformFloat(light.quadratic, "light.quadratic");
    pyramidShader.SetUniformFloat(light.cosInnerCutOff, "light.cosInnerCutOff");
    pyramidShader.SetUniformFloat(light.cosOuterCutOff, "light.cosOuterCutOff");

#if __PYRAMID_VERTEX_TYPE__ == __PNT_VERTEX__
    pyramidShader.SetUniformInt(0, "textureImage");
#elif __PYRAMID_VERTEX_TYPE__ == __PN_VERTEX__
    pyramidShader.SetUniformVec3(pyramidMaterial.ambient, "material.ambient");
    pyramidShader.SetUniformVec3(pyramidMaterial.diffuse, "material.diffuse");
    pyramidShader.SetUniformVec3(pyramidMaterial.specular, "material.specular");
    pyramidShader.SetUniformFloat(pyramidMaterial.shininess, "material.shininess");
#else
#endif

    //-------------------------------------- CONTAINER MODEL --------------------------------------//

    glm::vec3 containerPosition = glm::vec3(2.0f, -0.0f, -2.5f);
    float containerRadian = 0.0f;
    glm::quat containerRotation = glm::angleAxis(containerRadian, glm::vec3(0.0f, 1.0f, 0.0f));
    float containerScalar = 1.0f;

    glm::mat4 containerModel = glm::mat4(1.0f);
    containerModel = glm::translate(containerModel, containerPosition);
	containerModel = containerModel * glm::mat4_cast(containerRotation);
    containerModel = glm::scale(containerModel, glm::vec3(containerScalar));
    glm::mat3 containerNormalMatrix = glm::mat3(glm::transpose(glm::inverse(containerModel)));

    VAO containerVAO = VAO();
    containerVAO.Bind();
    EBO containerEBO = EBO(containerIndices);

    VBO containerVBO = VBO(containerTextureVertices, GL_STATIC_DRAW);
    containerVAO.LinkAttribute(containerVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(PNTVertex), (void*)0);                         // position
    containerVAO.LinkAttribute(containerVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(PNTVertex), (void*)(sizeof(glm::vec3)));       // normal
    containerVAO.LinkAttribute(containerVBO, 2, 2, GL_FLOAT, GL_FALSE, sizeof(PNTVertex), (void*)(2 * sizeof(glm::vec3)));   // texture

    containerVAO.Unbind();
    containerVBO.Unbind();
    containerEBO.Unbind();

    Texture2D containerDiffuseMap = Texture2D((Common::Instance().GetTexturesPath() + "wood_container2.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    Texture2D containerSpecularMap = Texture2D((Common::Instance().GetTexturesPath() + "wood_container2_specular.png").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);
    Texture2D containerEmissionMap = Texture2D((Common::Instance().GetTexturesPath() + "matrix.jpg").c_str(), GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);    
    float containerShininess = 16.0f;

    Shader containerShader = Shader(
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, VERTEX_SHADER, LIGHTING_MAP_VERTEX).c_str(), 
        Common::Instance().GetShaderProgramPath(PHONG_SHADING, FRAGMENT_SHADER, LIGHTING_MAP_VERTEX).c_str()
    );

    containerShader.Use();
    containerShader.SetUniformMat3(containerNormalMatrix, "normalMatrix");
    containerShader.SetUniformMat4(containerModel, "model");

    containerShader.SetUniformInt(light.type, "light.type");
    containerShader.SetUniformVec3(light.color, "light.color");
    containerShader.SetUniformVec3(light.position, "light.position");
    containerShader.SetUniformVec3(light.direction, "light.direction");
    containerShader.SetUniformFloat(light.intensity, "light.intensity");
    containerShader.SetUniformFloat(light.linear, "light.linear");
    containerShader.SetUniformFloat(light.quadratic, "light.quadratic");
    containerShader.SetUniformFloat(light.cosInnerCutOff, "light.cosInnerCutOff");
    containerShader.SetUniformFloat(light.cosOuterCutOff, "light.cosOuterCutOff");

    containerShader.SetUniformInt(0, "materialMap.diffuse");
    containerShader.SetUniformInt(1, "materialMap.specular");
    containerShader.SetUniformInt(2, "materialMap.emission");
    containerShader.SetUniformFloat(containerShininess, "materialMap.shininess");

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

        const glm::vec4& backgroundColor = Common::Instance().GetBackgroundColor();
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //-------------------------------------- DRAW PYRAMID --------------------------------------//

        pyramidShader.Use();
        pyramidShader.SetUniformMat4(projectionView, "projectionView");
        pyramidShader.SetUniformVec3(cameraPosition, "cameraPosition");
        pyramidTexture.Bind(0);
        pyramidVAO.Bind();
        glDrawElements(GL_TRIANGLES, pyramidIndices.size(), GL_UNSIGNED_INT, (void*)0);
        pyramidTexture.Unbind();
        pyramidVAO.Unbind();

        //-------------------------------------- DRAW CONTAINER --------------------------------------//

        containerShader.Use();
        containerShader.SetUniformMat4(projectionView, "projectionView");
        containerShader.SetUniformVec3(cameraPosition, "cameraPosition");
        containerDiffuseMap.Bind(0);
        containerSpecularMap.Bind(1);
        containerEmissionMap.Bind(2);
        containerVAO.Bind();
        glDrawElements(GL_TRIANGLES, containerIndices.size(), GL_UNSIGNED_INT, (void*)0);
        containerDiffuseMap.Unbind();
        containerSpecularMap.Unbind();
        containerEmissionMap.Unbind();
        containerVAO.Unbind();

        //-------------------------------------- DRAW LIGHT --------------------------------------//

        lightShader.Use();
        lightShader.SetUniformMat4(projectionView, "projectionView");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, lightIndices.size(), GL_UNSIGNED_INT, (void*)0);
        lightVAO.Unbind();

        //-------------------------------------- END OF DRAW --------------------------------------//

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    pyramidVAO.Delete();
    pyramidVBO.Delete();
    pyramidEBO.Delete();
    pyramidTexture.Delete();
    pyramidShader.Delete();

    containerVAO.Delete();
    containerVBO.Delete();
    containerEBO.Delete();
    containerDiffuseMap.Delete();
    containerSpecularMap.Delete();
    containerEmissionMap.Delete();
    containerShader.Delete();

    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    lightShader.Delete();

    glfwTerminate();
    return 0;
}
