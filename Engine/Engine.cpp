
#include "Engine/EngineCommon.h"
#include "Engine/Engine.h"

#include "Foundation/Network/Network.h"

#include <gl3w/gl3w.h>
#include <SDL/SDL.h>

#include <freetype/ft2build.h>
#include FT_FREETYPE_H

#include "Engine/Asset/AssetLoader.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Window/WindowManager.h"
#include "Engine/Time/Time.h"

static bool s_Quit = false;

FT_Library g_FreeType;

bool EngineInit()
{
  NetworkInit();

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
  {
    fprintf(stderr, "Could not start SDL");
    return false;
  }

  if (FT_Init_FreeType(&g_FreeType))
  {
    fprintf(stderr, "Could not start FreeType");
    return false;
  }

  g_AssetLoader.Init();
  g_AudioManager.Init();

  return true;
}

bool EngineRenderInit()
{
  gl3wInit();
  g_TextManager.Init();

  BootstrapContext();

  return true;
}

void EngineUpdate()
{
  g_AssetLoader.ProcessResponses();
  g_TimeManager.Update();

  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      s_Quit = true;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      g_WindowManager.HandleKeyPressMessage(e.key.windowID, e.key.keysym.sym, e.key.keysym.scancode, true);
    }
    else if (e.type == SDL_KEYUP)
    {
      g_WindowManager.HandleKeyPressMessage(e.key.windowID, e.key.keysym.sym, e.key.keysym.scancode, false);
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
      g_WindowManager.HandleMouseButtonPressMessage(e.button.windowID, e.button.button, true);
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
      g_WindowManager.HandleMouseButtonPressMessage(e.button.windowID, e.button.button, false);
    }
    else if (e.type == SDL_WINDOWEVENT)
    {
      if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
      {
        g_WindowManager.SetWindowKeyboardFocused(e.window.windowID, true);
      }
      else if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
      {
        g_WindowManager.SetWindowKeyboardFocused(e.window.windowID, true);
      }
      if (e.window.event == SDL_WINDOWEVENT_ENTER)
      {
        g_WindowManager.SetWindowMouseFocused(e.window.windowID, true);
      }
      else if (e.window.event == SDL_WINDOWEVENT_LEAVE)
      {
        g_WindowManager.SetWindowMouseFocused(e.window.windowID, true);
      }
      else if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
      {
        g_WindowManager.SetWindowSize(e.window.windowID, Vector2(e.window.data1, e.window.data2));
      }
      else if (e.window.event == SDL_WINDOWEVENT_MOVED)
      {
        g_WindowManager.SetWindowPos(e.window.windowID, Vector2(e.window.data1, e.window.data2));
      }
    }
    else if (e.type == SDL_TEXTINPUT)
    {
      g_WindowManager.HandleTextInputCommit(e.text.windowID, e.text.text);
    }
    else if (e.type == SDL_TEXTEDITING)
    {
      g_WindowManager.HandleTextInputComposition(e.edit.windowID, e.edit.text);
    }
  }

  g_WindowManager.UpdateInput();
}

void EngineCleanup()
{
  g_AssetLoader.ShutDown();
  g_AudioManager.ShutDown();
  g_TextManager.ShutDown();

  NetworkShutdown();
}

bool EngineWantsToQuit()
{
  return s_Quit;
}