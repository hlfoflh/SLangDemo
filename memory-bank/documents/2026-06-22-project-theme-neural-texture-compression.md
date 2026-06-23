# Project Theme: Render-Aware Neural Texture Compression

## 文档职责

本文档记录本项目主题选择的阶段性决策。长期有效结论已提炼到 `context.md` 和 `plan.md`；这里保留更具体的取舍理由，后续可作为回顾材料。

## 决策

项目主线确定为基于 Slang 可微渲染的神经纹理/材质压缩实验框架。

更具体地说，目标不是只做一套普通 neural image codec，而是训练一种可在实时 shader 中解码的紧凑纹理/材质表示，并用最终渲染画面的 loss 来约束压缩结果。

## 为什么选择这个方向

- 工业问题明确：纹理和材质集是实时渲染中显存、带宽和包体的重要来源。
- 实验边界清晰：可以稳定比较码率、显存、图像质量、最终渲染误差和解码耗时。
- 与 Slang 契合：tiny decoder、half precision、shader-side random access、mip/filtering 都适合在 Slang 中探索。
- 与可微渲染契合：loss 不只看 texture-space 重建，也可以看 render-space 最终画面。
- 比完整 3D 重建、完整 path tracing 或 3DGS 训练器更适合作为本仓库早期主线。

## 地基原则

- 先打能支持实验闭环的地基，不提前建设大而全框架。
- 地基至少包括 shader 编译、Vulkan device、buffer/texture、dispatch、readback、metrics、实验入口。
- 当一个真实实验开始让现有结构难受时，再反向改进架构。
- 新增目录和抽象必须服务于正在推进的实验，而不是预设未来所有可能性。

## 实验主线

1. `TextureFit`：固定 quad/mesh/UV，优化 texture 匹配 reference。
2. `NeuralTextureCompression`：latent texture + tiny decoder，重建 texture/material channels。
3. `RenderAwareMaterialCompression`：用 PBR shading 的最终画面 loss 训练/评估压缩表示。

## 基线和指标

- 基线：uncompressed、BCn/传统压缩、neural compressed。
- 质量：MSE、PSNR、SSIM、render-space loss。
- 成本：bits/texel、显存、解码 ALU、ms/frame、训练耗时。
- 工程性：random access、mip 支持、filtering 稳定性、shader 可集成性。

## AIHoloImager 参考结论

`gongminmin/AIHoloImager` 是一个完整 Windows/CMake/C++/GPU/AI 3D 重建系统，目标是 few images/video 到相对完整的 3D mesh。它值得参考，但不适合直接引入。

可参考点：

- 数据流分阶段：SfM、mask/delight、AI mesh、differentiable optimizer、post processing。
- `GpuDiffRender` 的 pass 分解：rasterize fwd/bwd、interpolate fwd/bwd、texture fwd/bwd、anti-alias fwd/bwd。
- PyTorch autograd bridge 的组织方式。

不直接引入的原因：

- 外部依赖非常重，包含 SfM、AI 模型、PyTorch、D3D12/Vulkan 等。
- 主题是完整 3D mesh reconstruction，容易把本项目拉偏。
- shader 体系以 HLSL/DXC 为主，而本项目核心探索 Slang autodiff 和 Vulkan 路径。

