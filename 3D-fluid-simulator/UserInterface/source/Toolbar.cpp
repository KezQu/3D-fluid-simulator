﻿#include "Toolbar.h"

#include "Camera.h"

bool Toolbar::_fullscreen = false;
std::unordered_map<Essentials::SimulationState, std::string>
    Toolbar::simulationState{
        {Essentials::SimulationState::IDLE, "Start"},
        {Essentials::SimulationState::INIT, "Start"},
        {Essentials::SimulationState::SIMULATION, "Stop"},
        {Essentials::SimulationState::GEN_FRAME, "Stop"},
    };

Toolbar::Toolbar(ImVec2 const& size, ImVec2 const& position)
    : Interface(size, position,
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar |
                    ImGuiWindowFlags_NoDecoration |
                    ImGuiWindowFlags_AlwaysAutoResize)
{
}

void Toolbar::Generate()
{
  ImGui::SetNextWindowPos(_position);
  ImGui::SetNextWindowSize(_size);

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
  if (ImGui::Begin("##Toolbar", nullptr, _flags))
  {
    if (ImGui::Button(simulatorInstance.GetSimulationState() ==
                              Essentials::SimulationState::IDLE
                          ? "Start"
                          : "Pause"))
    {
      simulatorInstance.SetSimulationState(
          simulatorInstance.GetSimulationState() ==
                  Essentials::SimulationState::SIMULATION
              ? Essentials::SimulationState::IDLE
              : Essentials::SimulationState::SIMULATION);
    }
    if (simulatorInstance.GetSimulationState() !=
        Essentials::SimulationState::SIMULATION)
    {
      ImGui::SameLine();
      if (ImGui::Button("One frame"))
      {
        simulatorInstance.SetSimulationState(
            Essentials::SimulationState::GEN_FRAME);
      }
    }
    else
    {
      ImGui::SameLine();
      if (ImGui::Button("Stop"))
      {
        simulatorInstance.SetSimulationState(Essentials::SimulationState::INIT);
      }
    }
    ImGui::SameLine();
    ImGui::PushItemWidth(100.f);
    static float static_timestep = 6.f;
    ImGui::DragFloat("##timestep_value", &static_timestep, 0.1f, 0.f, 1000.f,
                     "%.1f ms", ImGuiSliderFlags_AlwaysClamp);
    ImGui::SameLine();
    if (ImGui::Button("Set timestep") || static_timestep > 1e-6f)
    {
      simulatorInstance.UpdateDeltaTime(static_timestep);
    }
    else
    {
      simulatorInstance.UpdateDeltaTime();
    }
    ImGui::PopItemWidth();

    ImGui::SameLine(_size.x - 200);
    ImGui::Text("%mouse speed: %.1f", Camera::GetCamera().GetMoveSpeed());
    std::string framerate =
        std::to_string(static_cast<int>(ImGui::GetIO().Framerate)) + " FPS";
    auto FPS_text_size = ImGui::CalcTextSize(framerate.c_str()).x;
    ImGui::SameLine(_size.x - FPS_text_size);
    ImGui::Text(framerate.c_str());
  }
  ImGui::End();
  ImGui::PopStyleVar();
}
