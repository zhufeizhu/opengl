#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    std::cout<<"window is change"<<std::endl;
    std::cout<<"width is "<<width<<std::endl;
    std::cout<<"height is "<<height<<std::endl;
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) /*判读是否按下了esc键位*/
        glfwSetWindowShouldClose(window, true);
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
        /*输入阶段*/
        processInput(window);

        /*执行渲染指令*/
        glClearColor(0.2f,0.3f,0.3f,0.2f);
        glClear(GL_COLOR_BUFFER_BIT);                   

        /*交换颜色缓冲*/
        glfwSwapBuffers(window);     

        /*检查是否触发了什么事件，如键盘鼠标输入等*/
        glfwPollEvents();       
        
    }

    glfwTerminate();
    return 0;
}