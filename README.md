# MDB
Implementing a **memory database** like Redis with C++.

## 3rd-deps
- gtest(if `TESTING` is `ON`)

## Build

### Linux
```sh
mkdir build
cd build
cmake [-DCMAKE_BUILD_TYPE=Debug|Release -DTESTING=ON|OFF] ..
make all
make test # if TESTING is ON
```

### Windows CMake Project
Open source directory with Visual Studio 2019.  
Using `CMakeSettings.json` directly in Visual Studio 2019.

### Windows VS Project
Generate Visual Studio project files with CMake.  

**Comand Line**
```powershell
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=<vcpkg_root>/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows  -G "Visual Studio 16" -Thost=x64 [-DTESTING=ON] ..
```

**CMake GUI**
```txt
1. Click 'configure'.
2. Specify generator, optional platform and optional toolset.
3. Specify toolchain file as <vcpkg_root>/scripts/buildsystems/vcpkg.cmake.
4. Click configure 'Finish'.
5. Specify CMake options.
6. Click 'Generate'.
7. Open project.
```