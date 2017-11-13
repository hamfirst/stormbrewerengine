#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

#include "Game/GameNetworkData.refl.h"
#include "Game/GameNetworkExternals.refl.h"
#include "Game/GameNetworkEvents.refl.h"

#include "Game/GameNetworkSettings.h"
#include "Runtime/ServerObject/ServerObjectManager.h"
#include "Runtime/ServerObject/ServerObjectSerialize.h"

struct GameFullState
{
  NET_REFL;
  STORM_REFL_NODEFAULT;

  ServerObjectManager m_ServerObjectManager;
  GameInstanceData m_InstanceData;

};

struct GameStateStagingPlayer
{
  NET_REFL;
  std::string m_UserName;

#ifdef NET_USE_READY
  bool m_Ready = false;
#endif

  NetRangedNumber<int, -1, kMaxTeams - 1> m_Team = 0;
};

struct GameStateStaging
{
  NET_REFL;
  NetSparseList<GameStateStagingPlayer, kMaxPlayers> m_Players;
  GameInitSettings m_Settings;
  NetRangedNumber<int, 0, 255> m_Countdown;
  int m_WaitTimer;
};

struct GameStateLoadingPlayer
{
  NET_REFL;
  std::string m_UserName;
  bool m_Loaded = false;
  NetRangedNumber<int, -1, kMaxTeams - 1> m_Team = 0;
};

struct GameStateLoading
{
  NET_REFL;
  NetSparseList<GameStateLoadingPlayer, kMaxPlayers> m_Players;
};

#if NET_MODE == NET_MODE_GGPO

struct GameHistoryInput
{
  NET_REFL;
  NetRangedNumber<int, 0, kMaxPlayers> m_PlayerIndex;
  int m_Frame;
  ClientInput m_Input;
};

struct GameHistoryEvent
{
  NET_REFL;
  NetRangedNumber<int, 0, kMaxPlayers> m_PlayerIndex;
  int m_Frame;
  NetPolymorphic<ClientNetworkEvent> m_Event;
};

struct GameHistoryClientEvent
{
  NET_REFL;
  int m_Frame;
  NetPolymorphic<ClientNetworkEvent> m_Event;
};


struct GameHistoryExternal
{
  NET_REFL;
  int m_Frame;
  NetPolymorphic<GameNetworkExternalEvent> m_Event;
};

struct GameHistoryAuthEvent
{
  NET_REFL;
  int m_Frame;
  NetPolymorphic<ServerAuthNetworkEvent> m_Event;
};

struct GameHistoryClientLocal
{
  NET_REFL;
  int m_Frame;
  ClientLocalData m_Data;
};

struct GameGGPOServerGameState
{
  NET_REFL;
  STORM_REFL_NODEFAULT;

  int m_AckFrame;
  int m_ServerFrame;
  int m_EventStartFrame;

  std::shared_ptr<GameFullState> m_State;

  NetOptional<NetArrayList<GameHistoryInput, 1023>> m_Inputs;
  NetOptional<NetArrayList<GameHistoryEvent, 1023>> m_Events;
  NetOptional<NetArrayList<GameHistoryExternal, 1023>> m_Externals;
  NetOptional<NetArrayList<GameHistoryClientLocal, 1023>> m_LocalData;
  NetOptional<NetArrayList<GameHistoryAuthEvent, 1023>> m_ServerAuthEvents;
};

struct GameGGPOClientUpdate
{
  NET_REFL;

  int m_AckFrame;
  int m_ClientFrame;
  NetOptional<NetArrayList<ClientAuthData, 127>> m_Inputs;
  NetOptional<NetArrayList<GameHistoryClientEvent, 127>> m_Events;
};

#endif

