////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Contains main function to create a window and run engine that
///        repeatedly generates a framebuffer and displays it.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
// STL
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// Engine
#include "GLInclude.h"

////////////////////////////////////////////////////////////////////////////////
// Global variables - avoid these

// Window
int g_width{1360};
int g_height{768};

// Framebuffer
std::unique_ptr<glm::vec4[]> g_frame{nullptr}; ///< Framebuffer

// Frame rate
const unsigned int FPS = 60;
float g_frameRate{0.f};
std::chrono::high_resolution_clock::time_point g_frameTime{
  std::chrono::high_resolution_clock::now()};
float g_delay{0.f};
float g_framesPerSecond{0.f};

////////////////////////////////////////////////////////////////////////////////
// Functions
//To-Do List:
//scene with a ground plane with a normal n=y axis centered on p=(0,0,0)

//point light emanates from a point l in all directions

///////
//Jory's pseudocode
//i, j is which cell on the view plane
//for each column i do
//  for each row j do 
//    generate a ray origin and direction
//
//    find the first intersection point of the ray
//
//    shade the ray intersection
/*
//generate a ray origin + direction from perspective view
Ray genertate_ray(int col, int row, const Camera& camera){//make a ray class
  Ray r;
  r.origin = camera.eye();
}

//For each light source do
//  computer ambient, diffuse, and specular
//  add to final color

glm::vec4 getColor(const vector<Light>& lights, const Material& material, const glm::vec3& point, const::vec3& normal){

  for (const Light& light : lights){
    glm::vec4 ambient = 
    glm::vec4 diffuse = 
    glm::vec4 specular = 
    final_color += ambient + diffuse + specular;
  }

  return final_color;

}
///////


class Camera{
  public:
    Camera();

    const glm::vec3& eye() { return m_eye; }
  private:
    glm::vec3 eye;
}
*/
//hardcode camera coordinate frame

class Plane(){
  
}

struct Material(){//material structure

  glm::vec4 ambient(float xk, float yk, float zk, float xI, float yI, float zI){
    glm::vec4 ka(xk, yk, zk, 0.f);//material for ambient
    glm::vec4 Ia(xI, yI, zI, 0.f);//intensity to ambient
    glm::vec4 ambientAns = ka*Ia;//ambient light eqn
    return ambientAns;

  }

  glm::vec4 diffuse(float xk, float yk, float zk, float xI, float yI, float zI){
    glm::vec4 kd(xk, yk, zk, 0.f);//material for diffuse
    glm::vec4 Id(xI, yI, zI, 0.f);//intensity for diffuse
    glm::vec3 n(0.f, 0.f, 0.f);//normal
    glm::vec4 nNew = glm::vec4(n, 0.f);//convert to vector 4
    glm::vec3 l(0.f, 0.f, 0.f);//light vector??
    glm::vec4 lNew = glm::vec4(l, 0.f);//convert to vector 4
    glm::vec4 diffuseAns = kd*Id*glm::max(0.f, glm::dot(nNew, lNew));//diffuse lighting eqn
    retrun diffuseAns;
  }

  glm::vec4 specular(float xk, float yk, float zk, float xI, float yI, float zI, float p){
    //p is shininess value
    glm::vec4 ks(xk, yk, zk, 0.f);//material for specular
    glm::vec4 Is(xI, yI, zI, 0.f);//intensity for specular
    glm::vec3 v(0.f, 0.f, 0.f);//direction of camera
    glm::vec4 vNew = glm::vec4(v, 0.f);//converted to vec4
    glm::vec3 h = (v+l)/glm::vec3 length(v+l);
    glm::vec4 hNew = glm::vec4(h, 0.f);//converted to vec4
    glm::vec4 specularAns = ks*Is*(glm::pow(glm::max(0.f, glm::dot(vNew, hNew)), p));//specular lighting eqn
    return specularAns;
  }


}//prob make a function for the materials


class Sphere(){//might have to make a sphere class

  float r;
  public:
    Sphere(){//default constructor
      glm::vec3 p(0.f, 0.f, 0.f);//center of the sphere is origin
      r = 1.0;
      
    }

    Sphere(float x, float y, float z, float r_){//user inputs their own radius and center
      glm::vec3 p(x, y, z);
      r_ = r;
      
    }

}

