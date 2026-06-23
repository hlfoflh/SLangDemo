# Context

## 文档职责

本文档记录项目长期有效的核心上下文：项目简介、主要设计取向、当前总体架构和关键约束。只有发生较大方向或结构更新时才修改，内容保持简洁。

## 项目简介

本项目是基于 Slang 搭建可微渲染实验框架的探索区，当前主线确定为 render-aware neural texture/material compression：训练可在实时 shader 中解码的紧凑纹理/材质表示，并用可微渲染损失约束最终画面效果。

## 初始设计取向

- 核心关注实验测试闭环，不追求一开始就完成完整 renderer。
- 地基只搭到能稳定支撑实验：设备/资源/shader 编译/dispatch/readback/metrics；实验中出现真实痛点后再扩展架构。
- 前向渲染、loss、gradient、optimizer、benchmark 应尽量拆成可替换环节。
- 项目明确只支持 Windows 平台；不考虑多平台适配，不建立跨平台抽象层。
- 优先推进 Windows + C++ + Vulkan + Slang 路径。
- Python/SlangPy 路径保留为后续快速研究选项，但不作为当前源码骨架的一部分。
- 对每个实验保留最小可复现入口、输入资产和结果验证方式。
- 初始根目录约定为 `Source/` 放源码、`Asset/` 放美术/测试资源、`ThirdParty/` 放固定版本外部源码依赖、`compiled-out/` 放本地编译与生成输出。

## 主题边界

- 第一优先级：神经纹理/材质压缩，包括 latent texture、tiny decoder、multi-channel material set、mip/random access、render-space loss。
- 基线比较：uncompressed、BCn/传统压缩、neural compressed。
- 关键指标：码率/显存、PSNR/SSIM/MSE、render-space loss、decode cost、ms/frame、训练耗时。
- 暂不作为主线：完整 3D 重建、完整 path tracer、完整 3D Gaussian Splatting 训练器。

## 平台边界

- 只支持 Windows。
- 不设计 Linux/macOS/移动端兼容层。
- 不为多图形 API 建立通用 RHI；当前 GPU 后端以 Vulkan 为主。
- 可以参考其他项目的抽象方式，但代码结构优先服务 Windows/Vulkan/Slang 实验效率。

## 当前环境摘要

- 已可见：Vulkan SDK、`slangc`、`glslangValidator`、`spirv-val`、`spirv-dis`、`dxc`、`git`。
- 已验证：`slangc` 版本为 `2026.8`；Vulkan instance 为 `1.4.350`；当前机器可见 NVIDIA GeForce RTX 5070 与 AMD 集显。
- 项目 CMake 路径：`C:\Program Files\CMake\bin\cmake.exe`，版本 `4.3.3`。
- 当前 PATH 未可见：`cmake`、`ninja`、`python`/`py`、`cl`、`msbuild`。





