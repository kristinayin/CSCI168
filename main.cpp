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

float tauVal(float col, float right, float left, float pixelX){//finding the value of tau (x-axis)
  float tau = left + ((right - left)/pixelX)*(col + 0.5);
  return tau;
}

float sigmaVal(float row, float top, float bott, float pixelY){//finding the value of sigma (y-axis)
  float sigma = bott + ((top - bott)/pixelY)*(row + 0.5);
  return sigma;
}

//This calculates the direction of a ray based 
//on the tau and theta value on the viewport
glm::vec3 direction(float tau, float sigma, float focal){
  glm::vec3 w(0.f, 0.f, -1.f);
  glm::vec3 u(1.f, 0.f, 0.f);
  glm::vec3 v(0.f, 1.f, 0.f);
  glm::vec3 dir;
  dir= focal*w + tau*u + sigma*v;
  return dir;
}

//this puts values in the point and direction of a ray instance
Ray generateRay(float tau, float sigma, const Camera& camera){
  Ray r();
  r.point= camera.eye;
  r.vec= direction(tau,sigma, 1.f);
}

//camera
class Camera(){
  glm::vec3 eye(0.f, 0.f, 0.f);
  Camera();
  Camera(float x, float y, float z){
    eye[0]=x;
    eye[1]=y;
    eye[2]=z;
  } 
}

void rayCast(const Camera& camera, float length, float height){
  //maybe use a vector to store data for input of each pixel??
  for(int x=0; x<length; x++){
    for(int y=0; y<height; y++){
      Ray r();
      r= generateRay(x,y,camera);

    }
  }
}

//create a depth testing function
/*

*/

//holds the RGBO values of an object
class color(){
  glm::vec4 rgb;
  color(){
    glm::vec4 rgb = glm::vec4(0.f,0.f,0.f,0.f);
  }
  color(float R, float G, float B, float O){
    glm::vec4 rgb = glm::vec4(R,G,B,O);
  }
}

//holds a point and a vector for direction adn an RGB value
class Ray(){
  glm::vec3 point(0.f, 0.f, 0.f);
  glm::vec3 vec(0.f, 0.f, 0.f);
  color RGB();
  Ray();
  Ray(vec3 p, vec3 v){
    point = p;
    vec = v;
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
int main(int _argc, char** _argv) {
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
