#include "pch.h"


#include "MyLog.h"
#include "MainConfig.h"
#include "ImGuiCTX.h"

#include "AutoAssemblerKinda/AutoAssemblerKinda.h"

#include "VariousPatches/Hack_EnterWindowsWhenRisPressed.h"
#include "VariousPatches/Hack_SlowMenacingWalkAndAutowalk.h"
#include "VariousPatches/Hack_CycleEquipmentWhenScrollingMousewheel.h"
#include "VariousPatches/Hack_ModifyAimingFOV.h"
#include "VariousPatches/Hack_DontForceUnsheatheWhenInDisguise.h"
#include "VariousPatches/Hack_CrouchFix.h"
#include "VariousPatches/Hack_ReworkedTakeCover.h"
#include "VariousPatches/Hack_BreakfallAndLedgeGrab.h"
#include "VariousPatches/Hack_EasierTurnWhenSwinging.h"
#include "VariousPatches/Hack_AimFromPeaks.h"
#include "VariousPatches/Hack_NoMoreFailedBombThrows.h"
#include "VariousPatches/Hack_MoreResponsiveBombQuickDrop.h"
#include "VariousPatches/Hack_ReloadRangedWeaponsWhenRefillAllInShop.h"
#include "VariousPatches/Hack_MoreReliableQuickshot.h"
#include "VariousPatches/Hack_DontRandomlyTurn180Degrees.h"
#include "VariousPatches/Hack_NoWaitForUnsafeEject.h"
#include "VariousPatches/Hack_AllowCustomizeEquipment.h"
#include "VariousPatches/Hack_GunRange.h"
#include "VariousPatches/Hack_UnequipPistol.h"
#include "VariousPatches/Hack_CorrectLandingHeightOutOfVault.h"

#include "VariousPatches/Hack_LookbehindButton.h"
#include "VariousPatches/Hack_WhistleAbility.h"
#include "VariousPatches/Hacks_VariousExperiments.h"

#include "VariousPatches/Cheat_BatlampOfFranciade.h"
#include "VariousPatches/Cheat_PretendYoureInFranciade.h"
#include "VariousPatches/Cheat_Health.h"
#include "VariousPatches/Cheat_Ammo.h"
#include "VariousPatches/Cheat_DisguiseUpgrades.h"

#include "VariousPatches/Request_Spindescent.h"
#include "VariousPatches/Request_FreezeFOV.h"

void DrawSlowMotionControls();
void DrawSlowMotionTrickControls();
void DrawHoodControls();

#include "ImGuiConfigUtils.h"
class MyHacks
{
public:
    AutoAssembleWrapper<EnterWindowWhenRisPressed> enterWindowsByPressingAButton;
    AutoAssembleWrapper<AllowSlowMenacingWalkAndAutowalk> menacingWalkAndAutowalk;
    AutoAssembleWrapper<ModifyConditionalFOVs> changeZoomLevelsWhenAimingBombs;
    AutoAssembleWrapper<InputInjection_CycleEquipmentWhenScrollingMousewheel> cycleEquipmentUsingMouseWheel;
    AutoAssembleWrapper<DontUnsheatheLikeAnIdiotWhileInDisguise> dontUnsheatheWhenInDisguise;
    AutoAssembleWrapper<CrouchFix> slightlyMoreResponsiveCrouch;
    AutoAssembleWrapper<ReworkedTakeCover> takingCoverIsLessSticky;
    AutoAssembleWrapper<LookbehindButton> lookbehindButton;
    AutoAssembleWrapper<BreakfallAndLedgeGrab> breakfallAndCatchLedgeByPressingE;
    AutoAssembleWrapper<EasierTurnWhenSwinging> easierTurnWhenSwingingOnAHorizontalBar;
    AutoAssembleWrapper<MoreSituationsToDropBomb> moreSituationsToDropBombs;
    AutoAssembleWrapper<AimFromPeaks> aimBombsFromPeaks;
    AutoAssembleWrapper<NoMoreFailedBombThrows> noMoreImaginaryBombThrows;
    AutoAssembleWrapper<DontRandomlyTurn180Degrees> dontRandomlyTurn180degrees;
    AutoAssembleWrapper<ReloadRangedWeaponsWhenRefillAllInShop> automaticallyReloadWeaponsWhenRefillAllInShops;
    AutoAssembleWrapper<MoreReliableQuickshot> moreReliableQuickshot;
    AutoAssembleWrapper<NoWaitForUnsafeEject> noWaitForUnsafeEject;
    AutoAssembleWrapper<AllowCustomizeEquipment> allowCustomizeEquipmentOnLedges;
    AutoAssembleWrapper<GuillotineGunRange> guillotineGunRange;
    AutoAssembleWrapper<UnequipPistol> allowUnequipPistol;
    AutoAssembleWrapper<CorrectLandingHeightOutOfVault> correctLandingHeightOutOfVault;

