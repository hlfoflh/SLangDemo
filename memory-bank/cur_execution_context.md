# Current Execution Context

## 文档职责

本文档记录当前正在推进的规划上下文，比 `plan.md` 更细：当前目标、已确认事实、临时决策、算法笔记路径、参考资料入口和下一步执行项。一个阶段结束后，应把长期有效内容提炼到 `context.md` 或 `architecture.md`，并清理过期细节。

## 当前目标

围绕 render-aware neural texture/material compression 搭建最小可微渲染实验地基。

## 已确认环境

- 工作区：`D:\Code\SLangDemo`
- 当前仓库内容：已有 `memory-bank/`、`ThirdParty/`、`Source/`、`Asset/`、`compiled-out/` 初始目录。
- `VULKAN_SDK=D:\CodeTools\VulkanSDK\1.4`
- `slangc`：`D:\CodeTools\VulkanSDK\1.4\Bin\slangc.exe`，版本 `2026.8`
- `glslangValidator`：Vulkan SDK 路径可见，版本 `16.2.0`
- SPIR-V 工具：`spirv-val.exe`、`spirv-dis.exe` 可见
- Vulkan：instance `1.4.350`；可见 NVIDIA GeForce RTX 5070 与 AMD Radeon(TM) Graphics
- CMake：采用 `C:\Program Files\CMake\bin\cmake.exe`，版本 `4.3.3`
- CMake 已可通过 VS 2022/MSVC 生成并构建项目；MSVC 编译器为 `19.44.35228.0`
- 当前 PATH 未找到：`cmake`、`ninja`、`python`/`py`、`cl`、`msbuild`，但 CMake 能通过 VS 安装路径调用 MSBuild/MSVC

## 初始判断

- 现有 Vulkan/Slang SDK 足够开始做 shader 编译、SPIR-V 生成与基础 Vulkan 能力验证。
- 若走 C++/Vulkan 主机程序，已有可用 CMake；仍需确认 MSVC/Visual Studio Build Tools 或其他 C++ 编译器是否可从项目构建环境调用。
- 若走 SlangPy/PyTorch 快速实验，需要补齐 Python 3.10+，之后再决定是否安装 PyTorch。
- 当前明确只支持 Windows 平台；不考虑多平台适配，不提前建立跨平台层或通用 RHI 抽象。
- Python/SlangPy 保留为后续研究入口，但当前源码骨架先聚焦 C++/Vulkan。
- 项目主线已确定为神经纹理/材质压缩，优先建立可测试、可对比、可迭代的实验闭环。
- 地基只搭到实验需要的程度；实验过程中出现真实痛点后再扩展架构。

## ThirdParty 初始建议

- 根目录可建立 `ThirdParty/`，用于存放固定版本的外部依赖源码或轻量单文件库。
- 初期只建议纳入最小 C++/Vulkan 运行时依赖，例如 `vk-bootstrap`、`VulkanMemoryAllocator`、`stb`、`glm`、`tinyobjloader`。
- Python 依赖不建议放入 `ThirdParty/`，应由虚拟环境和 requirements/lock 文件管理。
- Slang/Vulkan SDK 自带工具不建议复制到 `ThirdParty/`，只在 CMake 配置中引用本机路径或环境变量。

## 初始目录约定

- `Source/`：源码根目录，当前只保留 `Main.cpp`、`SDR.h/.cpp` 和 `Shaders/`。
- `Asset/`：未来 demo/实验需要的美术资源、测试场景、模型、纹理和 reference 数据。
- `ThirdParty/`：固定版本的第三方源码依赖，不放 SDK、工具链或虚拟环境。
- `compiled-out/`：本地编译和生成输出路径，整个目录默认由 `.gitignore` 忽略。

## 当前源码骨架

