#include "pch.h"

#include "AutoAssemblerKinda/AutoAssemblerKinda.h"

#include "ImGuiCTX.h"
#include "ImGuiConfigUtils.h"

#include "ParkourDebugging/ParkourDebuggingPatch.h"
#include "ParkourDebugging/LoggingTheHumanStates.h"
#include "ParkourDebugging/Hack_PickEntityToShoot.h"
#include "AnimationTools/AnimationsLog/AnimationGraphEvaluationLog.h"


class MyHacksContainer_DevExtras
{
public:
    AutoAssembleWrapper<ParkourDebuggingPatch> parkourDebugging;
    AutoAssembleWrapper<EnterHumanStateHook> humanStatesHook;
    AutoAssembleWrapper<AnimGraphEvaluationLogging> animGraphDebugging;
    AutoAssembleWrapper<PickEntityToShoot> pickEntityToShoot;

    void DrawControls()
    {
        ImGui::DrawCheckboxForHack(animGraphDebugging, "动画图调试");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "每当玩家角色开始播放一段动画时，\n"
                "就会向 ImGui 控制台添加一条日志，包含对应的\n"
                "AtomAnimationDataBaseNode 地址、Animation 地址、动画句柄\n"
                "以及文件名（如果已加载句柄字典且句柄可识别——详见“句柄”标签页）。\n"
                "这有助于弄清动画状态切换发生的时机与方式。\n"
                "同一段动画可能在动画图中被多次引用，\n"
                "但如果你在同一游戏会话中使用“将动画图转储为文本文件”功能，\n"
                "并搜索 AtomAnimationDataBaseNode 的地址，\n"
                "就能准确看到涉及哪些状态节点。"
            );
        }
        ImGui::Separator();
        ImGui::DrawCheckboxForHack(humanStatesHook, "记录玩家“人类状态机”日志");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "记录玩家“人类状态机”（HumanStates）的状态树。\n"
                "不同状态包含不同的回调函数，\n"
                "ACUFixes 的许多功能正是借助它们才得以实现。\n"
                "实时观察这棵状态树如何随玩家操作而变化，会很有启发。"
            );
        }
        if (humanStatesHook.IsActive())
        {
            ImGui::SameLine();
            DrawHumanStatesDebugControls();
        }
        ImGui::Separator();
        ImGui::DrawCheckboxForHack(parkourDebugging, "跑酷调试");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "向 ImGui 控制台记录哪些已识别的\n"
                "“跑酷动作”被选中等信息。\n"
                "如果启用了 3D 标记功能，还会可视化\n"
                "这些候选动作的目标位置。"
            );
        }
        ImGui::Separator();
        ImGui::DrawCheckboxForHack(pickEntityToShoot, "手动选择速射目标");
        if (pickEntityToShoot.IsActive())
        {
            RaycastPicker_PickRangedWeaponTarget();
        }
    }
};
std::optional<MyHacksContainer_DevExtras> g_MyHacks_DevExtras;

void DrawHacksControls_DevExtras()
{
    if (g_MyHacks_DevExtras)
    {
        g_MyHacks_DevExtras->DrawControls();
    }
}

void MyVariousHacks_DevExtras_Start()
{
    g_MyHacks_DevExtras.emplace();
}
