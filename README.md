# grpc_test
Exploring grpc cpp

## Prerequisites
- cmake
- vcpkg

## Installation and build
```
git clone https://github.com/venkateshrajan/grpc_test.git
cd grpc_test
cmake -S . -B build --preset=vcpkg
cmake --build build
```

## Run server
```
GLOG_logtostderr=1 ./build/server/server
```

## Run client
```
GLOG_logtostderr=1 ./build/clien/client --name World
```

## References
- [faaxm/exmpl-cmake-grpc](https://github.com/faaxm/exmpl-cmake-grpc)
- [grpc/helloworld](https://github.com/grpc/grpc/tree/master/examples/cpp/helloworld)
- [grpc/route_guide](https://github.com/grpc/grpc/tree/v1.58.0/examples/cpp/route_guide)
