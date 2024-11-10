/*
** EPITECH PROJECT, 2024
** Procedural-Visualizer
** File description:
** window_update
*/

#include "window.hpp"

#include "cube.hpp"
#include "primitive_generator.hpp"
// #include "random_primitive.hpp"
#include "Model.hpp"
#include "ObjLoader.hpp"
#include "Frustum.hpp"
#include "../parser/ObjModel.hpp"
#include <visualizer/ProceduralVisualizer.hpp>

namespace visualizer {
void Window::ProcessInput(GLFWwindow* window, MouseState& mouseState, Camera& camera) {
    // float cameraSpeed = 2.5f * deltaTime; use deltaTime for camera speed (UNCOMMENT)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.ProcessMouseScroll(1.0f); // Scroll up
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessMouseScroll(-1.0f);             // Scroll down
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // W = move forward
        camera.ProcessKeyboard(FORWARD, _deltaTime * 10);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // S = move backward
        camera.ProcessKeyboard(BACKWARD, _deltaTime * 10);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // A = move left
        camera.ProcessKeyboard(LEFT, _deltaTime * 5);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // D = move right
        camera.ProcessKeyboard(RIGHT, _deltaTime * 5);
    handleMouseDragging(window, mouseState, camera); // Handle mouse dragging
}

void Window::update() {
    MouseState           mouseState;
    Camera               camera(glm::vec3(0.0f, 0.0f, 3.0f));
    ProceduralVisualizer visualizer(width, height, camera, *window);
    visualizer.initialize();

    while (!ShouldClose()) {
        _deltaTime = CalculateDeltaTime();
        PollEvents();
        ProcessInput(window, mouseState, camera);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            using namespace ImGui;
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            Begin("Menu", NULL,
                  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
            Text("Application average: (%.1f FPS)", io->Framerate);
            End();
        }

        visualizer.update(_deltaTime);
        visualizer.render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SwapBuffers();
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }
    }
}
} // namespace visualizer
// void Window::update() {
//     Camera                   camera(glm::vec3(0.0f, 0.0f, 3.0f));
//     std::shared_ptr<Frustum> frustum = std::make_shared<Frustum>();
//     MouseState               mouseState;
//     int                      numVertices  = 128;
//     int                      numPositions = 10;
//     PrimitiveGenerator       theShapes("", numVertices, numPositions,
//                                        "src/primitives/random_primitive.hpp");
//     std::vector<float>       vertices        = theShapes.getVertices();
//     std::vector<glm::vec3>   randomPositions = theShapes.getPositions();
//     // cube coordinates are in /src/primitives/cube.hpp (TEMPORARY)

//     std::shared_ptr<Shaders> shaders = std::make_shared<Shaders>();
//     GLuint                   vertexShader =
//         shaders->compileShaderFromFile("src/shaders/glsl/vertex_shader.glsl",
//         GL_VERTEX_SHADER);
//     GLuint fragmentShader =
//         shaders->compileShaderFromFile("src/shaders/glsl/fragment_shader.glsl",
//         GL_FRAGMENT_SHADER);
//     // shaders->createProgram(vertexShader, fragmentShader, "cube");
//     shaders->createProgram(vertexShader, fragmentShader,
//     theShapes.getPrimitiveName().c_str()); VertexArray randomVAO(vertices.data(),
//     vertices.size()); randomVAO.bindAndUnbind();
//     // spawn at will

//     GLuint vertexComplexShader = shaders->compileShaderFromFile(
//         "src/shaders/glsl/complex_vertex_shader.glsl", GL_VERTEX_SHADER);
//     GLuint fragmentComplexShader = shaders->compileShaderFromFile(
//         "src/shaders/glsl/complex_fragment_shader.glsl", GL_FRAGMENT_SHADER);
//     shaders->createProgram(vertexComplexShader, fragmentComplexShader,
//     "generic_complex_obj");
//     // preprocessAllModels("src/primitives/obj");
//     ObjLoader objLoader;
//     objLoader.prepareObjModels("src/primitives/obj");
//     std::unordered_map<std::string, std::shared_ptr<ObjModel>> models =
//         loadAllModels("src/primitives/obj");

