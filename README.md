# 数字识别

- 开发环境 Ubuntu18.04

## 目录结构
```
.
└── 实验报告一
    ├── build                       //存放cmake编译中间文件
    ├── CMakeLists.txt              //cmake文件
    ├── demo
    │   └── detector_demo.cpp       //识别测试集数字图像
    ├── image
    │   ├── num.png
    │   ├── test_num                //存放测试图像
    │   │   ├── 0
    │   │   ├── 1
    │   │   ├── 2
    │   │   ├── 3
    │   │   ├── 4
    │   │   ├── 5
    │   │   ├── 6
    │   │   ├── 7
    │   │   ├── 8
    │   │   ├── 9 
    │   │   ├── creat_link.sh       //用于创建测试图像文件路径和标签的脚本
    │   │   └── link.txt            //图像文件路径和标签的文件
    │   └── train_num               //存放训练图像
    │       ├── 0
    │       ├── 1
    │       ├── 2
    │       ├── 3
    │       ├── 4
    │       ├── 5
    │       ├── 6
    │       ├── 7
    │       ├── 8
    │       ├── 9
    │       ├── creat_link.sh
    │       └── link.txt
    ├── include
    │   └── number_detector.h
    ├── README.md
    ├── src
    │   └── number_detector.cpp
    └── template                    //存放模板文件
        └── template.txt            //模板文件
```

## 编译步骤
```
-   mkdir build
-   cd build
-   cmake ..
-   make
```
## 运行步骤

### mnist数据集
```
通过脚步文件生成link.txt文件，此文件内每行保存图片路径和标签，运行后两个数据集文件夹内都会生成一个link.txt文本文件
- cd image/num_test
- bash ./creat_link.sh
- cd ../num_train
- bash ./creat_link.sh

通过贝叶斯分类识别数字
-   ./detector_demo
```