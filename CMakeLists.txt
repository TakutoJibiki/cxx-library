#
# パラメータ
#
set(config_path "../CMakeConfig")           # 設定ファイルのパス
set(share_dir_path1 cxx-library/source)     # share のディレクトリのパス
set(share_dir_path1 cxx-library/picojson)   # share のディレクトリのパス
set(target share)                           # 実行ファイル名

#
# 共有ライブラリ（*.so）を作成
#
file(GLOB files "source/*.cpp")
add_library(${target} SHARED ${files})
target_include_directories(${target} PUBLIC ${PROJECT_SOURCE_DIR}/${share_dir_path1})
target_include_directories(${target} PUBLIC ${PROJECT_SOURCE_DIR}/${share_dir_path2})

#
# コンパイラオプション
#
file(READ ${config_path} read_data)
string (REPLACE "\n" ";" lines ${read_data})
list(GET lines 0 raw_cflags)
string (REGEX REPLACE "CFLAGS ?= ?" "" cflags "${raw_cflags}")
add_definitions("${cflags}")
