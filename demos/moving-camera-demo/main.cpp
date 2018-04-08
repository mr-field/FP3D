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
    Vector3 cubeCenter = Vector3(1, 0, 2);
    Vector3 pyramidCenter = Vector3(-1, 0, 2);

    Mesh cube = Mesh::createCube(1, cubeCenter);
    cube.material = Material(ColorRGB(0.0, 0.1, 0.9));

    Mesh pyramid = Mesh::createPyramid(1, 1, pyramidCenter);
    pyramid.translate(Vector3(-1, 0, 0));
    pyramid.scale(2);
    pyramid.rotateX((180 * M_PI) / 180);
    pyramid.material = Material(ColorRGB(0.1, 0.9, 0.2));

    Mesh obj = Mesh::importObj("sample-obj/alfa147.obj");
    obj.translate(Vector3(-2, -0.5f, 0));
    obj.rotateX(-90 * M_PI / 180);
    obj.scale(0.01);
    obj.material = Material(ColorRGB(0.9, 0.1, 0.0));

    Camera camera = Camera(Vector3(0, 0, 0), 100, 0.1, 100, 800, 600);
    //camera.rotateY((45 * M_PI) / 180);
    std::vector<Mesh> meshes = std::vector<Mesh>({pyramid, cube, obj});

    Scene scene = Scene(meshes, camera);
    Light light(Vector3(0, 0, -1));
    light.intensity = 250;
    scene.lights.push_back(light);

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