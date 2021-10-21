#include "GLInclude.h"


float tauVal(float col, float right, float left, float pixelX){//finding the value of tau (x-axis)
  float tau = left + ((right - left)/pixelX)*(col + 0.5);
  return tau;
}

float sigmaVal(float row, float top, float bott, float pixelY){//finding the value of sigma (y-axis)
  float sigma = bott + ((top - bott)/pixelY)*(row + 0.5);
  return sigma;
}

//this puts values in the point and direction of a ray instance
Ray generateRay(float tau, float sigma, const Camera& camera){
  Ray r();
  r.point= camera.eye;
  r.vec= direction(tau,sigma, 1.f);
  return r;
  //forgot to return some Ray; not sure if it's the right syntax
}

Ray planeIntersection(Ray i, Plane j){
  if(glm::dot(i.vec, j.n)>0){//if vector i dot normal greater than 0
    float t = glm::dot((j.p-i.point), j.n)/glm::dot(i.vec, j.n);
    if(t>0){
      Ray result(i.point + t*i.vec, plane.n);
      return result;
    }
  }
  //return something else??
}

Ray sphereIntersection(Ray i, Sphere j){
  float A = glm::pow(i.vec, 2.f);
  float B = glm::dot(2*i.vec, (i.point - j.center));//need to add center in sphere class
  float C = glm::pow((i.point - j.center), 2.f) - glm::pow(j.radius, 2.f);//need to add radius in sphere class

  //both formulas use the discriminant
  float t1 = (-B+glm::sqrt(glm::pow(B, 2) - 4*A*C))/(2*A);
  float t2 = (-B+glm::sqrt(glm::pow(B, 2) - 4*A*C))/(2*A);

  if(t1<t2 && t1>0){
    Ray result(i,point + t1*i.vec, Sphere.n);//need to add normal to the sphere
  }else if(t2<t1 && t2>0){
    Ray result(i,point + t2*i.vec, Sphere.n);//need to add normal to the sphere
  }else{
    //return something when both t1 and t2 are less than 0
  }

  return result;

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
