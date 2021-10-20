#include "GLInclude.h"

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
/*
//Kristina's Plane Class
class Plane(){
  public:
    float a, b, c, d;
    Plane(float a = 0.0, float b = 0.0, float c = 1.0, float d = 0.0);
    Plane(Point p1, Point p2, Point p3);
    Vector normal() {return Vector(a, b, c);}
}
*/

class Plane(){
  glm::vec3 p(0.f, -1.f, 0,f);
  glm::vec3 n(0.f, 0.f, 0.f);
  Plane();
  Plane(float x, float y, float z, float u, float v, float w){
    p= glm::vec3(x,y,z);
    n= glm::vec3(u,v,w);
  }
}

class Sphere(){//might have to make a sphere class
  float rad = 1.0;
  glm::vec3 c(0.f, 0.f, 0.f);//center of the sphere is origin
  glm::vec3 n(0.f, 0.f, 0.f);//normal of the sphere
  Sphere();//default constructor
  Sphere(float x, float y, float z, float r_){//user inputs their own radius and center
    center = glm::vec3 (x,y,z);
    rad = r_;
    //n = (x-center)/radius where x is the point along the ray
  }

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


