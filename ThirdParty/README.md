# ThirdParty

## 目录职责

本目录用于存放项目需要固定版本管理的第三方源码依赖，优先选择小型、可审计、容易通过 CMake `add_subdirectory` 或单文件方式集成的库。

## 初始约定

- 不存放 Vulkan SDK、Slang SDK、CMake、Visual Studio Build Tools 等本机工具链。
- 不存放 Python 虚拟环境、pip 缓存、PyTorch wheel 或大型二进制包。
- 每个依赖应记录来源、版本或 commit、许可证，以及为什么需要它。
- 初期避免一次性引入完整渲染框架，优先保持可微渲染实验管线的可控性。

## 候选依赖

- `vk-bootstrap`：简化 Vulkan instance/device/queue/swapchain 初始化。
- `VulkanMemoryAllocator`：简化 Vulkan buffer/image memory 分配与映射。
- `glm`：主机侧向量、矩阵与相机数学。
- `stb`：轻量图像读写，适合 LDR debug 输出。
- `tinyobjloader`：轻量 OBJ mesh 输入。
- `tinyexr` 或 `OpenEXR`：HDR 图像与浮点 reference/gradient 数据。


