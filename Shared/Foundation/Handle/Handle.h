#pragma once

#include <cstdint>

struct Handle
{
  unsigned int m_Valid : 1;
  unsigned int m_Gen : 7;
  unsigned int m_Index : 24;

  Handle()
  {
    m_Valid = 0;
    m_Gen = 0;
    m_Index = 0;
  }

  Handle(const Handle & rhs) = default;

  bool operator == (const Handle & rhs) const
  {
    return *reinterpret_cast<const uint32_t *>(this) == *reinterpret_cast<const uint32_t *>(&rhs);
  }

  bool operator != (const Handle & rhs) const
  {
    return *reinterpret_cast<const uint32_t *>(this) != *reinterpret_cast<const uint32_t *>(&rhs);
  }
};

static const Handle kInvalidHandle = {};

template <typename ManagerType>
class SpecificHandle : public Handle
{
public:
  SpecificHandle()
  {

  }

  SpecificHandle(Handle handle) : Handle(handle)
  {

  }

  bool operator == (const SpecificHandle<ManagerType> & rhs) const
  {
    return *reinterpret_cast<const uint32_t *>(this) == *reinterpret_cast<const uint32_t *>(&rhs);
  }

  bool operator != (const SpecificHandle<ManagerType> & rhs) const
  {
    return *reinterpret_cast<const uint32_t *>(this) != *reinterpret_cast<const uint32_t *>(&rhs);
  }

  bool operator == (const Handle & rhs) const
  {
    return *reinterpret_cast<const uint32_t *>(this) == *reinterpret_cast<const uint32_t *>(&rhs);
  }

  bool operator != (const Handle & rhs) const
  {
    return *reinterpret_cast<const uint32_t *>(this) != *reinterpret_cast<const uint32_t *>(&rhs);
  }
};
