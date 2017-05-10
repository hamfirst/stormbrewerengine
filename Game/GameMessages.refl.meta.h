#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameMessages.refl.h"
#include "Game/GameSimulation.refl.meta.h"


template <>
struct StormReflTypeInfo<FromServerMessage>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FromServerMessage"; }
  static constexpr auto GetNameHash() { return 0x038F16E6; }
  static FromServerMessage & GetDefault() { static FromServerMessage def; return def; }
};

template <>
struct StormReflTypeInfo<PongMessage>
{
  using MyBase = FromServerMessage;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PongMessage"; }
  static constexpr auto GetNameHash() { return 0x9936163C; }
  static PongMessage & GetDefault() { static PongMessage def; return def; }
};

template <>
struct StormReflTypeInfo<ToServerMessage>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ToServerMessage"; }
  static constexpr auto GetNameHash() { return 0x4C3A63B8; }
  static ToServerMessage & GetDefault() { static ToServerMessage def; return def; }
};

template <>
struct StormReflTypeInfo<PingMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PingMessage"; }
  static constexpr auto GetNameHash() { return 0x9428667B; }
  static PingMessage & GetDefault() { static PingMessage def; return def; }
};

template <>
struct StormReflTypeInfo<JoinGameMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 3 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "JoinGameMessage"; }
  static constexpr auto GetNameHash() { return 0xF8762C60; }
  static JoinGameMessage & GetDefault() { static JoinGameMessage def; return def; }
};

template <>
struct StormReflTypeInfo<JoinGameMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &JoinGameMessage::m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<JoinGameMessage>::field_data<0 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<JoinGameMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<JoinGameMessage>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<JoinGameMessage>::field_data_static<1 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &JoinGameMessage::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<JoinGameMessage>::field_data<1 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<JoinGameMessage>::field_data_static<1 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<JoinGameMessage>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<JoinGameMessage>::field_data_static<2 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = GameInitSettings; // GameInitSettings
  static constexpr auto GetName() { return "m_Settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136974EB; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &JoinGameMessage::m_Settings; }
};

template <typename Self>
struct StormReflTypeInfo<JoinGameMessage>::field_data<2 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<JoinGameMessage>::field_data_static<2 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInitSettings> & Get() { return self.m_Settings; }
  std::add_const_t<std::remove_reference_t<GameInitSettings>> & Get() const { return self.m_Settings; }
  void SetDefault() { self.m_Settings = StormReflTypeInfo<JoinGameMessage>::GetDefault().m_Settings; }
};

template <>
struct StormReflTypeInfo<SimEventBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SimEventBase"; }
  static constexpr auto GetNameHash() { return 0x676A7295; }
  static SimEventBase & GetDefault() { static SimEventBase def; return def; }
};

template <>
struct StormReflTypeInfo<PlaceholderEvent>
{
  using MyBase = SimEventBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlaceholderEvent"; }
  static constexpr auto GetNameHash() { return 0xB61745A6; }
  static PlaceholderEvent & GetDefault() { static PlaceholderEvent def; return def; }
};

namespace StormReflFileInfo
{
  struct GameMessages
  {
    static const int types_n = 7;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameMessages::type_info<0>
  {
    using type = ::FromServerMessage;
  };

  template <>
  struct GameMessages::type_info<1>
  {
    using type = ::PongMessage;
  };

  template <>
  struct GameMessages::type_info<2>
  {
    using type = ::ToServerMessage;
  };

  template <>
  struct GameMessages::type_info<3>
  {
    using type = ::PingMessage;
  };

  template <>
  struct GameMessages::type_info<4>
  {
    using type = ::JoinGameMessage;
  };

  template <>
  struct GameMessages::type_info<5>
  {
    using type = ::SimEventBase;
  };

  template <>
  struct GameMessages::type_info<6>
  {
    using type = ::PlaceholderEvent;
  };

}

