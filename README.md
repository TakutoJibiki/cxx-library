# 環境構築
1. 本リポジトリのディレクトリ直下 `cxx-library/` で下記のコマンドを実行．コンパイラオプション，ライブラリのリンク等の設定は `../CMakeConfig` で指定する．
    ```bash
    $ cp CMakeConfig.sample ../CMakeConfig
    ```
2. C++ のプロジェクト用のディレクトリ（仮に `sample-project` とする）を作成し，CMake のファイルをコピーする．`../sample-project/CMakeLists.txt` 内の `sample-project` の部分を実際のプロジェクト名（ディレクトリ名）に合わせて変更すること．
    ```bash
    $ mkdir ../sample-project
    $ cp CMakeLists_project.txt ../sample-project/CMakeLists.txt
    ```
3. 環境全体用の CMake のファイルをコピーする．`../CMakeLists.txt` 内の `add_subdirectory` の記述は適宜変更，追加すること．
    ```bash
    $ cp CMakeLists_entire.txt ../CMakeLists.txt
    ```
4. `../sample-project/` 内にソースコードを配置していく．

# ビルド
1. `cxx-library/../` にビルド用のディレクトリを作成
    ```
    $ cd ../
    $ mkdir build
    $ cd build
    ```
2. 下記のコマンドでビルド
    ```
    $ cmake ..
    $ make
    ```