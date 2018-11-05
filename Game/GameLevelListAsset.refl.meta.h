#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameLevelListAsset.refl.h"


template <>
struct StormReflTypeInfo<GameLevelListAsset>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameLevelListAsset"; }
  static constexpr auto GetNameHash() { return 0x6F8BA414; }
  static GameLevelListAsset & GetDefault() { static GameLevelListAsset def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameLevelListAsset *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameLevelListAsset *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameLevelListAsset *>(ptr);
    if(typeid(GameLevelListAsset).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameLevelListAsset *>(ptr);
    if(typeid(GameLevelListAsset).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameLevelListAsset>::field_data_static<0>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_Levels"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD21533D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameLevelListAsset::m_Levels; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLevelListAsset *>(obj); return &ptr->m_Levels; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLevelListAsset *>(obj); return &ptr->m_Levels; }
};

template <typename Self>
struct StormReflTypeInfo<GameLevelListAsset>::field_data<0, Self> : public StormReflTypeInfo<GameLevelListAsset>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_Levels; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_Levels; }
  void SetDefault() { self.m_Levels = StormReflTypeInfo<GameLevelListAsset>::GetDefault().m_Levels; }
};

namespace StormReflFileInfo
{
  struct GameLevelListAsset
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameLevelListAsset::type_info<0>
  {
    using type = ::GameLevelListAsset;
  };

}

