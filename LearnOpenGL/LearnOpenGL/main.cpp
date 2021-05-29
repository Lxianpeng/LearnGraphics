#include <glad/glad.h>//封装的OpenGLApi,还有个是glew(更老)，//#include <GL/glew.h>
#include <GLFW/glfw3.h>//创建窗口,监听事件用的
#include <iostream>
#include "Debug.h"

using namespace std;

//定义宽高
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* winwod, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) 
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		
		glfwSetWindowShouldClose(window, true);//关闭opengl绘制窗口
	}
}

bool checkCompileShader(unsigned int shader, GLenum shadertype)
{
	const char* shadertypename = "";
	if (shadertype == GL_VERTEX_SHADER)
	{
		shadertypename = "VERTEX";
	}
	else
	{
		shadertypename = "FRAGMENT";
	}
	
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("ERROR::SHADER::");
		printf(shadertypename);
		printf("::COMPILATION_FAILED\n");
		printf(infoLog);
		Debug::log("123123");
		return false;
	}
	Debug::log("123123");
	printf("Succeed Compile ");
	printf(shadertypename);
	printf(" Shader\n");
	
	return true;
}

bool checkLinkShader(unsigned int shaderProgram)
{
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::");
		printf("LINK_SHADER_PROGRAM");
		printf("::COMPILATION_FAILED\n");
		return false;
	}
	printf("Succeed Link Shader");
	return true;
}
int main()
{
	
	//初始化
	glfwInit();
	//声明OPengl版本号，主版本号MAJOR，次版本号MINOR
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//使用Core模式，不向后兼容
	//GLFW_OPENGL_ANY_PROFILE
	//GLFW_OPENGL_COMPAT_PROFILE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//创建窗口
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)//失败
	{
		printf("Failed to Create GLFW window");
		glfwTerminate();//释放
		return -1;
	}
	glfwMakeContextCurrent(window);//指定当前线程主Context
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//给glad传入加载系统相关的Opengl的函数指针地址的函数
	{
		printf("Failed to Init GLAD");
		return -1;
	}
	//指定窗口大小改变的时候调用函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//顶点着色器
	const char *vertextShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}\0";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建
	glShaderSource(vertexShader, 1, &vertextShaderSource, NULL);//加载
	glCompileShader(vertexShader);//编译
	checkCompileShader(vertexShader, GL_VERTEX_SHADER);

	//像素着色器（片元着色器）
	const char *fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
		"}";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	checkCompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	//创建shader程序  是将多个shader连接的最终版本
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);//加入
	glAttachShader(shaderProgram, fragmentShader);//加入
	glLinkProgram(shaderProgram);//链接
	checkLinkShader(shaderProgram);

	glDeleteShader(vertexShader);//删除
	glDeleteShader(fragmentShader);//删除

	
	


	////////////////////////////////////使用VBO//////////////////////////////////////

	////顶点坐标
	//float vertices[] = {
	//	-0.5f,-0.5f,0.0f,
	//	 0.5f,-0.5f,0.0f,
	//	 0.0f, 0.5f,0.0f
	//};

	////定义VAO  VBO
	//unsigned int VAO,VBO;
	//glGenVertexArrays(1, &VAO);//用ID生成VAO顶点缓存对象
	//glGenBuffers(1, &VBO);//用ID生成VBO顶点缓存对象

	//glBindVertexArray(VAO);//绑定VAO

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//将定义的顶点数据复制到缓存中
	//																			//GL_STATIC_DRAW ：数据不会或几乎不会改变。
	//																			//GL_DYNAMIC_DRAW ：数据会被改变很多。
	//																			//GL_STREAM_DRAW ：数据每次绘制时都会改变。
	//														
	////设置顶点属性指针
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	////
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////使用EBO////////////////////////////////////////


	float vertices[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
	};

	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	//定义VAO  EBO   VBO
	unsigned int VAO,EBO,VBO;//EBO是索引缓存对象
	glGenVertexArrays(1, &VAO);//用ID生成VAO顶点缓存对象
	glGenBuffers(1, &VBO);//用ID生成VBO顶点缓存对象
	glGenBuffers(1, &EBO);//用ID生成EBO顶点缓存对象

	glBindVertexArray(VAO);//绑定VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	//将定义的顶点数据复制到缓存中
																				
	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//////////////////////////////////////////////////////////////////////////

	//循环渲染帧
	while (!glfwWindowShouldClose(window))
	{
		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设定颜色
		glClear(GL_COLOR_BUFFER_BIT);//用设定的颜色去填充
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 线框模式
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		//使用VBO绘制
		//glDrawArrays(GL_TRIANGLES,0,3);
		
		//使用EBO绘制
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



		//交换颜色缓存，检查事件
		glfwSwapBuffers(window);
		glfwPollEvents();

		//外部输入
		processInput(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	
	glfwTerminate();
	
	
	printf("Exit");
	return 0;
}