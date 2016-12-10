
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/RenderErrorMacros.h"

#include <gl3w/gl3w.h>


VertexBuffer::VertexBuffer()
{
  m_VertexBufferName = 0;
  m_IndexBufferName = 0;
  m_LoadError = 0;
  m_Type = VertexBufferType::kInvalid;
  m_IndexCount = 0;
}

VertexBuffer::VertexBuffer(VertexBuffer && rhs) noexcept
{
  Move(std::move(rhs));
}

VertexBuffer::~VertexBuffer()
{
  Destroy();
}

VertexBuffer & VertexBuffer::operator = (VertexBuffer && rhs) noexcept
{
  Destroy();
  Move(std::move(rhs));
  return *this;
}

void VertexBuffer::Move(VertexBuffer && rhs) noexcept
{
  m_VertexBufferName = rhs.m_VertexBufferName;
  m_IndexBufferName = rhs.m_IndexBufferName;
  m_LoadError = rhs.m_LoadError;
  m_Type = rhs.m_Type;
  m_IndexCount = rhs.m_IndexCount;

  rhs.m_VertexBufferName = 0;
  rhs.m_IndexBufferName = 0;
  rhs.m_LoadError = 0;
  rhs.m_Type = VertexBufferType::kInvalid;
  rhs.m_IndexCount = 0;
}

void VertexBuffer::Destroy()
{
  if (m_VertexBufferName != 0)
  {
    glDeleteBuffers(1, &m_VertexBufferName);
    m_VertexBufferName = 0;
  }

  if (m_IndexBufferName != 0)
  {
    glDeleteBuffers(1, &m_IndexBufferName);
    m_IndexBufferName = 0;
  }

  m_LoadError = 0;
  m_Type = VertexBufferType::kInvalid;
  m_IndexCount = 0;
}

void VertexBuffer::SetBufferData(const gsl::span<VertexInfo> & verts, const gsl::span<uint16_t> & indices, VertexBufferType type)
{
  if (m_VertexBufferName == 0)
  {
    glGenBuffers(1, &m_VertexBufferName); CHECK_GL_RENDER_ERROR;
  }

  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferName); CHECK_GL_RENDER_ERROR;
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo) * verts.size(), verts.data(), GL_STATIC_DRAW); CHECK_GL_RENDER_ERROR;
  glBindBuffer(GL_ARRAY_BUFFER, 0); CHECK_GL_RENDER_ERROR;

  m_Type = type;
  m_IndexCount = (uint32_t)indices.size();

  if (m_IndexBufferName == 0)
  {
    glGenBuffers(1, &m_IndexBufferName); CHECK_GL_RENDER_ERROR;
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferName); CHECK_GL_RENDER_ERROR;
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW); CHECK_GL_RENDER_ERROR;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); CHECK_GL_RENDER_ERROR;
}


void VertexBuffer::CreateDefaultBinding(const ShaderProgram & program) const
{
  int position_attrib_loc = glGetAttribLocation(program.m_ProgramName, "a_Position"); CHECK_GL_RENDER_ERROR;
  int texcoord_attrib_loc = glGetAttribLocation(program.m_ProgramName, "a_TexCoord"); CHECK_GL_RENDER_ERROR;
  int color_attrib_loc = glGetAttribLocation(program.m_ProgramName, "a_Color"); CHECK_GL_RENDER_ERROR;

  if (position_attrib_loc >= 0)
  {
    glEnableVertexAttribArray(position_attrib_loc); CHECK_GL_RENDER_ERROR;
    glVertexAttribPointer(position_attrib_loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void *)offsetof(VertexInfo, m_Position)); CHECK_GL_RENDER_ERROR;
  }

  if (texcoord_attrib_loc >= 0)
  {
    glEnableVertexAttribArray(texcoord_attrib_loc); CHECK_GL_RENDER_ERROR;
    glVertexAttribPointer(texcoord_attrib_loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void *)offsetof(VertexInfo, m_TexCoord)); CHECK_GL_RENDER_ERROR;
  }

  if (color_attrib_loc >= 0)
  {
    glEnableVertexAttribArray(color_attrib_loc); CHECK_GL_RENDER_ERROR;
    glVertexAttribPointer(color_attrib_loc, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void *)offsetof(VertexInfo, m_Color)); CHECK_GL_RENDER_ERROR;
  }
}

void VertexBuffer::Draw(int index_start, int index_end) const
{
  if (m_IndexBufferName == 0 || m_LoadError != 0)
  {
    return;
  }

  GLenum mode;
  switch (m_Type)
  {
  case VertexBufferType::kPoints:
    mode = GL_POINTS;
    break;
  case VertexBufferType::kLines:
    mode = GL_LINES;
    break;
  case VertexBufferType::kTriangles:
    mode = GL_TRIANGLES;
    break;
  case VertexBufferType::kQuads:
    mode = GL_QUADS;
    break;
  default:
  case VertexBufferType::kInvalid:
    return;
  }

  if (index_end < 0)
  {
    index_end = m_IndexCount;
  }

  glDrawRangeElements(mode, index_start, m_IndexCount, index_end - index_start, GL_UNSIGNED_SHORT, 0); CHECK_GL_RENDER_ERROR;
}

void VertexBuffer::Bind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferName); CHECK_GL_RENDER_ERROR;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferName); CHECK_GL_RENDER_ERROR;
}

void VertexBuffer::Unbind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, 0); CHECK_GL_RENDER_ERROR;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); CHECK_GL_RENDER_ERROR;
}