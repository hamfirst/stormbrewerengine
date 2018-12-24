#pragma once

#include "Engine/EngineCommon.h"

#include "Foundation/Time/StopWatch.h"

#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptInterface.h"
#include "Foundation/Script/ScriptClass.h"

#include "Runtime/UI/UIResource.h"

#include "StormExpr/StormExprFunctionList.h"

class InputState;
class Window;
class RenderState;
class RenderUtil;

class UIDef;
class UIScriptLoader;
class UIScriptInterface;

class UIClickable;
class UITextInput;

class UIManager
{
public:
  UIManager(Window & container_window);
  ~UIManager();

  void LoadScripts(const Vector2 & screen_size, bool immediate_load = false,
          Delegate<void> && load_complete_callback = {}, Delegate<void, czstr> && error_output = {});
  bool FinishedLoading() const;

  void Update(float delta_time, InputState & input_state, RenderState & render_state);
  void Render(RenderState & render_state, RenderUtil & render_util);

  void Pause();
  void Unpause();

  void GrabMouse(NotNullPtr<UIClickable> clickable);
  void ReleaseMouse(NotNullPtr<UIClickable> clickable);

  ScriptClassRef<UIClickable> AllocateClickable();

  void PushUIDef(const UIDef & def);
  void PushUIDef(const UIResourcePtr & ui);
  void ClearUI();
  ScriptInterface & CreateGameInterface();

  bool Call(czstr name, std::initializer_list<ScriptValue> args, NullOptPtr<ScriptValue> return_val = nullptr);
  void SetGlobal(czstr name, const ScriptValue & value);

  bool HasSelectedElement() const;

protected:

  friend class UIClickable;

  void AddClickableToRoot(const ScriptClassRef<UIClickable> & clickable);
  void RemoveClickableFromRoot(const ScriptClassRef<UIClickable> & clickable);
  void TrashClickable(NotNullPtr<UIClickable> clickable);
  void RemoveDeadClickables();

  void UpdateScriptGlobals(const Vector2 & screen_size);

  void AddToClickableList(NotNullPtr<UIClickable> clickable, NullOptPtr<UIClickable> parent, std::vector<NotNullPtr<UIClickable>> & list);
  void ProcessActiveAreas(float delta_time, InputState & input_state, RenderState & render_state);

private:

  friend class UIScriptInterface;

  Window & m_ContainerWindow;

  Optional<ScriptClass<UIClickable>> m_ClickableClass;
  Optional<ScriptClass<UITextInput>> m_TextInputClass;

  Optional<ScriptState> m_ScriptState;
  Optional<ScriptInterface> m_UIInterfaceObject;
  Optional<ScriptInterface> m_GameInterfaceObject;

  std::unique_ptr<UIScriptLoader> m_ScriptLoader;
  std::unique_ptr<UIScriptInterface> m_ScriptInterface;

  std::vector<ScriptClassRef<UIClickable>> m_RootClickables;
  std::vector<NotNullPtr<UIClickable>> m_DeadClickables;

  std::string m_CleanupFunc;
  Vector2 m_PrevCursorPos = Vector2(-10000, -10000);

  NotNullPtr<UIClickable> m_GrabbedMouseClickable = nullptr;
  bool m_HasSelectedElement = false;

  StopWatch m_UpdateTimer;
  bool m_Paused = false;
  bool m_Destroying = false;
};

