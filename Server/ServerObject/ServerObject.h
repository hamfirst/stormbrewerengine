#pragma once

#include "Foundation/Handle/Handle.h"
#include "Foundation/SkipField/SkipFieldIterator.h"

#include "Server/ServerObject/ServerObjectHandle.h"
#include "Server/ServerObject/ServerObjectRegistrationMacros.h"
#include "Server/ServerObject/ServerObjectEventDispatch.h"
#include "Server/ServerObject/ServerObjectEventSystem.h"

#include "StormRefl/StormReflMetaInfoBase.h"

class ServerObjectManager;
class ServerComponent;
class ServerGameState;

class GameLogicContainer;

class ServerObject
{
public:
  DECLARE_BASE_SERVER_OBJECT;

  ServerObjectHandle GetObjectHandle() const;
  void Destroy(ServerObjectManager & obj_manager);

  virtual czstr GetDefaultEntityBinding();
  virtual czstr GetEntityBinding();

  bool IsDestroyed() const;
  int GetSlotIndex() const;

  int GetLifetime() const;

  template <typename Type>
  NullOptPtr<Type> CastTo()
  {
    if (CastToInternal((uint32_t)Type::TypeIndex))
    {
      return static_cast<Type *>(this);
    }

    return nullptr;
  }

  template <typename EventType>
  void SendEvent(const EventType & ev, GameLogicContainer & game_container)
  {
    TriggerEventHandler(EventType::TypeNameHash, &ev, game_container);
  }

protected:

  void SetEventDispatch(NotNullPtr<ServerObjectEventDispatch> event_dispatch);

private:

  template <typename Type>
  friend class SkipField;

  template <typename ObjectType, typename HandleType, typename ... HandlerArgs>
  friend class EventSystem;

  friend class ServerObjectSystem;
  friend class ServerObjectManager;

  const Handle & GetHandle() const;
  void SetHandle(Handle & handle);

  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

  void TriggerEventHandler(uint32_t event_type, const void * ev, GameLogicContainer & game_container);

private:
  bool m_IsStatic = false;
  int m_TypeIndex = 0;
  int m_SlotIndex = 0;
  int m_FramesAlive = 0;

  SkipFieldIterator m_Iterator;
  Handle m_Handle;
  ServerObjectHandle m_ServerObjectHandle;

  NullOptPtr<ServerObjectEventDispatch> m_EventDispatch = nullptr;
};

template <typename T>
NullOptPtr<T> ServerObjectHandle::ResolveTo(const ServerObjectManager & object_manager)
{
  static_assert(std::is_base_of<ServerObject, T>::value, "Must resolve to server object type");

  auto ptr = Resolve(object_manager);
  if (ptr == nullptr)
  {
    return nullptr;
  }

  if (ptr->CastToInternal((uint32_t)T::TypeIndex))
  {
    return static_cast<T *>(ptr);
  }

  return nullptr;
}

template <>
NullOptPtr<ServerObject> ServerObjectHandle::ResolveTo<ServerObject>(const ServerObjectManager & object_manager);

template <>
struct StormReflTypeInfo<ServerObject>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerObject"; }
  static constexpr auto GetNameHash() { return COMPILE_TIME_CRC32_STR("ServerObject"); }
  static ServerObject & GetDefault() { static ServerObject def; return def; }
};

template <>
struct StormReflFuncInfo<ServerObject>
{
  using MyBase = StormRelfEmptyBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};