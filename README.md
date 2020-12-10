1. 进入glfw-3.3.2目录下新建build目录
   ```
   cd glfw-3.3.2 
   mkdir glfw && cd glfw
   cmake ../
   make && make install //如果有权限问题分别用sudo make 和 sudo make install
   cd ../..
    ```
2. 将glad目录下的头文件拷贝到/usr/local/include下
    ```
   cd glad
   cp -rf glad/glad /usr/local/include
   cp -rf glad/KHR /usr/local/include
    ```
   这样在编译程序的时候可以查找到对应的头文件
3. 进入demo目录的src下编写代码同时创建build目录执行编译并运行程序
    ```
    mkdir build && cd build
    cmake ..
    make
    ./demo
    ```