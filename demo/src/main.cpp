#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int main(){
    /*初始化并配置GLFW*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*创建显示窗口*/
    /*函数以小写的glfw开头*/
    /*对象以大写的GLFW开头*/
    GLFWwindow *window = glfwCreateWindow(800,600,"demo1",NULL,NULL);

    if (!window) {
        std::cout<<"creat failed"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);

    /*注册窗口大小改变时的回调函数*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    /*渲染循环,保证在程序推出前不断的绘制图像并能够接受用户输入*/
    while(!glfwWindowShouldClose(window)){ /*每次循环前进行检查GLFW是否需要被退出*/
        glfwSwapBuffers(window);            /*交换颜色缓冲*/
        glfwPollEvents();                   /*检查是否处罚了什么事件，如键盘鼠标输入等*/
    }

    glfwTerminate();
    return 0;
}