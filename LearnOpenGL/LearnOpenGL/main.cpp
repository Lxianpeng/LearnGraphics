//#define USE_VBO
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

	//输出单个顶点最大可携带的数据量
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

	printf("顶点最大数据量：%d \n" , nrAttributes);



	//指定窗口大小改变的时候调用函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader uniformShader("ShaderFile/vertex/vertex.v","ShaderFile/fragment/fragmentFromUniform.f");
	Shader vertexShader("ShaderFile/vertex/vertex.v", "ShaderFile/fragment/fragmentFromVertex.f");


	//顶点数组对象：Vertex Array Object，VAO
	//顶点缓冲对象：Vertex Buffer Object，VBO
	//索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO



#ifdef USE_VBO
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

	//定义VAO 
	unsigned int VAOs[2];

	//定义VBO
	unsigned int VBOs[2];
	glGenVertexArrays(2, VAOs);//用ID生成VAO顶点数组对象
	glGenBuffers(2, VBOs);//用ID生成VBO顶点缓存对象

	glBindVertexArray(VAOs[0]);//绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);//绑定VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//将定义的顶点数据复制到缓存中
																				    //GL_STATIC_DRAW ：数据不会或几乎不会改变。
																				    //GL_DYNAMIC_DRAW ：数据会被改变很多。
																				    //GL_STREAM_DRAW ：数据每次绘制时都会改变。
	//设置顶点属性指针
	//index：第几个属性，从0开始取，0，1，2，顺序自己定义，例如顶点位置，纹理，法线

	//size：一个顶点所有数据的个数，这里每个顶点有三个浮点数属性值，所以是3

	//type：顶点描述数据的类型，这里position数组中的数据全部为float，所以是GL_FLOAT

	//normalized：是否需要显卡帮忙把数据归一化到 - 1到 + 1区间，这里不需要，所以设置GL_FALSE

	//stride：步长，一个顶点占有的总的字节数，连续的顶点属性组之间的间隔，这里为两个float，所以是sizeof(float) * 3

	//pointer：当前指针指向的vertex内部的偏离字节数，可以唯一的标识顶点某个属性的偏移量

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAOs[1]);//绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);//绑定VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);	//将定义的顶点数据复制到缓存中
																					//GL_STATIC_DRAW ：数据不会或几乎不会改变。
																					//GL_DYNAMIC_DRAW ：数据会被改变很多。
																					//GL_STREAM_DRAW ：数据每次绘制时都会改变。
	////设置顶点属性指针
	////三角形2  三个顶点，每个顶点6个float  这里是先指定三角形2的全部顶点
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	////三角形2  这里是指定三角形2的顶点色，  顶点色有三个float,从3个float开始偏移
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//解除VBO和VAO的绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
#else
	//
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

	//解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
	
	//////////////////////////////////////////////////////////////////////////

	//循环渲染帧
	while (!glfwWindowShouldClose(window))
	{
		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设定颜色
		glClear(GL_COLOR_BUFFER_BIT);//用设定的颜色去填充
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模式  默认是直接填充  GL_FILL
		

#ifdef USE_VBO
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue * 10) / 2 + 0.5f;//glUniform4f(0.0f, greenValue, 0.0f, 1.0f);
		uniformShader.use();
		GLfloat colors[4] = { 0.0f, greenValue, 0.0f, 1.0f };
		uniformShader.setFloa4("inputColor", colors);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES,0,3);


		vertexShader.use();
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3); 
#else
		//vertexShader.use();

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue * 10) / 2 + 0.5f;//glUniform4f(0.0f, greenValue, 0.0f, 1.0f);
		uniformShader.use();
		GLfloat colors[4] = { 0.0f, greenValue, 0.0f, 1.0f };
		uniformShader.setFloa4("inputColor", colors);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		vertexShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
#endif

		//交换颜色缓存，检查事件
		glfwSwapBuffers(window);
		glfwPollEvents();

		//外部输入
		processInput(window);
	}

	

#ifdef USE_VBO
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
#else
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	


#endif



	uniformShader.destroy();
	vertexShader.destroy();
	
	glfwTerminate();
	
	
	printf("Exit");
	return 0;
}