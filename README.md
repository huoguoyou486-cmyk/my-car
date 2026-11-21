# 我的小车

基于 **STM32F103C8** 的智能循迹小车项目，使用 **Keil MDK-ARM（µVision）** 和 STM32F10x 标准外设库。

## 主要功能

- 左右电机独立方向控制、PWM 调速
- 四路红外传感器检测黑线（PA8、PA9、PA10、PA11）
- 弯道、急转弯处理
- OLED 显示与 LED 指示

## 工程结构

- `user/`：主程序、中断处理
- `Hardware/`：电机、PWM、传感器、OLED、转弯逻辑等
- `System/`：延时模块
- `start/`：启动文件与芯片支持代码
- `library/`：STM32F10x 标准外设库
- `project.uvprojx`：Keil 工程文件

## 使用方法

安装 Keil MDK-ARM 和 STM32F1 相关设备支持包，打开 `project.uvprojx`，检查芯片型号、连线后编译并下载。

## 已知问题

原压缩包中**缺少 `Hardware/Key.c`**，此前工程引用了本地电脑上的绝对路径。整理版本中的工程配置已改为相对路径，但未虚构缺失源码。若提示 `Key_Init`、`Key_GetNum` 未定义，需要补齐此文件。

本项目尚未在当前环境完成编译或实机验证。生成的 `Objects/` 和 `Listings/` 目录不必提交。第三方 STM32 库文件保留其原始版权声明。
