#include <glad/glad.h>//��װ��OpenGLApi,���и���glew(����)��//#include <GL/glew.h>
#include <GLFW/glfw3.h>//��������,�����¼��õ�
#include <iostream>
#include "Debug.h"

using namespace std;

//������
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
		
		glfwSetWindowShouldClose(window, true);//�ر�opengl���ƴ���
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
	
	//��ʼ��
	glfwInit();
	//����OPengl�汾�ţ����汾��MAJOR���ΰ汾��MINOR
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//ʹ��Coreģʽ����������
	//GLFW_OPENGL_ANY_PROFILE
	//GLFW_OPENGL_COMPAT_PROFILE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//��������
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)//ʧ��
	{
		printf("Failed to Create GLFW window");
		glfwTerminate();//�ͷ�
		return -1;
	}
	glfwMakeContextCurrent(window);//ָ����ǰ�߳���Context
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//��glad�������ϵͳ��ص�Opengl�ĺ���ָ���ַ�ĺ���
	{
		printf("Failed to Init GLAD");
		return -1;
	}
	//ָ�����ڴ�С�ı��ʱ����ú���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//������ɫ��
	const char *vertextShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}\0";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//����
	glShaderSource(vertexShader, 1, &vertextShaderSource, NULL);//����
	glCompileShader(vertexShader);//����
	checkCompileShader(vertexShader, GL_VERTEX_SHADER);

	//������ɫ����ƬԪ��ɫ����
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

	//����shader����  �ǽ����shader���ӵ����հ汾
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);//����
	glAttachShader(shaderProgram, fragmentShader);//����
	glLinkProgram(shaderProgram);//����
	checkLinkShader(shaderProgram);

	glDeleteShader(vertexShader);//ɾ��
	glDeleteShader(fragmentShader);//ɾ��

	
	


	////////////////////////////////////ʹ��VBO//////////////////////////////////////

	////��������
	//float vertices[] = {
	//	-0.5f,-0.5f,0.0f,
	//	 0.5f,-0.5f,0.0f,
	//	 0.0f, 0.5f,0.0f
	//};

	////����VAO  VBO
	//unsigned int VAO,VBO;
	//glGenVertexArrays(1, &VAO);//��ID����VAO���㻺�����
	//glGenBuffers(1, &VBO);//��ID����VBO���㻺�����

	//glBindVertexArray(VAO);//��VAO

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);//��VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//������Ķ������ݸ��Ƶ�������
	//																			//GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
	//																			//GL_DYNAMIC_DRAW �����ݻᱻ�ı�ܶࡣ
	//																			//GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	//														
	////���ö�������ָ��
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	////
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////ʹ��EBO////////////////////////////////////////


	float vertices[] = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};

	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	//����VAO  EBO   VBO
	unsigned int VAO,EBO,VBO;//EBO�������������
	glGenVertexArrays(1, &VAO);//��ID����VAO���㻺�����
	glGenBuffers(1, &VBO);//��ID����VBO���㻺�����
	glGenBuffers(1, &EBO);//��ID����EBO���㻺�����

	glBindVertexArray(VAO);//��VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//��VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//��EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	//������Ķ������ݸ��Ƶ�������
																				
	//���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//////////////////////////////////////////////////////////////////////////

	//ѭ����Ⱦ֡
	while (!glfwWindowShouldClose(window))
	{
		//��Ⱦ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�趨��ɫ
		glClear(GL_COLOR_BUFFER_BIT);//���趨����ɫȥ���
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); �߿�ģʽ
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		//ʹ��VBO����
		//glDrawArrays(GL_TRIANGLES,0,3);
		
		//ʹ��EBO����
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



		//������ɫ���棬����¼�
		glfwSwapBuffers(window);
		glfwPollEvents();

		//�ⲿ����
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