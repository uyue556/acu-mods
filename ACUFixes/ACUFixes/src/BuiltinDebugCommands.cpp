#include "pch.h"

#include "ACU/CLAssassin.h"
#include "ACU/DebugCommandsHolder.h"

DebugCommandsHolder* GetCheatsHolder()
{
    CLAssassin* cla = CLAssassin::GetSingleton();
    if (!cla) { return nullptr; }
    return cla->cheatCodes;
}
void DrawBuiltinDebugCommands()
{
    ImGui::Text(
        "其中大多数没有任何效果。\n"
        "警告：“Nuke enemies”/“Nuke allies”（核爆敌人/友军）会导致游戏崩溃。"
    );
    DebugCommandsHolder* cheatsHolder = GetCheatsHolder();
    if (!cheatsHolder) { return; }
    static std::string buf;
    buf.reserve(200);
    for (int i = 0; i < cheatsHolder->arrDebugCommands.size; i++)
    {
        DebugCommand* cheat = cheatsHolder->arrDebugCommands[i];
        buf.clear();
        buf.append(std::to_string(i));
        if (cheat->textDesc)
        {
            buf += ": ";
            buf += cheat->textDesc;
        }
        if (ImGui::Button(buf.c_str()))
        {
            constexpr int mostCommandsSeemToRequireTheFirstParameterToBe1 = 1;
            cheat->fnExecute(mostCommandsSeemToRequireTheFirstParameterToBe1, cheatsHolder);
        }
    }
}
