import re
from subprocess import run, CalledProcessError
import glob
import os
import shutil
import time


def generate_and_move_pyi():
    try:
        # 生成 .pyi 文件
        run(["stubgen", "."], check=True)

        # 遍历当前目录及所有子目录
        for root, dirs, files in os.walk("out/LuoguDesktop"):
            # 获取 .pyi 文件
            source_files = glob.glob(os.path.join(root, "*.pyi"))
            if not source_files:
                continue  # 如果当前子目录没有 .pyi 文件，则跳过

            for file in source_files:
                # 提取相对路径
                relative_path = os.path.relpath(file, "out/LuoguDesktop")

                # 生成目标文件路径
                destination = os.path.join(os.getcwd(), relative_path)

                # 确保目标文件夹存在
                os.makedirs(os.path.dirname(destination), exist_ok=True)

                # 移动文件到目标路径，可能会覆盖已存在的文件
                shutil.move(file, destination)

                print(f"移动 {file} 到 {destination}")

    except CalledProcessError as e:
        print(f"生成 .pyi 文件时出错: {e}")
    except FileNotFoundError as e:
        print(e)
    except Exception as e:
        print(f"发生了一个错误: {e}")


# 调用函数
generate_and_move_pyi()
os.remove("out")  # 删除生成的 .pyi 文件
