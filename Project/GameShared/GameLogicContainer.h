#pragma once

struct GameInstanceData;
struct GameInitSettings;
class GameController;
class ServerObjectManager;
class ServerObjectEventSystem;
class GameServerEventSender;
class GameSimulationEventCallbacks;
class GameLogicSystems;
class GameStage;

class GameLogicContainer
{
public:
  GameLogicContainer(
    GameController & game_controller,
    const GameInitSettings & init_settings,
    GameInstanceData & global_data,
    ServerObjectManager & object_manager,
    ServerObjectEventSystem & server_object_event_system,
    GameServerEventSender & server_event_sender,
    GameSimulationEventCallbacks & sim_event_sender,
    GameLogicSystems & systems,
    const GameStage & stage, 
    bool is_authority,
    int & send_timer);

  GameLogicContainer(const GameLogicContainer & rhs) = default;
  GameLogicContainer(GameLogicContainer && rhs) = default;

  GameLogicContainer & operator = (const GameLogicContainer & rhs) = default;
  GameLogicContainer & operator = (GameLogicContainer && rhs) = default;

  GameController & GetGameController();
  const GameInitSettings & GetGameInitSettings();
  GameInstanceData & GetInstanceData();
  ServerObjectManager & GetObjectManager();
  ServerObjectEventSystem & GetServerObjectEventSystem();
  GameServerEventSender & GetEventSender();
  GameSimulationEventCallbacks & GetSimEventCallbacks();
  GameLogicSystems & GetSystems();
  const GameStage & GetStage();
  bool IsAuthority();
  void TriggerImmediateSend();

private:
  GameController & m_GameController;
  const GameInitSettings & m_InitSettings;
  GameInstanceData & m_InstanceData;
  ServerObjectManager & m_ObjectManager;
  ServerObjectEventSystem & m_ObjectEventSystem;
  GameServerEventSender & m_ServerEventSender;
  GameSimulationEventCallbacks & m_SimEventSender;
  GameLogicSystems & m_Systems;
  const GameStage & m_Stage;
  bool m_IsAuthority;
  int & m_SendTimer;
};

