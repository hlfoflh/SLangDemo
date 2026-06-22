# Architecture

## 文档职责

本文档作为项目的手动维护代码地图，记录目录结构、核心模块、数据流、依赖边界和关键入口。它应该随代码结构变化同步更新，但不承载详细算法推导或长期路线规划。

## 当前代码地图

当前仓库已建立精简的 Windows-only 初始骨架。暂不引入多平台层或通用 RHI 抽象；后续模块按实际需求再创建。

```text
SLangDemo/
  memory-bank/              # 项目文档与执行上下文
  ThirdParty/               # 固定版本的外部源码依赖；不放 SDK/虚拟环境
  Source/                   # 项目源码根目录
    Main.cpp                # 程序入口，只启动 FSDR 并处理顶层异常
    SDR.h/.cpp              # 可微渲染器主控制类
    Shaders/                # Slang shader/module 源码
      vector_add.slang      # 官方 hello-world 思路改写的最小 compute seed
  Asset/                    # 美术资源、测试场景、模型、纹理、reference 数据
  compiled-out/             # 本地编译和生成输出；默认不提交产物
```

## 代码风格

- 参考 `D:\Code\MeteorRender\MeteorRender\Private` 的 UE-like 风格。
- 类型名使用大驼峰并带语义前缀，例如 `FSDR`、`FSDRConfig`。
- 函数、局部变量和成员变量使用大驼峰；布尔变量使用 `b` 前缀，例如 `bInitialized`。
- 参数可使用 `In` 前缀表达输入语义，例如 `InConfig`。
- 当前命名空间为 `SLangDR`。

## 维护规则

- 只记录已经存在或基本确定会落地的结构。
- 新增模块时补充其职责、主要输入输出、依赖方向。
- 算法细节和实验笔记放入 `cur_execution_context.md` 或 `documents/`。







