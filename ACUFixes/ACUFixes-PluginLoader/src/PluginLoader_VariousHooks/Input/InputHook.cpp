#include "pch.h"

#include "Hack_GameRawInputHook.h"
#include "ACU/InputContainer.h"
#include "Common_Plugins_impl/InputHooks.h"
#include "base.h"

ACU::Input::InputHooks g_InputHooks;

void UpdateImGuiMouseInput(MouseState& mouseState)
{
    // When going Fullscreen (but not Borderless Fullscreen)
    // the `ImGui_ImplWin32_WndProcHandler()` function doesn't receive most mouse messages:
    // WM_MOUSEWHEEL and mouse button events such as WM_LBUTTONDOWN.
    // In fact, when in Fullscreen, the WndProc of the main window doesn't receive
    // these messages either.
    // WM_MOUSEMOVE is ok, go figure.
    // This means that the ImGui menu reacts to mouse move (buttons are highlighted on hover,
    // for example), but not to clicks, drags etc.
    // Somehow (by using an additional WndProc in some hidden window?), the game is still aware
    // of the mouse button updates and I use the data available in the Raw Input Hook
    // to update the mouse state variables in `ImGuiIO`.
    if (ImGui::GetCurrentContext() == NULL)
        return;

    ImGuiIO& io = ImGui::GetIO();
    HWND hwnd = Base::Data::hWindow;

    for (uint8 button = 0; button < std::size(mouseState.mouseButtonStates); button++)
    {
        uint8 buttonState = mouseState.mouseButtonStates[button];
        const bool isMouseButtonUp = buttonState == 0;
        if (isMouseButtonUp)
        {
            io.MouseDown[button] = false;
            if (!ImGui::IsAnyMouseDown() && ::GetCapture() == hwnd)
                ::ReleaseCapture();
            continue;
        }
        const bool isMouseButtonDown = buttonState == 0x80;
        if (isMouseButtonDown)
        {
            if (!ImGui::IsAnyMouseDown() && ::GetCapture() == NULL)
                ::SetCapture(hwnd);
            io.MouseDown[button] = true;
        }
    }

    // `io.MouseWheel` is accumulated. This is slightly (for now) problematic
    // because in Borderless Fullscreen (when WM_MOUSEWHEEL _is_ received)
    // it gets accumulated twice: once here, once in ImGui_ImplWin32_WndProcHandler.
    // Better than not working in Fullscreen at all, I guess.
    io.MouseWheel += (float)(mouseState.mouseWheelDeltaInt) / (float)WHEEL_DELTA;
}
#include "ImGuiConsole.h"
std::pair<bool, bool> IsNeedToBlockGameInput()
{
    ImGuiIO& io = ImGui::GetIO();
    const bool blockMouse = io.WantCaptureMouse;
    const bool blockKeyboard = io.WantCaptureKeyboard;
    return { blockMouse, blockKeyboard };
}

extern uint64_t g_lastWmMouseMoveTimestamp_ms;
static bool s_wasFeedingMousePosFromDeltas = false;

// On some systems, in exclusive Fullscreen the WndProc doesn't receive
// WM_MOUSEMOVE either (only keyboard messages arrive), so `io.MousePos`
// never updates and the ImGui cursor is stuck.
// The game's own MouseState still receives valid per-frame deltas,
// so while the menu is capturing the mouse and no WM_MOUSEMOVE has been
// seen recently, accumulate those deltas into `io.MousePos` ourselves.
// If WM_MOUSEMOVE flows normally (Borderless Windowed), this does nothing.
void FeedMousePosFromDeltas(MouseState& mouseState)
{
    ImGuiIO& io = ImGui::GetIO();
    if (!io.WantCaptureMouse)
    {
        s_wasFeedingMousePosFromDeltas = false;
        return;
    }
    if (GetTickCount64() - g_lastWmMouseMoveTimestamp_ms < 250)
        return;
    if (!s_wasFeedingMousePosFromDeltas)
    {
        POINT screenPos {};
        if (::GetCursorPos(&screenPos) && ::ScreenToClient(Base::Data::hWindow, &screenPos))
        {
            io.AddMousePosEvent((float)screenPos.x, (float)screenPos.y);
            s_wasFeedingMousePosFromDeltas = true;
        }
        return;
    }
    const float displayWidth = io.DisplaySize.x;
    const float displayHeight = io.DisplaySize.y;
    if (displayWidth <= 0.f || displayHeight <= 0.f)
        return;
    const float newX = std::max(0.f, std::min(displayWidth - 1.f, io.MousePos.x + (float)mouseState.mouseDeltaInt.x));
    const float newY = std::max(0.f, std::min(displayHeight - 1.f, io.MousePos.y + (float)mouseState.mouseDeltaInt.y));
    io.AddMousePosEvent(newX, newY);
}

void GameRawInputHook_ImGuiLayer(InputContainerBig& inpCont)
{
    if (!Base::Data::IsImGuiInitialized)
    {
        return;
    }
    UpdateImGuiMouseInput(inpCont.mouseState);
    FeedMousePosFromDeltas(inpCont.mouseState);
    auto [blockMouse, blockKeyboard] = IsNeedToBlockGameInput();
    if (blockMouse)
    {
        inpCont.mouseState.mouseDeltaInt = inpCont.mouseState.mouseDeltaInt_PrevFrame = { 0, 0 };
        inpCont.mouseState.mouseWheelDeltaInt = inpCont.mouseState.mouseWheelDeltaInt_PrevFrame = 0;
        std::memset(inpCont.mouseState.mouseButtonStates, 0, sizeof(inpCont.mouseState.mouseButtonStates));
    }
    if (blockKeyboard)
    {
        std::memset(inpCont.isPressed_byScancode, 0, sizeof(inpCont.isPressed_byScancode));
    }
}
class PluginLoader_UpdateInputHooks
{
public:
    static void Update(InputContainerBig& inpCont)
    {
        g_InputHooks.UpdateEvolvedKeyStates(inpCont);
    }
};
void BeforeActionKeysAreUpdatedFromScancodes_RunRawInputHooks(AllRegisters* params)
{
    InputContainerBig& inpBig = *(InputContainerBig*)params->rbx_;
    PluginLoader_UpdateInputHooks::Update(inpBig);
    GameRawInputHook_ImGuiLayer(inpBig);
}
#include "ACU_DefineNativeFunction.h"
DEFINE_GAME_FUNCTION(GetCursorPos_P, 0x14273B3F0, void, __fastcall, (InputContainerBig* a1));
void GetCursorPos_SkipIfCapturingMouse(AllRegisters* params)
{
    auto [blockMouse, blockKeyboard] = IsNeedToBlockGameInput();
    if (blockMouse) return;
    GetCursorPos_P((InputContainerBig*)params->rcx_);
}
GameRawInputHook::GameRawInputHook()
{
    uintptr_t beforeActionKeysAreUpdatedFromScancodes = 0x14273BC64;
    PresetScript_CCodeInTheMiddle(
        beforeActionKeysAreUpdatedFromScancodes, 6,
        BeforeActionKeysAreUpdatedFromScancodes_RunRawInputHooks, RETURN_TO_RIGHT_AFTER_STOLEN_BYTES, true);


    uintptr_t GetCursorPos_Parent_Callsite = 0x14273BDF0;
    PresetScript_CCodeInTheMiddle(GetCursorPos_Parent_Callsite, 5,
        GetCursorPos_SkipIfCapturingMouse, RETURN_TO_RIGHT_AFTER_STOLEN_BYTES, false);
}
