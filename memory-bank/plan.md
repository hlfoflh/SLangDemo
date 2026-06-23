# Plan

## 文档职责

本文档保存大块的、长线的高层规划。它关注阶段目标、取舍和里程碑，不记录每天执行细节；执行中的细化任务放入 `cur_execution_context.md`。

## 长线规划

### Phase 0: 环境与最小实验地基

- 保持 Windows-only、C++/Vulkan/Slang 的最小闭环。
- 建立 shader 编译、Vulkan device、buffer/texture、dispatch、readback、图像/数值输出。
- 建立实验入口、metrics 输出和最小数据资产约定。
- 地基达到“能稳定跑一个 texture-space 实验”后立即进入实验，不提前铺大框架。

### Phase 1: Texture Fitting

- 固定 UV/quad 或简单 mesh，优化一张小 texture 匹配 reference。
- 先用 texture-space MSE，随后加入简单 render-space loss。
- 验证 Slang 自动微分或手写 backward 的梯度方向，加入有限差分对照。
- 输出 loss curve、result image、gradient/debug image。

### Phase 2: Neural Texture Compression

- 使用 latent texture + tiny decoder 重建 target texture/material channels。
- 在 Slang shader 中实现实时 decode 路径。
- 比较 uncompressed、BCn/传统压缩、neural compressed。
- 记录码率/显存、PSNR/SSIM/MSE、decode cost 和训练耗时。

### Phase 3: Render-Aware Material Compression

- 将 albedo/normal/roughness/metallic/AO 作为 material set 联合压缩。
- 使用固定几何、相机、灯光，从最终 PBR shading 计算 render-space loss。
- 评估 mip/random access/filtering 对质量和成本的影响。
- 形成可复用实验模板和 benchmark 报告。

### Phase 4: Optional Extensions

- SlangPy/PyTorch 快速训练路径。
- Mesh/material fitting 或 light/pose fitting。
- Triangle/gaussian/splat 表示只作为后续可选方向，不抢占神经纹理压缩主线。


