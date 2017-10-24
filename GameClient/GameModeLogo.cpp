#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeLogo.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameModeSinglePlayerBots.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeLogo::GameModeLogo(GameContainer & game) :
  GameMode(game)
{

}

GameModeLogo::~GameModeLogo()
{

}

void GameModeLogo::Initialize()
{
  auto & container = GetContainer();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  GetAssets().LoadAsset<TextureAsset>("./Images/stormbrewers_logo.png", "logo");
}

void GameModeLogo::OnAssetsLoaded()
{
  m_Timer.Start();
}

void GameModeLogo::Update()
{
  auto & container = GetContainer();
  container.GetWindow().Update();

  bool timer_allowed = m_Timer.GetTimeSinceStart() > 1.0;
  bool global_loaded = container.AllGlobalResourcesLoaded();

  if (timer_allowed && global_loaded)
  {
    container.SwitchMode(GameModeDef<GameModeMainMenu>{});
    return;
  }
}

void GameModeLogo::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  render_util.SetClearColor(Color(255, 255, 255, 255));
  render_util.Clear();
  
  render_state.EnableBlendMode();

  auto texture = GetAssets().GetTexture("logo");
  if (texture && texture->IsLoaded())
  {
    auto window_size = container.GetWindow().GetSize();
    auto texture_size = texture->GetSize();
   
    render_util.DrawTexturedQuad(window_size / 2 - texture_size / 2, Color(255, 255, 255, 255), texture->GetTexture(), window_size);
  }
}

