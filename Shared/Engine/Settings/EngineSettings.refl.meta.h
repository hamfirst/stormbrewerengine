#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "EngineSettings.refl.h"


template <>
struct StormReflTypeInfo<EngineSettings>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "EngineSettings"; }
  static constexpr auto GetNameHash() { return 0x372CF65D; }
  static constexpr bool HasDefault() { return true; }
  static EngineSettings & GetDefault() { static EngineSettings def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<EngineSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const EngineSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<EngineSettings *>(ptr);
    if(typeid(EngineSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const EngineSettings *>(ptr);
    if(typeid(EngineSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<EngineSettings>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AssetLoadQueueSize"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8D4B1025; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &EngineSettings::m_AssetLoadQueueSize; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<EngineSettings *>(obj); return &ptr->m_AssetLoadQueueSize; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const EngineSettings *>(obj); return &ptr->m_AssetLoadQueueSize; }
};

template <typename Self>
struct StormReflTypeInfo<EngineSettings>::field_data<0, Self> : public StormReflTypeInfo<EngineSettings>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_AssetLoadQueueSize; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_AssetLoadQueueSize; }
  void SetDefault() { self.m_AssetLoadQueueSize = StormReflTypeInfo<EngineSettings>::GetDefault().m_AssetLoadQueueSize; }
};

template <>
struct StormReflTypeInfo<EngineSettings>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AssetLoadThreads"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x141FA100; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &EngineSettings::m_AssetLoadThreads; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<EngineSettings *>(obj); return &ptr->m_AssetLoadThreads; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const EngineSettings *>(obj); return &ptr->m_AssetLoadThreads; }
};

template <typename Self>
struct StormReflTypeInfo<EngineSettings>::field_data<1, Self> : public StormReflTypeInfo<EngineSettings>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_AssetLoadThreads; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_AssetLoadThreads; }
  void SetDefault() { self.m_AssetLoadThreads = StormReflTypeInfo<EngineSettings>::GetDefault().m_AssetLoadThreads; }
};

template <>
struct StormReflTypeInfo<EngineSettings>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_FontCacheSize"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2011866D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &EngineSettings::m_FontCacheSize; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<EngineSettings *>(obj); return &ptr->m_FontCacheSize; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const EngineSettings *>(obj); return &ptr->m_FontCacheSize; }
};

template <typename Self>
struct StormReflTypeInfo<EngineSettings>::field_data<2, Self> : public StormReflTypeInfo<EngineSettings>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_FontCacheSize; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_FontCacheSize; }
  void SetDefault() { self.m_FontCacheSize = StormReflTypeInfo<EngineSettings>::GetDefault().m_FontCacheSize; }
};

namespace StormReflFileInfo
{
  struct EngineSettings
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct EngineSettings::type_info<0>
  {
    using type = ::EngineSettings;
  };

}

