import os
import shutil

source_dir = "./dll"
target_dir = "./build"

# 创建目标目录（如果不存在）
if not os.path.exists(target_dir):
    os.makedirs(target_dir)

# 遍历源目录，复制 DLL 文件到目标目录
for filename in os.listdir(source_dir):
    if filename.endswith(".dll"):
        shutil.copy(os.path.join(source_dir, filename), target_dir)
        print(f"Copied {filename} to {target_dir}")
