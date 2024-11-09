#include "ProgramDispatch.h"

ProgramDispatch::ProgramDispatch()
    : _shaderPipelineSimple{{GL_VERTEX_SHADER, "/ElementTessOff.vert"},
                            {GL_VERTEX_SHADER, "/CalculateColor.glsl"},
                            {GL_VERTEX_SHADER, "/CalculateNDC.glsl"},
                            {GL_FRAGMENT_SHADER, "/Element.frag"}},
      _shaderPipelineWithTesselation{
          {GL_VERTEX_SHADER, "/ElementTessOn.vert"},
          {GL_TESS_CONTROL_SHADER, "/Element.tesc"},
          {GL_TESS_EVALUATION_SHADER, "/Element.tese"},
          {GL_TESS_EVALUATION_SHADER, "/CalculateNDC.glsl"},
          {GL_FRAGMENT_SHADER, "/Element.frag"}}
{
}

std::unique_ptr<ProgramDispatch>& ProgramDispatch::GetInstance()
{
  static std::unique_ptr<ProgramDispatch> instance{nullptr};

  if (instance == nullptr)
  {
    instance = std::unique_ptr<ProgramDispatch>{new ProgramDispatch{}};
  }
  return instance;
}

void ProgramDispatch::CleanUp()
{
  GetInstance().reset(nullptr);
}

Program& ProgramDispatch::GetSimplePipeline()
{
  return GetInstance()->_shaderPipelineSimple;
}

Program& ProgramDispatch::GetTesselationPipeline()
{
  return GetInstance()->_shaderPipelineWithTesselation;
}
