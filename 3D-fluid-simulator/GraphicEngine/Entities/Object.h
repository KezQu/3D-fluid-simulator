#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include "Debug.h"
#include "Entity.h"
#include "Essentials.h"
#include "GL/glew.h"
#include "Program.h"
#include "ProgramDispatch.h"
#include "Shape.h"
#include "Simulator.h"
#include "imgui.h"

/**
 * @brief Class representing a static object present in the simulation
 *
 * @tparam Prim OpenGL primitive used to generate the shape of an object
 */
template <GLenum Prim>
class Object : public Entity
{
 private:
  std::unique_ptr<Shape<Prim>> _shape;

 public:
  /**
   * @brief Creates a object with a given shape
   *
   * @param shape shape that the object will have
   */
  Object(Shape<Prim>* const shape);
  Object(Object const& obj_copy) = delete;
  Object(Object&& obj_move) = default;
  Object& operator=(Object const& obj_copy) = delete;
  Object& operator=(Object&& obj_move) = default;
  ~Object() override = default;
  void Initialize() override;
  void Calculate() override;
  void Draw() const override;
  Essentials::DetailControls Details() override;
  Essentials::ShapeProperties GetShapeProperties() override;
};

template <GLenum Prim>
Object<Prim>::Object(Shape<Prim>* const shape)
    : Entity{Essentials::PhysicsType::STATIC},
      _shape{std::unique_ptr<Shape<Prim>>(shape)}
{
  // Initialize created object in order to be displayed in the simulation
  // context
  Initialize();
}

template <GLenum Prim>
void Object<Prim>::Initialize()
{
  // Initialize physics for a given object with the needed uniforms and buffers
  // specified in a callback
  _physicsDispatch.Initialize(
      _mesh_size.GetValue(), [this](uint32_t program_id) {
        _shape->BindUniforms(program_id);
        Simulator::GetInstance()->BindUniforms(program_id);
        Simulator::GetInstance()->BindTerrain(program_id);
        Bind(program_id);
      });
}

template <GLenum Prim>
void Object<Prim>::Calculate()
{
  // Calculate physics for a given object depending whether it is visible in the
  // context
  if (_visible)
  {
    _physicsDispatch.CalculateFrame(
        _mesh_size.GetValue(), [this](uint32_t program_id) {
          _shape->BindUniforms(program_id);
          Simulator::GetInstance()->BindUniforms(program_id);
          Simulator::GetInstance()->BindTerrain(program_id);
          Bind(program_id);
        });
  }
}

template <GLenum Prim>
void Object<Prim>::Draw() const
{
  // Draw an object for a current frame for a specified program pipeline
  // depending on whether the tesselation for a shape is required or not
  if (_visible)
  {
    // Choose a rendering pipeline
    Program& renderer =
        _shape->GetTesselation() == true
            ? ProgramDispatch::GetInstance()->GetTesselationPipeline()
            : ProgramDispatch::GetInstance()->GetSimplePipeline();

    // Recompile pipeline and link if that process in needed
    if (!renderer.isLinked()) renderer.Link();

    // Bind pipeline and needed buffers and uniforms to perform drawing
    renderer.Bind();
    _shape->Bind(renderer.ID());
    Simulator::GetInstance()->BindUniforms(renderer.ID());
    _physicsDispatch.BindPhysicsMesh(renderer.ID());
    // Schedule drawing command for a given object
    _(glDrawElements(_shape->GetDrawPrimitive(), _shape->GetVA().Size(),
                     _shape->GetVA().IndexBufferType(), nullptr));
  }
}

template <GLenum Prim>
Essentials::DetailControls Object<Prim>::Details()
{
  // Retrieve controls of a base class and attach new controls specific to an
  // object class, allowing also to modify the properties of objects' shape
  auto details = Entity::Details();
  auto& shape_properties = this->_shape->GetShapeProperties();
  auto const& ui_callback = [this]() {
    auto old_sim_state_saved = Simulator::GetInstance()->GetSimulationState();
    Simulator::GetInstance()->SetSimulationState(
        Essentials::SimulationState::IDLE);
    Initialize();
    Simulator::GetInstance()->SetSimulationState(old_sim_state_saved);
  };

  details.push_back({"Location", shape_properties._location.ExposeToUI()});
  details.push_back({"Rotation", shape_properties._rotation.ExposeToUI()});
  details.push_back({"Scale", shape_properties._scale.ExposeToUI()});
  details.push_back(
      {"Subdivision", shape_properties._subdivision.ExposeToUI()});
  details.push_back(
      {"Color type", [ui_callback, &shape_properties]() {
         if (ImGui::Combo("##Color_type",
                          (int32_t*)&shape_properties._color.first.GetValue(),
                          Essentials::ColorPropertyTolistObject()))
         {
           ui_callback();
         }
       }});
  details.push_back(
      {"Color", shape_properties._color.second.ExposeToUI(ui_callback)});
  details.push_back({"Radius", shape_properties._radius.ExposeToUI()});
  return details;
}

template <GLenum Prim>
Essentials::ShapeProperties Object<Prim>::GetShapeProperties()
{
  return _shape->GetShapeProperties();
}