//     // load object Model
//     // Model complexTorus("src/primitives/obj/complex_torus.obj");

//     // Light and material properties
//     glm::vec3 lightPos(1.2f, 1.0f, 5.0f);
//     glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
//     glm::vec3 objectColor(1.0f, 1.0f, 1.0f);
//     glm::mat4 projection =
//         glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
//     // glm::mat4 view = camera.GetViewMatrix();
//     // set object color to red

//     while (!ShouldClose()) {
//         glm::mat4 view = camera.GetViewMatrix();
//         _deltaTime     = CalculateDeltaTime();
//         // Poll and handle events (inputs, window resize, etc.)
//         PollEvents();
//         ProcessInput(window, mouseState, camera);
//         // Start the Dear ImGui frame
//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplGlfw_NewFrame();
//         ImGui::NewFrame();

//         // Show menu etc
//         {
//             using namespace ImGui;
//             ImGui::SetNextWindowPos(ImVec2(0, 0));
//             Begin("Menu", NULL,
//                   ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
//                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
//             Text("Application average: (%.1f FPS)", io->Framerate);
//             End();
//         }

//         frustum->update(projection, view);
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         // Use the shader program
//         shaders->useProgram(theShapes.getPrimitiveName().c_str());
//         shaders->setMat4("projection", projection);
//         shaders->setMat4("view", view);

//         // Render random primitives
//         randomVAO.bind();
//         for (unsigned int i = 0; i < randomPositions.size(); i++) {
//             if (frustum->isPointVisible(randomPositions[i])) {
//                 glm::mat4 model = glm::mat4(1.0f);
//                 model           = glm::translate(model, randomPositions[i]);
//                 float angle     = glfwGetTime() * 50.0f; // Adjust the speed as needed
//                 model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//                 shaders->setMat4("model", model);

//                 glDrawArrays(GL_TRIANGLES, 0, numVertices);
//             }
//         }

//         shaders->useProgram("generic_complex_obj");

//         for (auto& [modelName, model] : models) {
//             if (model->isInFrustum(*frustum)) {

//                 // glm::vec3 modelPosition = glm::vec3(
//                 //     static_cast<float>(rand() % 10 - 5),
//                 //     static_cast<float>(rand() % 10 - 5),
//                 //     static_cast<float>(rand() % 10 - 5)
//                 // );
//                 // model->setPosition(modelPosition);
//                 // Light and material properties
//                 glm::vec3 lightPos(1.2f, 1.0f, 5.0f);
//                 glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

//                 // Example of applying transformations to the model
//                 glm::mat4 modelMatrix = glm::mat4(1.0f);
//                 modelMatrix           = glm::translate(modelMatrix, model->getPosition());
//                 // continous rotation
//                 float angle = glfwGetTime() * 50.0f; // Adjust the speed as needed
//                 modelMatrix =
//                     glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f,
//                     0.5f));

//                 // Set the shader uniforms
//                 glm::vec3 gradientColorStart(0.0f, 0.0f, 1.0f); // Blue
//                 glm::vec3 gradientColorEnd(1.0f, 0.0f, 0.0f);

//                 bool useGradient = false;
//                 shaders->setVec3("gradientColorStart", gradientColorStart);
//                 shaders->setVec3("gradientColorEnd", gradientColorEnd);
//                 shaders->setBool("useGradient", useGradient);

//                 shaders->setMat4("model", modelMatrix);
//                 shaders->setMat4("view", view);
//                 shaders->setMat4("projection", projection);
//                 shaders->setVec3("lightPos", lightPos);
//                 shaders->setVec3("viewPos", camera.Position);
//                 shaders->setVec3("lightColor", lightColor);
//                 shaders->setVec3("objectColor", objectColor);

//                 // Use the model matrix for rendering
//                 model->draw();
//             }
//         }

//         // Rendering ImGui
//         ImGui::Render();
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//         SwapBuffers();
//         GLenum err;
//         while ((err = glGetError()) != GL_NO_ERROR) {
//             std::cerr << "OpenGL error: " << err << std::endl;
//         }
//     }
//     randomVAO.deleteBuffers(); // acts like the destructor
// }
//}// namespace visualizer
