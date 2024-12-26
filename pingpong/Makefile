# 编译器设置
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra

# SFML 配置
SFML_INCLUDE = -I"D:/cpplib/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.2/include"
SFML_LIB = -L"D:/cpplib/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.2/lib"
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# 项目路径和目标设置
SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = $(BUILDDIR)/pingpong.exe

# 源代码文件和目标文件设置
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# 构建规则
all: run_python $(TARGET)

# 在构建之前运行 Python 脚本
run_python:
	@echo "Running python script to move DLLs..."
	python .\move_dlls.py

# 构建目标文件规则
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c $< -o $@

# 生成可执行文件规则
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(SFML_LIB) $(SFML_FLAGS) -o $(TARGET)

# 清理规则
clean:
	rm -rf $(BUILDDIR)/*
