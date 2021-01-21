# MDB
Implementing a **memory database** like Redis with C++.

## 3rd-deps
- gtest(if `TESTING` is `ON`)

## Build
```sh
mkdir build
cd build
cmake [-DCMAKE_BUILD_TYPE=Debug|Release -DTESTING=ON|OFF] ..
make all
make UnitTests # if TESTING is ON
```

