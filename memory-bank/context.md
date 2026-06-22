# Context

## 文档职责

本文档记录项目长期有效的核心上下文：项目简介、主要设计取向、当前总体架构和关键约束。只有发生较大方向或结构更新时才修改，内容保持简洁。

## 项目简介

本项目是基于 Slang 搭建可微渲染管线的探索型 demo 区域。目标不是一次性完成完整 renderer，而是建立一个灵活、可读、可扩展的实验框架，让 Slang 自动微分、Vulkan/compute 路径、以及可选 Python/PyTorch 训练工作流可以逐步接入。

## 初始设计取向

- 先把 Slang shader/module 组织清楚，再决定主机侧运行时厚度。
- 前向渲染、损失计算、梯度传播应尽量拆成可替换 pass。
- 暂定只支持 Windows 平台，优先推进 C++/Vulkan 路径，不提前建立多平台层或通用 RHI 抽象。
- Python/SlangPy 路径保留为后续快速研究选项，但不作为当前源码骨架的一部分。
- 对每个实验保留最小可复现入口、输入资产和结果验证方式。
- 初始根目录约定为 `Source/` 放源码、`Asset/` 放美术/测试资源、`ThirdParty/` 放固定版本外部源码依赖、`compiled-out/` 放本地编译与生成输出。

## 当前环境摘要

- 已可见：Vulkan SDK、`slangc`、`glslangValidator`、`spirv-val`、`spirv-dis`、`dxc`、`git`。
- 已验证：`slangc` 版本为 `2026.8`；Vulkan instance 为 `1.4.350`；当前机器可见 NVIDIA GeForce RTX 5070 与 AMD 集显。
- 项目 CMake 路径：`C:\Program Files\CMake\bin\cmake.exe`，版本 `4.3.3`。
- 当前 PATH 未可见：`cmake`、`ninja`、`python`/`py`、`cl`、`msbuild`。




