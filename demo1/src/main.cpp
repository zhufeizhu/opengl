#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*窗口大小改变的回调函数*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

/*片段着色器源码*/
const char* fragmentShaderSource  = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main(){\n"
                                    "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
                                    "}\0";
/*顶点着色器源码*/
const char* vertexShaderSource    = "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main(){\n"
                                    "   gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
                                    "}\0";
int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800,600,"demo1",NULL,NULL);
    if (!window) {
        std::cout<<"create window failed"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    /**----------------------顶点着色器----------------------**/
    /*创建一个shader*/
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    /*将shader与其源码进行绑定*/
    /**
     * param1:需要编译的shader
     * param2:源码字符串的数量
     * param3:需要编译的源码
     * param4:
    **/
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);

    /*编译shader源码*/
    glCompileShader(vertexShader);

    int success;

    char infoLog[512];

    /*获取编译的结果*/
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);

    if (!success) {
        /*如果编译失败，将报错信息保存在infoLog中*/
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout<<"VERTEX SHADER COMPLIE FIALED"<<infoLog<<std::endl;
    }

    /**----------------------片段着色器----------------------**/
    /*片段着色器所做的是计算像素最后的颜色输出*/
    unsigned int fragmentShader;
    
    /*创建片段着色器*/
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    /*将片段着色器与对应源码绑定*/
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);

    /*编译片段着色器*/
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout<<"FRAGMENT SHADER COMPLIE FIALED"<<infoLog<<std::endl;
    }

    /**----------------------着色器程序----------------------**/
    /*将编译好的着色器链接为一个着色器程序*/
    unsigned int shaderProgram;

    /*创建着色器程序*/
    shaderProgram = glCreateProgram();

    /*将之前编译的着色器与当前着色器程序相绑定*/
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);

    /*将以上进行链接*/
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout<<"SHADER PROGRAM LINK FIALED"<<infoLog<<std::endl;
    }

    /*生成着色器程序后不需要着色器，将其删除*/
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    unsigned int VBO, VAO;

    /*生成VAO和VBO*/
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    /*绑定当前要操作的VAO*/
    glBindVertexArray(VAO);

    /*将VBO绑定到之前绑定的VAO中*/
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    /*因为之前已经执行了glBindBuffer,因此当前操作的对象就是VBO的ARRAY_BUFFER,下面的glBufferData不需要指定对象*/
    /*该函数将数据传输到了GPU的显存中，同时由VBO进行管理*/
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    /**
     * 该函数告诉OpenGL如何解析顶点数据,这里就是解析的就是传输到当前绑定对象的数据，具体为顶点的坐标，需要按照一定的格式来解析它
     * param1:指定配置的顶点属性
     * param2:指定顶点属性的大小,当前为vec3,因此为3
     * param3:指定参数的类型，在GLSL中均为FLOAT
     * param4:是否希望数据被标准化
     * param5:连续的顶点属性组之间的间隔
     * param6:表示位置数据在缓冲中起始位置的偏移量(Offset)
    **/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    /*进行解绑定*/
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        /*处理输入事件*/
        processInput(window);


        /*清除当前窗口并设置当前窗口的颜色为某个颜色*/
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*激活着色器程序*/
        glUseProgram(shaderProgram);

        /*因为初始阶段已经将VAO的数据和操作绑定好了,现在需要使用的时候直接绑定当current即可*/
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    /*清除VAO,VBO以及着色器程序*/
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) /*判读是否按下了esc键位*/
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}