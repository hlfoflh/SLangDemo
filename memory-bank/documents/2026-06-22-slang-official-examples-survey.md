# Slang Official Examples Survey

## 文档职责

本文档是临时调研记录，用于筛选哪些 Slang 官方示例适合作为本项目的起始参考。长期有效结论应提炼到 `context.md`、`architecture.md` 或 `cur_execution_context.md`。

## 本地参考源码

- Slang 官方示例：曾临时 clone 到 `compiled-out/reference/slang/examples/`
- SlangPy 官方示例：曾临时 clone 到 `compiled-out/reference/slangpy/examples/`
- slang-rhi 官方示例：曾临时 clone 到 `compiled-out/reference/slang-rhi/examples/`

这些目录只作为临时阅读材料，已经删除；后续需要时再临时 clone。

## 结论摘要

最适合作为第一阶段敲门砖的是 Slang 官方 `hello-world` + `reflection-api` + `autodiff-texture` 的组合，而不是直接复制完整 demo：

- `hello-world`：最小 Slang -> SPIR-V -> Vulkan compute 路径，适合作为编译和 host 运行时的起点。
- `reflection-api`：展示如何从 Slang program reflection 获取参数与布局信息，适合后续减少手写 Vulkan descriptor/layout。
- `autodiff-texture`：最贴近可微渲染目标，展示 custom backward derivative、texture sampling 的反向传播、loss fragment pass 和梯度累积。

SlangPy 示例更适合作为研究/训练快速通道：

- `simple_compute`：最小 Python 调 Slang compute 的入口。
- `pathtracer`：适合作为中期 scene/camera/path tracing/accumulation/tone mapping 结构参考，但体量较大，不宜作为第一个 C++ 起点。
- `render_pipeline`：适合参考 SlangPy raster pipeline 组织。

`slang-rhi` 示例可以参考接口设计，但暂不建议直接引入为核心依赖；官方 README 仍说明该库处于重构和开发中。

## 候选示例评估

### Slang `hello-world`

适合作为第一个 C++/Vulkan compute seed。它展示了：

- 创建 Slang global/session。
- `loadModule` 加载 `.slang` 文件。
- `findEntryPointByName` 定位 compute entry。
- 组合 module + entry point 并生成 SPIR-V。
- 创建 Vulkan compute pipeline、descriptor、buffer 并 dispatch。

需要改造点：

- 官方代码里 Vulkan 初始化和资源管理较手写，后续应迁移到本项目的 Windows/Vulkan runtime。
- descriptor/layout 后续应结合 Slang reflection，而不是长期硬编码。

### Slang `reflection-api`

适合作为早期第二块。它展示：

- 遍历 module 中定义的 entry points。
- 组合并 link program。
- 获取 target-specific program layout。
- 遍历参数、类型和布局信息。

对本项目价值：

- 为 Slang module 到 Vulkan 资源绑定建立自动化基础。
- 支撑后续 render/diff pass 的统一参数绑定。

### Slang `autodiff-texture`

这是可微渲染方向最关键的官方参考。它展示：

- 用 `[BackwardDerivative]` 给 texture load 定义自定义反向传播。
- 用 `[PrimalSubstituteOf]` 将 hardware sample 的反向传播替换为可微 reference implementation。
- 用 `__bwd_diff(loss)` 从 loss pass 触发反向传播。
- 用 accumulate buffer 收集 texture gradient。

需要谨慎点：

- 官方示例依赖其示例框架和图形抽象层，不适合整包移植。
- fixed point atomic 累积梯度适合 demo，但本项目后续应抽象 gradient accumulation policy。

### Slang `mlp-training`

适合作为训练闭环参考，不是渲染起点。它展示：

- `bwd_diff(loss)` 的训练用法。
- 网络参数、梯度和 Adam optimizer 的 kernel pass 分离。
- loss reduction 和 parameter update 的基本结构。

对本项目价值：

- 后续可把 optimizer/loss/gradient buffer 的组织迁移到 `Source/Diff/`。

### SlangPy `simple_compute`

适合作为 Python 快速验证起点。它展示：

- `spy.Device` 创建。
- `load_program` 加载 Slang shader。
- `create_compute_kernel` 创建 kernel。
- buffer 创建、`ShaderCursor` 绑定、dispatch、readback。

需要等 Python 3.10+ 和 SlangPy 安装后再落地。

### SlangPy `pathtracer`

适合作为中期结构参考。它包含：

- camera、scene、mesh/material buffer、TLAS、path tracing compute pass。
- accumulation 和 tone mapping pass。
- Python 与 C++ 两条形式。

不适合作为第一块代码，因为依赖和体量会压过当前项目架构。

### slang-rhi `triangle/base`

适合参考 GPU 抽象和示例组织形状，但不代表本项目要建立通用 RHI：

- device creation helper。
- shader program/pipeline creation helper。
- render pass/command encoder 使用方式。

暂不建议作为项目依赖。本项目明确只支持 Windows/Vulkan，不做多 API 通用 RHI。

## 建议引入顺序

1. 保留当前 `SDR` 主控骨架。
2. 引入一个官方 `hello-world` 风格的 compute shader seed，先验证 Slang 编译。
3. 在最小 Windows/Vulkan host 中吸收 `hello-world` 的 Slang session/module/entry point 流程，先避免创建过重抽象层。
4. 建立最小 Vulkan compute host，先跑 vector add。
5. 引入 `reflection-api` 思路，替换硬编码 descriptor/layout。
6. 等出现真实可微渲染需求后，再抽出 loss/gradient/optimizer 结构，参考 `autodiff-texture` 和 `mlp-training`。
7. 可选建立 `Source/Python/` SlangPy simple compute，以便快速验证 shader 行为。




