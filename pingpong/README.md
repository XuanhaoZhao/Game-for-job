# Ping Pong 游戏（基于SFML）

这是一个使用 SFML（简单快速多媒体库）开发的简单乒乓球游戏。游戏具有基本的功能，包括玩家控制的球拍、一个会反弹的球、以及一个计分系统。

## 特性
- 玩家对战模式
- 计分系统
- 球的反弹机制
- 视觉效果，包括扫描线和复古风格

## 截图
![游戏截图](./screenshots/pingpong_example.png)

## 运行要求
要运行该项目，你需要以下环境：
- **C++ 编译器**（如 GCC 或 Clang）
- **SFML 库**（v2.5 或更高版本）
    - 你可以从 [SFML 官方网站](https://www.sfml-dev.org/download.php) 下载并安装 SFML。

## 构建项目

1. **安装 SFML**: 
   请确保你已经安装了 SFML。如果你使用的是包管理工具，可以通过以下命令安装：
   
   - **Ubuntu/Debian**: `sudo apt-get install libsfml-dev`
   - **MacOS**: `brew install sfml`
   - **Windows**: 从 [SFML 官方网站](https://www.sfml-dev.org/download.php) 下载适合的版本并根据安装说明进行配置。

2. **克隆仓库**:
    ```
    git clone https://github.com/your-username/pingpong-game.git
    cd pingpong-game
    ```

3. **使用 Makefile 构建项目**:
   - 导航到包含 `Makefile` 文件的目录，运行以下命令构建项目：
     ```
     make
     ```

4. **运行游戏**:
    - 构建完成后，可执行文件将会在 `build` 文件夹中。你可以通过以下命令运行游戏：
    ```
    ./build/pingpong.exe
    ```

## 游戏规则

- **玩家控制**:
    - **玩家 1**：使用 `W` 键和 `S` 键控制左侧的球拍上下移动。
    - **玩家 2**：使用 **向上** 和 **向下** 箭头键控制右侧的球拍上下移动。

- **游戏目标**:
    - 游戏目标是防止球从你的球拍旁边飞过，并尽量让球通过对方球拍得分。
    - 每当球通过某个玩家的球拍时，将为对方加分。

- **视觉效果**:
    - 游戏包括简单的复古风格效果，模拟 **扫描线** 和 **绿色显示覆盖**，以营造老式CRT电视的效果。

## 游戏配置

### 资源
- 项目中包含了诸如 `PressStart2P-Regular.ttf` 的字体文件，用于计分显示。
- **注意**：请确保 `assets` 文件夹包含所有必需的资源文件后再运行游戏。

## 致谢
- **SFML**：用于构建该游戏的多媒体库。
- **字体**：该游戏使用了 [Press Start 2P 字体](https://www.1001fonts.com/press-start-2p-font.html)。

## 许可证
该项目使用 MIT 许可证 - 详细内容请见 [LICENSE.md](LICENSE.md) 文件。


