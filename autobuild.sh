#! /bin/bash
set -e
PROJECT_ROOT=$(pwd)
BUILD_DIR="${PROJECT_ROOT}/build"
INCLUDE_DIR="${PROJECT_ROOT}/include"
LIB_DST="${PROJECT_ROOT}/lib"

mkdir -p "${BUILD_DIR}"
mkdir -p "${LIB_DST}"

rm -rf "${BUILD_DIR}"/*

cd "${BUILD_DIR}"
cmake ..
make

cd "${PROJECT_ROOT}"
echo "编译完成，头文件已拷贝至 ${LIB_DST}"