    // Unused and unfinished
    AutoAssembleWrapper<PlayWithFOV> fovGames;
    AutoAssembleWrapper<PlayWithBombAimCameraTracker2> bombAimExperiments2;
    AutoAssembleWrapper<WhistleAbility> whistleAbility;
    AutoAssembleWrapper<BetterAimingFromBehindCover> moreConsistentAimBombFromBehindCover;

    void DrawControls()
    {
        if (ImGui::Button("保存配置文件"))
        {
            WriteConfig(g_Config);
            MainConfig::WriteToFile();
        }
        //ImGui::DrawCheckboxForHack(whistleAbility, "Whistle ability");
        //if (ImGui::IsItemHovered())
        //{
        //    ImGui::SetTooltip("Press Y to _try_to_ attract nearby guards' attention. Very unfinished.");
        //}
        //WhistleAbilityAttempt_ImGuiControls(whistleAbility.IsActive());
        ImGui::DrawCheckboxForHack(enterWindowsByPressingAButton, "按键进入附近的窗户");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "攀墙时按指定键（默认 R，同《枭雄》）可进入附近窗户。\n"
                "站在地面时也可进入附近的藏身点（带帘衣柜）。"
            );
        }
        if (enterWindowsByPressingAButton.IsActive())
        {
            ImGuiCTX::Indent _indent;
            ImGui::Checkbox("同时进入附近的藏身衣柜", &g_Config.hacks->enterWindowsByPressingAButton->alsoEnterNearbyHidespotClosets.get());
            bool isHotkeyChanged = ImGui::DrawEnumPicker(
                "进入窗户按键",
                g_Config.hacks->enterWindowsByPressingAButton->enterWindowsButton.get(),
                ImGuiComboFlags_HeightLarge);
        }
        ImGui::DrawCheckboxForHack(menacingWalkAndAutowalk, "启用自动行走与缓慢威慑步");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "CapsLock 切换缓慢威慑步；\n"
                "朝任意方向行走时按一下自动行走键，然后松开方向键，\n"
                "亚诺会继续朝原方向行走。\n"
                "或者：站定 → 按一下自动行走键 → 一秒内开始行走并松开。"
            );
        }
        if (menacingWalkAndAutowalk.IsActive())
        {
            ImGuiCTX::Indent _indent;
            bool isHotkeyChanged = ImGui::DrawEnumPicker(
                "自动行走按键",
                g_Config.hacks->menacingWalkAndAutowalk->autowalkButton.get(),
                ImGuiComboFlags_HeightLarge);
        }
        ImGui::DrawCheckboxForHack(moreSituationsToDropBombs, "更多情况下可投掷炸弹（如跳跃中），请阅读说明");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "允许在更多情况下快速投掷炸弹：跳跃中、悬挂在墙上、\n"
                "暗杀中、藏身柜中、单杠摆荡时等。\n"
                "由于会播放投掷动画（至少涉及左臂），部分情况下动作可能显得不自然\n"
                "（如刺杀中途扔炸弹、单臂悬挂时），无法保证所有动画都无缝衔接。"
            );
        }
        if (moreSituationsToDropBombs.IsActive())
        {
            ImGuiCTX::Indent _ind;
            ImGui::Checkbox("战斗中也更灵敏", &g_Config.hacks->moreSituationsToDropBombs->alsoMoreResponsiveInCombat.get());
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip(
                    "战斗中允许在做其他动作时投掷炸弹，\n"
                    "如招架、翻滚、处决过程中。"
                );
            }
        }
        ImGui::DrawCheckboxForHack(moreReliableQuickshot, "更可靠的速射，请阅读说明");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "允许从高处和 V 形结构（旗杆、树木等）速射腕弩和手枪。\n"
                "同时修复：收近战武器时尝试速射手枪会变成装填（即使弹匣已满）。\n"
                "并有望修复一个罕见的严重速射 bug：速射后立即跑酷会导致\n"
                "无法切换远程武器、在边缘无法行走或转身。\n"
                "建议同时启用“减少速射限制”选项。"
            );
        }
        if (moreReliableQuickshot.IsActive())
        {
            ImGuiCTX::Indent _indent;
            ImGui::Checkbox("减少速射限制，请阅读说明", &g_Config.hacks->moreReliableQuickshot->lessQuickshotRestrictions.get());
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip(
                    "通常速射很容易被打断：撞到桌子、从桌上走下、甚至只是撞上未攀爬的墙都会取消动画。\n"
                    "此补丁移除大部分打断情况，例如滑过桌面时也能射击。\n"
                    "若启用“更多情况下可投掷炸弹”，则大多数此类情况下也可速射，\n"
                    "如跳跃中、翻滚中、甚至悬挂在墙上时。\n"
                    "主要适用于手枪和腕弩——悬挂时用步枪等双手武器射击没有意义。\n"
                    "遗憾：仍无法从边缘射击步枪。\n"
                    "注意：与主要只用左臂的投弹不同，速射动画涉及躯干，\n"
                    "因此更容易出现动作违和（如下半身翻滚而上半身保持速射姿态）。\n"
                    "请自行尝试并判断效果。"
                );
            }
        }
        ImGui::DrawCheckboxForHack(changeZoomLevelsWhenAimingBombs, "瞄准炸弹时改变缩放级别");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "瞄准炸弹和断头台枪时增大 FOV。\n"
                "瞄准炸弹时按鼠标右键拉近视角。"
            );
        }
        ImGui::DrawCheckboxForHack(cycleEquipmentUsingMouseWheel, "使用滚轮切换装备");
        ImGui::DrawCheckboxForHack(dontUnsheatheWhenInDisguise, "伪装状态下不拔出武器");
        ImGui::DrawCheckboxForHack(slightlyMoreResponsiveCrouch, "下蹲按键响应更灵敏");
        ImGui::DrawCheckboxForHack(takingCoverIsLessSticky, "掩体进出不再粘滞");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "默认仅在刚按下掩体键（空格）时尝试进入掩体。\n"
                "启用后按住空格期间（低姿态下）会持续尝试进入掩体。\n"
                "另外更容易向远离方向脱离掩体；\n"
                "到达掩体边缘时会离开掩体而非探头绕角。"
            );
        }
        ImGui::DrawCheckboxForHack(breakfallAndCatchLedgeByPressingE, "更可靠的受身与抓取边缘");
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "失控坠落时（如高空跳跃后手臂乱挥、爬墙被击落），\n"
                "按住“跑酷向下/互动”键（默认 E）可抓住面前最近的边缘。\n"
                "同时按住方向键可朝其他方向抓取（如果附近有）。"
            );
        }
        ImGui::DrawCheckboxForHack(easierTurnWhenSwingingOnAHorizontalBar, "单杠摆荡时更容易转向");
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(
                "跳上单杠准备摆荡时按住 冲刺+后退，\n"
                "亚诺会变向回荡。"
            );
        }
        ImGui::DrawCheckboxForHack(aimBombsFromPeaks, "可从“顶点”瞄准炸弹（竖管、尖塔等）");
        ImGui::DrawCheckboxForHack(noMoreImaginaryBombThrows, "不再出现空扔炸弹");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "有时瞄准并释放炸弹后播放了投掷动画，却没有炸弹飞出？\n"
                "这不应再发生了。"
            );
        }
        ImGui::DrawCheckboxForHack(dontRandomlyTurn180degrees, "不再随机原地转 180 度");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "蹲下潜行时小幅移动，角色却瞬间凭空转 180 度？\n"
                "此补丁消除了至少一个导致该问题的原因。"
            );
        }
        ImGui::DrawCheckboxForHack(automaticallyReloadWeaponsWhenRefillAllInShops, "商店使用“全部补充”时自动装填武器");
        DrawHoodControls();
        ImGui::DrawCheckboxForHack(noWaitForUnsafeEject, "不安全蹬墙反跳无需等待");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "某些位置执行不安全的墙面后跳时，游戏通常要求停止移动 1 秒后才能进行。\n"
                "此补丁移除了该等待时间。"
            );
        }
        ImGui::DrawCheckboxForHack(allowCustomizeEquipmentOnLedges, "坐在边缘时允许打开装备自定义");
        ImGui::DrawCheckboxForHack(guillotineGunRange, "断头台枪速射距离略微增加");
        //ImGui::DrawCheckboxForHack(preventAutomaticReequipPistol, "Don't automatically reequip the pistol after switching from a rifle");
        //if (ImGui::IsItemHovered())
        //{
        //    ImGui::SetTooltip(
        //        "If you want to play without the pistol equipped,"
        //        "this is not as good as an \"Unequip\" button, but it's something."
        //    );
        //}
        ImGui::DrawCheckboxForHack(allowUnequipPistol, "允许卸下手枪");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "前往 暂停菜单 → 角色自定义 → 装备配置 → 武器 → 手枪，\n"
                "选中当前装备的手枪（黄色高亮），按 回车/装备 即可卸下。"
            );
        }
        ImGui::DrawCheckboxForHack(correctLandingHeightOutOfVault, "修正翻越后的落地高度");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "特定情况下小翻越后亚诺会出现严重的踉跄。\n"
                "此补丁应能修复该 bug。"
            );
        }
        ImGui::DrawCheckboxForHack(lookbehindButton, "向后看按键");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "按下热键时镜头转向身后。\n"
                "警告：瞄准断头台枪时无效。"
            );
        }
        if (lookbehindButton.IsActive())
        {
            ImGuiCTX::Indent _ind;
            ImGui::DrawEnumPicker("向后看热键", g_Config.hacks->lookbehindButton->hotkey.get(), ImGuiComboFlags_HeightLarge);
        }
        DrawSlowMotionTrickControls();
        if (g_Config.developmentExtras->showDevelopmentExtras)
        {
            if (ImGuiCTX::TreeNode _header{ "未完成且无用的补丁" })
            {
                // This is one of the useless experimental hacks, and has some severe stuttering,
                // but only _sometimes_ for some reason.
                //ImGui::DrawCheckboxForHack(fovGames, "Play with FOV");
                ImGui::DrawCheckboxForHack(bombAimExperiments2, "炸弹瞄准实验2");
                ImGui::DrawCheckboxForHack(moreConsistentAimBombFromBehindCover, "掩体外瞄准炸弹条件略放宽");
                if (ImGui::IsItemHovered())
                {
                    ImGui::SetTooltip(
                        "有时想绕角落扔炸弹，角色却因未贴紧掩体边缘而离开墙壁，\n"
                        "结果炸弹瞄向了墙而不是角落。此补丁应能减少这类情况。\n"
                        "但目前部分位置反而会更糟。"
                    );
                }
            }
        }
        ImGui::Separator();
        ImGui::Text("作弊");
        ImGui::Separator();
        DrawCheatsControls();
        ImGui::Separator();
        if (ImGuiCTX::TreeNode _{ "个人需求" })
        {
            DrawPersonalRequestsControls();
        }
    }
    void DrawCheatsControls()
    {
        {
            ImGui::DrawCheckboxForHack(batlampOfFranciade, "允许在户外使用圣丹尼斯之首");
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip(
                    "启用后请阅读其选项。"
                );
            }
            if (batlampOfFranciade.IsActive())
            {
                DrawBatlampControls();
            }
            Cheat_Health_DrawImGui();
            ImGui::DrawCheckboxForHack(dontDecreaseRemainingAmmo, "无限弹药");
            if (ImGuiCTX::TreeNode _disguiseUpgradesSection{ "伪装增强" })
            {
                ImGui::DrawCheckboxForHack(disableDisguiseCooldown, "禁用伪装冷却");
                ImGui::DrawCheckboxForHack(unbreakableDisguise, "伪装不失效");
                if (ImGui::IsItemHovered())
                {
                    ImGui::SetTooltip(
                        "伪装会让敌人“看不见”你，这让“伪装不失效”在正常游戏中相当无聊。\n"
                        "如果只想借用他人外观，可取消勾选“对敌人隐身”，伪装就不会阻止侦测。\n"
                        "另外若想穿着伪装战斗，可能还需禁用“伪装状态下不拔出武器”。"
                    );
                }
                ImGui::DrawCheckboxForHack(disguiseDoesntMakeYouInvisible, "启用后伪装不会让你对敌人隐身");
            }
            Cheat_Invisibility_DrawImGui();
            ImGui::DrawCheckboxForHack(pretendYoureInFranciade, "假装身处弗朗西亚德");
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip(
                    "例如可将提灯（含魔法道具圣丹尼斯之首）带入巴黎。\n"
                    "启用前建议备份存档。\n"
                    "副作用至少包括部分音效缺失。"
                );
            }
            DrawSlowMotionControls();
        }
    }
    void DrawPersonalRequestsControls()
    {
        ImGui::DrawCheckboxForHack(freezeFOV, "冻结全局 FOV");
        if (freezeFOV.IsActive())
        {
            DrawFreezeFOVControls();
        }
        ImGui::DrawCheckboxForHack(parkourHelpers, "跑酷辅助");
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(
                "应玩家要求让一些炫酷跑酷动作更容易触发。\n"
                "这些并非修复，未必适合所有人，但可能很有趣。"
            );
        }
        if (parkourHelpers.IsActive())
        {
            ImGuiCTX::Indent _ind;
            ImGui::Checkbox("旋转下降辅助", &g_Config.personalRequests->parkourHelper->spinningDescentHelper.get());
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip(
                    "简述：摆荡时按住 冲刺+前进+跑酷向下，旋转下降更容易触发。\n"
                    "这是 E3 演示中出现过的稀有动作：空中转体 270 度后抓缘。\n"
                    "此补丁让摆荡中使用跑酷向下时优先触发旋转下降（忽略其他跑酷动作）。\n"
                    "并非每次都能成功，有时动作可能显得突兀。未在多人模式测试。"
                );
            }
            ImGui::Checkbox("俯冲辅助", &g_Config.personalRequests->parkourHelper->diveHelper->isActive.get());
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip(
                    "按住新热键（默认鼠标侧键5）时，俯冲动作获得比旋转下降更高的优先级\n"
                    "（“俯冲”是一种高姿态跳跃，落到单杠/绳索/挑檐上双手悬挂、双脚悬空）。\n"
                    "其他输入仍然有效：目标横杠近且低于你时按 冲刺+跑酷向下+前进+俯冲键；\n"
                    "近且略高或较远时按 冲刺+跑酷向上+前进+俯冲键。\n"
                    "与原版一样需要自行判断距离和跑酷模式，但现在可以主动优先俯冲。"
                );
            }
            if (g_Config.personalRequests->parkourHelper->diveHelper->isActive.get())
            {
                ImGuiCTX::Indent _ind2;
                ImGui::DrawEnumPicker("俯冲辅助热键", g_Config.personalRequests->parkourHelper->diveHelper->hotkey.get(), ImGuiComboFlags_HeightLarge);
                ImGui::Checkbox("允许蹬墙跳出接悬挂", &g_Config.personalRequests->parkourHelper->diveHelper->allowWallEjectToHang.get());
                {
                    static ImGuiTextBuffer infoAboutWallEjectToHang = []() {
                        ImGuiTextBuffer buf;
                        buf.appendf(
                            "按住俯冲热键时，若条件满足可使用蹬墙侧跳接悬挂\n"
                            "和蹬墙后跳接悬挂跑酷动作。\n"
                            "实验性功能。\n"
                            "\n"
                            "发现者：TheManWithNothing\n"
                            "   https://www.youtube.com/@TheManWithNothing\n"
                            "   https://www.youtube.com/watch?v=SjgeA2mUs30\n"
                            "（右键点击复制到剪贴板）\n"
                            "给 modder 的冷知识：\n"
                            "仅将 0x14015423F 处的 4 字节 NOP 掉\n"
                            "就能得到一个几乎可用的侧跳接悬挂。\n"
                            "Unity 有时就这德行。"
                        );
                        return buf;
                        }();
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip(infoAboutWallEjectToHang.c_str());
                    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
                        ImGui::SetClipboardText(infoAboutWallEjectToHang.c_str());
                }
            }
            ImGui::Checkbox("边缘暗杀后可立即起身", &g_Config.personalRequests->parkourHelper->canRiseOnLedgeAfterLedgeAssassination.get());
        }
    }
    void ReadConfig(ConfigTop& cfg)
    {
        auto& hacksSection = cfg.hacks;
        enterWindowsByPressingAButton.Toggle(hacksSection->enterWindowsByPressingAButton->isActive);
        menacingWalkAndAutowalk.Toggle(hacksSection->menacingWalkAndAutowalk->isActive);
        changeZoomLevelsWhenAimingBombs.Toggle(hacksSection->changeZoomLevelsWhenAimingBombs);
        cycleEquipmentUsingMouseWheel.Toggle(hacksSection->cycleEquipmentUsingMouseWheel);
        dontUnsheatheWhenInDisguise.Toggle(hacksSection->dontUnsheatheWhenInDisguise);
        slightlyMoreResponsiveCrouch.Toggle(hacksSection->slightlyMoreResponsiveCrouch);
        takingCoverIsLessSticky.Toggle(hacksSection->takingCoverIsLessSticky);
        breakfallAndCatchLedgeByPressingE.Toggle(hacksSection->breakfallAndCatchLedgeByPressingE);
        easierTurnWhenSwingingOnAHorizontalBar.Toggle(hacksSection->easierTurnWhenSwingingOnAHorizontalBar);
        aimBombsFromPeaks.Toggle(hacksSection->aimBombsFromPeaks);
        noMoreImaginaryBombThrows.Toggle(hacksSection->noMoreImaginaryBombThrows);
        dontRandomlyTurn180degrees.Toggle(hacksSection->dontRandomlyTurn180degrees);
        moreSituationsToDropBombs.Toggle(hacksSection->moreSituationsToDropBombs->isActive);
        moreReliableQuickshot.Toggle(hacksSection->moreReliableQuickshot->isActive);
        automaticallyReloadWeaponsWhenRefillAllInShops.Toggle(hacksSection->automaticallyReloadWeaponsWhenRefillAllInShops);
        lookbehindButton.Toggle(hacksSection->lookbehindButton->isActive);
        noWaitForUnsafeEject.Toggle(hacksSection->noWaitForUnsafeEject);
        allowCustomizeEquipmentOnLedges.Toggle(hacksSection->allowCustomizeEquipmentOnLedges);
        guillotineGunRange.Toggle(hacksSection->slightlyGreaterGuillotineGunQuickshotRange);
        allowUnequipPistol.Toggle(hacksSection->allowUnequipPistol);
        correctLandingHeightOutOfVault.Toggle(hacksSection->correctLandingHeightOutOfVault);

        auto& cheatsSection = cfg.cheats;
        dontDecreaseRemainingAmmo.Toggle(cheatsSection->infiniteAmmo);

        auto& requestsSection = cfg.personalRequests;
        parkourHelpers.Toggle(requestsSection->parkourHelper->isActive);
        freezeFOV.Toggle(requestsSection->freezeFOV->isActive);
    }
    void WriteConfig(ConfigTop& cfg)
    {
        auto& hacksSection = cfg.hacks;
        hacksSection->enterWindowsByPressingAButton->isActive = enterWindowsByPressingAButton.IsActive();
        hacksSection->menacingWalkAndAutowalk->isActive = menacingWalkAndAutowalk.IsActive();
        hacksSection->changeZoomLevelsWhenAimingBombs = changeZoomLevelsWhenAimingBombs.IsActive();
        hacksSection->cycleEquipmentUsingMouseWheel = cycleEquipmentUsingMouseWheel.IsActive();
        hacksSection->dontUnsheatheWhenInDisguise = dontUnsheatheWhenInDisguise.IsActive();
        hacksSection->slightlyMoreResponsiveCrouch = slightlyMoreResponsiveCrouch.IsActive();
        hacksSection->takingCoverIsLessSticky = takingCoverIsLessSticky.IsActive();
        hacksSection->breakfallAndCatchLedgeByPressingE = breakfallAndCatchLedgeByPressingE.IsActive();
        hacksSection->easierTurnWhenSwingingOnAHorizontalBar = easierTurnWhenSwingingOnAHorizontalBar.IsActive();
        hacksSection->aimBombsFromPeaks = aimBombsFromPeaks.IsActive();
        hacksSection->noMoreImaginaryBombThrows = noMoreImaginaryBombThrows.IsActive();
        hacksSection->dontRandomlyTurn180degrees = dontRandomlyTurn180degrees.IsActive();
        hacksSection->moreSituationsToDropBombs->isActive = moreSituationsToDropBombs.IsActive();
        hacksSection->moreReliableQuickshot->isActive = moreReliableQuickshot.IsActive();
        hacksSection->automaticallyReloadWeaponsWhenRefillAllInShops = automaticallyReloadWeaponsWhenRefillAllInShops.IsActive();
        hacksSection->lookbehindButton->isActive = lookbehindButton.IsActive();
        hacksSection->noWaitForUnsafeEject = noWaitForUnsafeEject.IsActive();
        hacksSection->allowCustomizeEquipmentOnLedges = allowCustomizeEquipmentOnLedges.IsActive();
        hacksSection->slightlyGreaterGuillotineGunQuickshotRange = guillotineGunRange.IsActive();
        hacksSection->allowUnequipPistol = allowUnequipPistol.IsActive();
        hacksSection->correctLandingHeightOutOfVault = correctLandingHeightOutOfVault.IsActive();

        auto& cheatsSection = cfg.cheats;
        cheatsSection->infiniteAmmo = dontDecreaseRemainingAmmo.IsActive();

        auto& requestsSection = cfg.personalRequests;
        requestsSection->parkourHelper->isActive = parkourHelpers.IsActive();
        requestsSection->freezeFOV->isActive = freezeFOV.IsActive();
    }
    AutoAssembleWrapper<BatlampOfFrancide> batlampOfFranciade;
    AutoAssembleWrapper<AmmoCheat> dontDecreaseRemainingAmmo;
    AutoAssembleWrapper<PretendYoureInFranciade> pretendYoureInFranciade;
    AutoAssembleWrapper<DisableDisguiseCooldown> disableDisguiseCooldown;
    AutoAssembleWrapper<UnbreakableDisguise> unbreakableDisguise;
    AutoAssembleWrapper<DisguiseDoesntMakeYouInvisible> disguiseDoesntMakeYouInvisible;

    AutoAssembleWrapper<ParkourActionsExtraProcessing> parkourHelpers;
    AutoAssembleWrapper<FreezeFOV> freezeFOV;
};
std::optional<MyHacks> g_MyHacks;
void WriteAppliedHacksStateToConfig()
{
    if (g_MyHacks)
    {
        g_MyHacks->WriteConfig(g_Config);
    }
}
void DrawHacksControls()
{
    if (g_MyHacks)
    {
        g_MyHacks->DrawControls();
    }
}

#include "MyVariousHacks.h"
void MyVariousHacks_DevExtras_Start();
void MyVariousHacks::Start()
{
    g_MyHacks.emplace();
    MyVariousHacks_DevExtras_Start();
    g_MyHacks->ReadConfig(g_Config);
    g_MyHacks->WriteConfig(g_Config);
    MainConfig::WriteToFile();
}