////////////////////////////////////////////////////////////////////////////////
/// @brief Initialize GL settings
void
initialize(GLFWwindow* _window) {
  glClearColor(0.f, 0.f, 0.f, 1.f);

  g_frame = std::make_unique<glm::vec4[]>(g_width*g_height);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback for resize of window
///
/// Responsible for setting window size (viewport) and projection matrix.
void resize(GLFWwindow* window, int _w, int _h) {
  g_width = _w;
  g_height = _h;

  // Viewport
  glfwGetFramebufferSize(window, &g_width, &g_height);
  glViewport(0, 0, g_width, g_height);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Draw function for single frame
void
draw(GLFWwindow* _window, double _currentTime) {
  //////////////////////////////////////////////////////////////////////////////
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);

  for(int i = 0; i < g_width*g_height; ++i)
    g_frame[i] = glm::vec4(0.f, 0.4f, 0.f, 0.f);

  //////////////////////////////////////////////////////////////////////////////
  // Draw

  // Simple static :P
  for(int i = 0; i < g_width*g_height; ++i)
    g_frame[i] = glm::vec4(float(rand())/RAND_MAX, float(rand())/RAND_MAX,
                           float(rand())/RAND_MAX, 1.f);

  glDrawPixels(g_width, g_height, GL_RGBA, GL_FLOAT, g_frame.get());
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Main application loop
void
run(GLFWwindow* _window) {
  using namespace std::chrono;

  std::cout << "Starting main loop" << std::endl;

  while(!glfwWindowShouldClose(_window)) {
    draw(_window, glfwGetTime());
    ////////////////////////////////////////////////////////////////////////////
    // Show
    glfwSwapBuffers(_window);
    glfwPollEvents();

    ////////////////////////////////////////////////////////////////////////////
    // Record frame time
    high_resolution_clock::time_point time = high_resolution_clock::now();
    g_frameRate = duration_cast<duration<float>>(time - g_frameTime).count();
    g_frameTime = time;
    g_framesPerSecond = 1.f/(g_delay + g_frameRate);
    printf("FPS: %6.2f\n", g_framesPerSecond);

    ////////////////////////////////////////////////////////////////////////////
    // Delay to fix the frame-rate
    g_delay = std::max(0.f, 1.f/FPS - g_frameRate);
    std::this_thread::sleep_for(std::chrono::microseconds(
        static_cast<long int>(g_delay*1000)));
  }

  std::cout << "Ending main loop" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard input
/// @param _window
/// @param _key Key
/// @param _scancode Platform specific keycode
/// @param _action Action, e.g., pressed or released
/// @param _mods Keyboard modifiers
void
keyCallback(GLFWwindow* _window, int _key, int _scancode,
           int _action, int _mods) {
  if(_action == GLFW_PRESS) {
    switch(_key) {
      // Escape key : quit application
      case GLFW_KEY_ESCAPE:
        std::cout << "Closing window" << std::endl;
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
        break;
        // Arrow keys
      case GLFW_KEY_LEFT:
      case GLFW_KEY_RIGHT:
        break;
        // Unhandled
      default:
        std::cout << "Unhandled key: " << _key << std::endl;
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
// Main

////////////////////////////////////////////////////////////////////////////////
/// @brief main
/// @param _argc Count of command line arguments
/// @param _argv Command line arguments
/// @return Application success status
int
main(int _argc, char** _argv) {
  //////////////////////////////////////////////////////////////////////////////
  // Initialize
  std::cout << "Initializing GLFWWindow" << std::endl;
  // GLFW
  if(!glfwInit()) {
    std::cerr << "GLFW Cannot initialize" << std::endl;
    return 1;
  }

  GLFWwindow* window = glfwCreateWindow(
    g_width, g_height, "Spiderling: A Rudamentary Game Engine", NULL, NULL);
  if(!window) {
    std::cerr << "GLFW Cannot create window" << std::endl;
    const char* err_msg;
    int error_code = glfwGetError(&err_msg);
    std::cerr << "Error " << error_code << ": " << err_msg << std::endl;
    return 1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwGetFramebufferSize(window, &g_width, &g_height);
  glViewport(0, 0, g_width, g_height);  // Initialize viewport


  // Assign callback functions
  std::cout << "Assigning Callback functions" << std::endl;
  glfwSetFramebufferSizeCallback(window, resize);
  glfwSetKeyCallback(window, keyCallback);

  // Program initialize
  std::cout << "Initializing application" << std::endl;
  initialize(window);

  //////////////////////////////////////////////////////////////////////////////
  // Main loop
  run(window);

  //////////////////////////////////////////////////////////////////////////////
  // Cleanup GLFW Window
  std::cout << "Destroying GLFWWindow" << std::endl;
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
