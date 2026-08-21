# ACU Mods（刺客信条：大革命/Unity Mod 合集）

本仓库包含两部分内容：

## 一、ACUFixes 汉化版（ACUFixes/）

基于 [NameTaken3125/ACUFixes](https://github.com/NameTaken3125/ACUFixes) **v0.9.3**（commit `08f84c3`）的中文汉化增强版。

### 相对上游的改动

1. **全菜单简体中文汉化**：插件（ACUFixes.dll）与插件加载器（ACUFixes-PluginLoader.dll）的全部 ImGui 菜单项、按钮、提示框（tooltip）均已翻译为中文。
2. **中文字体支持**：
   - ImGui 字体加载优先使用系统微软雅黑（`msyh.ttc`），字形范围改为 `GetGlyphRangesChineseSimplifiedCommon()`；
   - 菜单「附加」标签内可实时调节字体大小（9~75，默认 16），保存后写入配置文件 `fontSize` 字段。
3. **独占全屏鼠标修复**：上游版本在独占全屏模式下菜单无法移动鼠标（WndProc 收不到鼠标消息）。本版在游戏原始输入钩子处用内部鼠标增量自行推算光标位置并喂给 ImGui；无边框窗口模式不受影响（自动检测、不重复干预）。
4. **编译兼容性**：全部项目加 `/utf-8` 编译标志（源码含中文必须）；两份 `ImGuiConfigUtils.h` 补充 `#include "Serialization/enumFactory.h"`（v143 工具集下 `enum_reflection` 需要显式包含）。
5. `release-dlls/` 内附带已编译好的发布文件（不含 PDB）。

### 编译方法

- Visual Studio 2022（MSVC v143），解决方案级构建（不要单独构建某个 vcxproj，会因 `$(SolutionDir)` 未定义而失败）：

```bat
msbuild ACUFixes.sln /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143
```

- 构建产物位于 `build\x64\Release\`。

### 安装到游戏（Assassin's Creed Unity v1.5.0）

```
<游戏根目录>\
├─ version.dll                        ← 代理加载器
└─ ACUFixes\
   ├─ ACUFixes-PluginLoader.dll
   ├─ ACUFixes-PluginLoader-config.json
   └─ plugins\
      ├─ ACUFixes.dll
      └─ NewAnimations\*.anim.json    ← 兜帽动画所需
```

进游戏后按 **Insert** 打开菜单（全中文）。

## 二、Mods 目录（大革命相关工具与补丁）

| 目录 | 内容 |
|---|---|
| `Mods/AnvilToolkit_Utils/` | Anvil 工具箱辅助 |
| `Mods/刺客信条ID转换器/` | 含 ACSaveTool_x64.exe 存档工具 |
| `Mods/AnvilToolkit.exe` | Anvil 引擎资源解包/打包工具 |
| `Mods/大革命/90帧物理补丁/` | 90 帧物理补丁 |
| `Mods/大革命/AC修复mod/` | AC 修复 mod |
| `Mods/大革命/大革命单独的ReShade补丁/` | ReShade 光效补丁 |
| `Mods/大革命/翻滚动作/` | 前空翻动作 mod（两个 >100MB 的 .data 文件经 **Git LFS** 存储） |
| `Mods/大革命/铁占工具箱/` | Anvil 工具箱（铁占=Anvil 音译） |

> 注：`3DMGAME-GhostReconBreakpointv20211103T17Epic.zip` 与本仓库主题无关，未纳入版本控制。

## Git LFS 说明

克隆本仓库前请安装 [Git LFS](https://git-lfs.com/) 并执行 `git lfs install`，否则 `Mods/大革命/翻滚动作/` 下的大文件只会得到指针文件。
