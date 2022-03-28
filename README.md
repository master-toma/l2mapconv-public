# l2mapconv

<p align="center">
    <img src="assets/cruma.png" width="400">
    <img src="assets/toi.png" width="400">
</p>

Lineage II geodata builder.

- Supported clients: C1, HF.
- Supported geodata formats: L2J.

## Features

- Map and geodata preview.
- L2J geodata building.

## Usage

### Geodata preview

1. Place L2J geodata files in the `geodata` directory for preview.
2. Run `l2mapconv.exe preview` providing path to the client and the map names:

```sh
> l2mapconv.exe preview "C:/Path/To/L2" 19_21 20_21
```

3. Use WASD, RMB, Shift and Alt to control camera.
4. *Optional*. Press Build button to build geodata, see results in the `output` directory.

### Geodata building

1. Run `l2mapconv.exe build` providing path to the client and the map names:

```sh
> l2mapconv.exe build "C:/Path/To/L2" 19_21 20_21
```

2. See results in the `output` directory.

## Project building

Requirements:

- Clang
- Cmake
- Ninja
- MVS on Windows and Xcode on macOS (or standalone Clang)

### Windows

```sh
> git clone --recurse-submodules -j8 https://github.com/madyanov/l2mapconv-public.git
> cd l2mapconv-public
> cmake -H. -G Ninja -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang.exe"
> cd build
> ninja
```

### macOS

1. *Optional*. Install dependencies using [Brew](https://brew.sh/):

    ```sh
    $ brew install cmake ninja
    ```

2. Clone and build project:

    ```sh
    $ git clone --recurse-submodules -j8 https://github.com/madyanov/l2mapconv-public.git
    $ cd l2mapconv-public
    $ cmake -H. -G Ninja -Bbuild -DCMAKE_BUILD_TYPE=Release
    $ cd build
    $ ninja
    ```

## Credits

- [Recast](https://github.com/recastnavigation/recastnavigation)
- [L2PackageTools](https://github.com/Bigcheese/L2PackageTools)
- [l2mapper](https://github.com/justgos/l2mapper)
- [UEViewer](https://github.com/gildor2/UEViewer)
- [UT Package Tool](https://www.acordero.org/projects/unreal-tournament-package-tool)
- UT 2003