- `Source/Main.cpp`：程序入口，只负责创建并运行 `SLangDR::FSDR`，以及处理顶层异常。
- `Source/SDR.h/.cpp`：可微渲染器主控制类；当前只包含 `Initialize/Execute/Shutdown` 生命周期空壳。
- `Source/Shaders/vector_add.slang`：基于 Slang 官方 `hello-world` 思路改写的最小 compute shader seed。

## 代码风格约定

- 参考 `D:\Code\MeteorRender\MeteorRender\Private` 的 UE-like 风格。
- 类型名使用大驼峰并带语义前缀，例如 `FSDR`、`FSDRConfig`。
- 函数、局部变量和成员变量使用大驼峰；布尔变量使用 `b` 前缀，例如 `bInitialized`。
- 参数可使用 `In` 前缀表达输入语义，例如 `InConfig`。

## 官方示例调研

- 临时参考源码曾位于 `compiled-out/reference/`，已删除；后续需要时临时重新 clone。
- 调研记录：`memory-bank/documents/2026-06-22-slang-official-examples-survey.md`
- 第一阶段建议吸收：Slang `hello-world`、`reflection-api`、`autodiff-texture`。
- 第二阶段可参考：Slang `mlp-training`、SlangPy `simple_compute`、SlangPy `pathtracer`。

## 主题决策

- 主线：render-aware neural texture/material compression。
- 第一实验：`TextureFit`，固定 UV/quad 或简单 mesh，优化 texture 匹配 reference。
- 第二实验：`NeuralTextureCompression`，latent texture + tiny decoder，shader-side decode。
- 第三实验：`RenderAwareMaterialCompression`，多通道 PBR material set 联合压缩并用最终 shading loss 评估。
- 调研记录：`memory-bank/documents/2026-06-22-project-theme-neural-texture-compression.md`

## 地基边界

- 必须先具备：Slang 编译、Vulkan device、buffer/texture、dispatch、readback、metrics、实验入口。
- 可以暂缓：窗口系统、编辑器 UI、完整 scene system、完整 render graph、Python training bridge。
- 明确不做：Linux/macOS/移动端兼容层、多 API 通用 RHI。
- 新增抽象必须服务于当前实验，不为假想未来一次性铺开。

## 当前验证

- `Source/Shaders/vector_add.slang` 已用 `slangc` 编译到 `compiled-out/shaders/vector_add.spv`。
- `compiled-out/shaders/vector_add.spv` 已通过 `spirv-val` 校验。
- 根目录 Git 仓库已初始化，初始分支为 `main`。
- `.gitignore` 已设置 `compiled-out/` 忽略规则；该目录下所有文件均不进入 Git。
- CMake configure/build 已通过，生成 `compiled-out/bin/Debug/SLangDemo.exe`。
- 运行 `compiled-out/bin/Debug/SLangDemo.exe` 输出正常。
- VSCode 项目级配置已建立：`.vscode/settings.json`、`tasks.json`、`launch.json`、`extensions.json`。
- VSCode 默认 build task 为 `CMake: build default`；debug 配置为 `Debug SLangDemo`。

## 参考资料入口

- Slang 官方站点与文档：`https://shader-slang.org/`
- Slang 自动微分：`https://docs.shader-slang.org/en/latest/external/slang/docs/user-guide/07-autodiff.html`
- Slang 模块系统：`https://shader-slang.org/slang/user-guide/modules.html`
- SlangPy 文档：`https://slangpy.shader-slang.org/`
- Slang GitHub：`https://github.com/shader-slang/slang`

## 下一步候选任务

- 建立最小 Windows/Vulkan compute host，运行 `Source/Shaders/vector_add.slang`。
- 增加 readback 和 metrics 输出能力，形成第一个可测试 compute 闭环。
- 设计 `TextureFit` 最小实验输入：小尺寸 reference texture、可优化 texture buffer、MSE loss。
- 吸收 Slang 官方 `hello-world` 的 session/module/entry point/SPIR-V 生成流程，但先避免创建过重抽象层。












