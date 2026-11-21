ACST（ACSaveTool）v2.6.1
====

《刺客信条》系列存档 ID 转换工具，支持 GUI 与命令行两种模式。

- **版本**：v2.6.1（上游 2026-03 发布）
- **文件**：`ACSaveTool_x64.exe`
- **大小**：8,595,529 字节
- **SHA256**：`efc59cf3967153d6a40c91b2e33a66e3c4333b2800979437a587f1e0adbaf201`
- **上游项目**：<https://github.com/linzhouyu/ACST>
- **版权**：本文件为上游官方发布包的**原样备份**（未经任何修改），版权与署名归作者 **Linus L. (linzhouyu)** 所有

## 它能做什么

在不同账号之间转换《刺客信条》系列存档。存档数据是用**账号 ID 派生的密钥**加密的，换个账号直接拷存档进去会读不出来，这个工具负责把存档重新加密成目标账号可读的形式。

支持的存档与 ID 类型：

| 游戏 | ID 类型 |
|---|---|
| 刺客信条：大革命 (Unity) | Account ID (GUID) |
| 刺客信条：枭雄 (Syndicate) | Account ID |
| 刺客信条：起源 (Origins) | Account ID |
| 刺客信条：奥德赛 (Odyssey) | Account ID |
| 刺客信条：英灵殿 (Valhalla) | Account ID |
| 刺客信条：幻景 (Mirage) | Account ID |
| 刺客信条：影 (Shadows) | Account ID |
| 刺客信条：黑旗 (Black Flag) / 自由呐喊 | Game key |
| 刺客信条：叛变 (Rogue) | Game key |
| 刺客信条：解放 HD | Game key |
| 刺客信条 3 | Game key |
| 刺客信条 3 重制版 | Account ID |
| 刺客信条：启示录 | Legacy username |
| 渡神纪 / 极限巅峰 | Account ID |

## GUI 用法（大革命为例）

1. 运行 `ACSaveTool_x64.exe`
2. `存档文件` → **打开**，选择要转换的 `.save` 文件
3. `游戏` 下拉框选「刺客信条：大革命」
4. `解密 ID`：填存档原来的账号 ID，或勾选 `检测` 让工具自己识别
5. `加密 ID`：填目标账号 ID，或点右侧 `...` 按钮，**选一个用目标账号保存过的存档**让它反推 ID
6. 点 `转换`；原文件会自动备份到同目录 `acst_backup/`
7. 把输出的 `*.save` 拷回游戏存档目录（路径见下）

## 大革命存档目录

正版 / Ubisoft Connect：

```
C:\Program Files (x86)\Ubisoft\Ubisoft Game Launcher\savegames\<你的账号GUID>\720\
```

> 注意：有些第三方环境（各种"免安装/学习版"）存档在别处，例如
> `文档\Assassin's Creed Unity\<数字ID>\` 或 `D:\Ubisoft Game Launcher\savegames\<GUID>\720\`
> 具体以游戏实际读写的那个为准——**改错地方等于没改**。

## 命令行模式（v2.6.0 起支持）

GUI 里转换不方便时可以直接命令行调用，适合批处理。查看用法：

```bat
ACSaveTool_x64.exe --help
```

## 免责声明

本工具按「原样」提供，仅供学习研究使用，禁止商用。作者不对使用本工具可能造成的任何存档损坏负责。**转换前请务必备份原存档。**
