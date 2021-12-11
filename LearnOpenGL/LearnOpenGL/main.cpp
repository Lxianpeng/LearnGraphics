#include <glad/glad.h>//封装的OpenGLApi,还有个是glew(更老)，//#include <GL/glew.h>
#include <GLFW/glfw3.h>//创建窗口,监听事件用的
#include <iostream>
#include "Debug.h"
#include "shader.h"
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

	Shader uniformShader("ShaderFile/vertex/vertex.v","ShaderFile/fragment/fragmentFromUniform.f");
	Shader vertexShader("ShaderFile/vertex/vertex.v", "ShaderFile/fragment/fragmentFromVertex.f");


	//顶点数组对象：Vertex Array Object，VAO
	//顶点缓冲对象：Vertex Buffer Object，VBO
	//索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO

	////////////////////////////////////使用VBO//////////////////////////////////////

	//顶点坐标
	float vertices[] = {
		-1.0f,-0.5f,0.0f,
		 0.0f,-0.5f,0.0f,
		 -0.5f, 0.5f,0.0f
	};

	float vertices2[] = {
		 0.0f,-0.5f,0.0f, 1.0f,0.0f,0.0f,//左下
		 1.0f,-0.5f,0.0f, 0.0f,1.0f,0.0f,//右下
		 0.5f, 0.5f,0.0f, 0.0f,0.0f,1.0f //顶部
	};

	//定义VAO  VBO
	unsigned int VAOs[2],VBOs[2];
	glGenVertexArrays(2, VAOs);//用ID生成VAO顶点数组对象
	glGenBuffers(2, VBOs);//用ID生成VBO顶点缓存对象

	glBindVertexArray(VAOs[0]);//绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);//绑定VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//将定义的顶点数据复制到缓存中
																				    //GL_STATIC_DRAW ：数据不会或几乎不会改变。
																				    //GL_DYNAMIC_DRAW ：数据会被改变很多。
																				    //GL_STREAM_DRAW ：数据每次绘制时都会改变。
	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAOs[1]);//绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);//绑定VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);	//将定义的顶点数据复制到缓存中
																					//GL_STATIC_DRAW ：数据不会或几乎不会改变。
																					//GL_DYNAMIC_DRAW ：数据会被改变很多。
																					//GL_STREAM_DRAW ：数据每次绘制时都会改变。
	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////使用EBO////////////////////////////////////////


	//float vertices[] = {
	//0.5f, 0.5f, 0.0f,   // 右上角
	//0.5f, -0.5f, 0.0f,  // 右下角
	//-0.5f, -0.5f, 0.0f, // 左下角
	//-0.5f, 0.5f, 0.0f   // 左上角
	//};

	//unsigned int indices[] = { // 注意索引从0开始! 
	//	0, 1, 3, // 第一个三角形
	//	1, 2, 3  // 第二个三角形
	//};

	//定义VAO  EBO   VBO
	//unsigned int VAO,EBO,VBO;//EBO是索引缓存对象
	//glGenVertexArrays(1, &VAO);//用ID生成VAO顶点缓存对象
	//glGenBuffers(1, &VBO);//用ID生成VBO顶点缓存对象
	//glGenBuffers(1, &EBO);//用ID生成EBO顶点缓存对象

	//glBindVertexArray(VAO);//绑定VAO

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定EBO
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	//将定义的顶点数据复制到缓存中
	//																			
	//设置顶点属性指针
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);



	//////////////////////////////////////////////////////////////////////////

	//循环渲染帧
	while (!glfwWindowShouldClose(window))
	{
		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设定颜色
		glClear(GL_COLOR_BUFFER_BIT);//用设定的颜色去填充
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模式  默认是直接填充  GL_FILL
		
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue);//glUniform4f(inputColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		uniformShader.use();
		GLfloat colors[4] = { 0.0f, greenValue, 0.0f, 1.0f };
		GLsizei size = 1;
		uniformShader.setFloa4("inputColor", colors);


		glBindVertexArray(VAOs[0]);
		//使用VBO绘制
		glDrawArrays(GL_TRIANGLES,0,3);
		
		vertexShader.use();
		glBindVertexArray(VAOs[1]);
		//使用VBO绘制
		glDrawArrays(GL_TRIANGLES, 0, 3); 

		//使用EBO绘制
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//交换颜色缓存，检查事件
		glfwSwapBuffers(window);
		glfwPollEvents();

		//外部输入
		processInput(window);
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	/////////////////////////////////EBO/////////////////////////////////////////
	//glDeleteBuffers(1, &EBO);

	uniformShader.destroy();
	vertexShader.destroy();
	
	glfwTerminate();
	
	
	printf("Exit");
	return 0;
}