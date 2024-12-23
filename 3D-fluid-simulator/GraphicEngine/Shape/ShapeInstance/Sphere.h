#pragma once

#include "Essentials.h"
#include "GL/glew.h"
#include "Shape.h"
#include "VertexArray.h"

/**
 * @brief Class providing default sphere shape
 *
 */
class Sphere : public Shape<GL_TRIANGLES>
{
 private:
  static constexpr float radiusScaler = 1.90211303259030714423287866675876428;

 public:
  /**
   * @brief Construct a new sphere object around a given center
   *
   * @param center Center of the sphere
   * @param radius Radius of the sphere
   * @param enableTess Flag indicating if the tesselation is needed to create a
   * shape
   */
  Sphere(Vertex center = {{0, 0, 0}}, float radius = 15.f,
         bool enableTess = true);
  Sphere(Sphere const& obj_copy) = delete;
  Sphere(Sphere&& obj_move) = default;
  Sphere& operator=(Sphere const& obj_copy) = delete;
  Sphere& operator=(Sphere&& obj_move) = default;
  ~Sphere() override = default;
};
