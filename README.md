某些开源库如何在项目中进行编译

* [cyclonedds](https://github.com/eclipse-cyclonedds/cyclonedds/tags)

* [cyclonedds-cxx](https://github.com/eclipse-cyclonedds/cyclonedds-cxx/tags)

* [taskflow](https://github.com/taskflow/taskflow/tags)

下载 `tar.gz`，解压至 `libs`，然后 `cmake` 

```bash
cmake -B build
cmake --build build -j
```

即可，理论上 `amd64` 和 `arm64` 都可以编译成功