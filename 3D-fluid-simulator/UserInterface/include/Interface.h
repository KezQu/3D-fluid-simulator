#pragma once

#include <cstdint>

#include "Simulator.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"

class Interface
{
 protected:
  ImVec2 _size;
  ImVec2 _position;
  ImGuiWindowFlags _flags;

 public:
  Interface(ImVec2 const& size, ImVec2 const& position, ImGuiWindowFlags flags);
  virtual ~Interface();
  virtual void Generate() = 0;
};
