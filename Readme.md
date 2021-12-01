对[原版工程](https://github.com/ethan-li-coding/SemiGlobalMatching)做了linux端的迁移



```shell
# 环境配置：
# 由于只用到opencv的读取、保存功能，所以可以选择apt安装opencv
sudo apt install libopencv-dev
# 编译：
make
# 运行(示例)：
./semi Data/cone/im2.png Data/cone/im6.png
```

