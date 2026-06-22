# Plan

## 文档职责

本文档保存大块的、长线的高层规划。它关注阶段目标、取舍和里程碑，不记录每天执行细节；执行中的细化任务放入 `cur_execution_context.md`。

## 长线规划

### Phase 0: 环境与项目骨架

- 明确 C++/Vulkan、Slang CLI、SlangPy/Python 三条路径的最小依赖。
- 建立目录结构、忽略规则、基础构建脚本和 shader 编译验证。
- 形成第一个可重复运行的 compute shader 示例。

### Phase 1: 最小前向渲染管线

- 建立基础 scene/camera/material 数据表示。
- 实现一个最小 raster 或 compute-based rendering pass。
- 增加图像输出、debug capture、基础回归检查。

### Phase 2: 可微分核心闭环

- 选定一个小目标函数，例如单参数颜色/位置优化。
- 使用 Slang 自动微分生成或调用梯度路径。
- 加入有限差分对照，验证梯度方向和数值量级。

### Phase 3: 扩展实验

- 接入更复杂的几何、材质、光照或 SDF/point/gaussian 表示。
- 评估 C++ 原生管线与 Python/SlangPy 训练管线的边界。
- 沉淀可复用模块、实验模板和测试基线。

