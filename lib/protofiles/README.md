# ProtoFiles
This is the UBC Sailbot repository containing all .proto files for use with the [Google protobuf library](https://github.com/google/protobuf).
The specific use-case is for sending messages over [ZeroMQ](https://github.com/zeromq) without the need for a custom serializer/deserializer.

## Installing Dependencies
### Debian
```bash
sudo ./scripts/install_deps_debian.sh
```

### OS X
```bash
./scripts/install_deps_osx.sh
```
