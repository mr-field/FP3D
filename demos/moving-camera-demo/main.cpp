#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <Scene.h>
#include <OGLRenderer.h>
#include <cmath>

void updateCamera(Scene& scene, GLFWwindow* window) {
    Vector3 forward = scene.camera.transform.forward();
    Vector3 right = scene.camera.transform.right();
    Vector3 newPosition = scene.camera.transform.position();

    if (glfwGetKey(window, GLFW_KEY_W)) {
        newPosition += forward * 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        newPosition -= forward * 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        newPosition -= right * 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        newPosition += right * 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_E)) {
        scene.camera.rotateY(-0.5 * M_PI / 180);
    }
    if (glfwGetKey(window, GLFW_KEY_Q)) {
        scene.camera.rotateY(0.5 * M_PI / 180);
    }

    scene.camera.transform.setPosition(newPosition);
}


int main() {
    // Setup scene
    Camera camera = Camera(Vector3(0, 0, 0), 90, 0.1f, 100, 500, 500);
    Scene scene = Scene(camera);

    Vector3 cube1Center = Vector3(-1, 0, 2);
    Mesh cube1 = Mesh::createCube(1, cube1Center);
    cube1.material = Material(ColorRGB(0, 0, 1));
    scene.addMesh(cube1);

    Vector3 cube2Center = Vector3(1, 0, 2);
    Mesh cube2 = Mesh::createCube(1, cube2Center);
    cube2.material = Material(ColorRGB(1, 0, 0));
    //scene.addMesh(cube2);

    Vector3 cube3Center = Vector3(0, 0, 2);
    Mesh cube3 = Mesh::createCube(5, cube3Center);
    cube3.flipNormals();
    cube3.material = Material(ColorRGB(1, 1, 1));
    scene.addMesh(cube3);

    Vector3 planeCenter = Vector3(0, -0.5f, 2);
    Mesh plane = Mesh::createPlane(10, planeCenter);
    plane.material = Material(ColorRGB(1, 1, 1));
    scene.addMesh(plane);

    Mesh obj = Mesh::importObj("sample-obj/alfa147.obj");
    obj.translate(Vector3(0.8f, -0.5f, 2));
    obj.rotateX(-90 * M_PI / 180);
    obj.scale(0.01);
    obj.material = Material(ColorRGB(0.9, 0.1, 0.0));
    scene.addMesh(obj);

    Light light(Vector3(1, 1, 0));
    light.color = ColorRGB(1, 1, 1);
    light.intensity = 100;
    scene.addLight(light);

    // Create window and OpenGL context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(scene.camera.width, scene.camera.height, "OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Could not create GLFW window" << std::endl;
    }
    glfwMakeContextCurrent(window);

    // Create renderer
    OGLRenderer renderer = OGLRenderer(&scene);

    // Render the scene
    while (!glfwWindowShouldClose(window)) {
        renderer.render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        updateCamera(scene, window);
    }
}