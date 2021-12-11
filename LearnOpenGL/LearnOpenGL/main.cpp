#include <glad/glad.h>//��װ��OpenGLApi,���и���glew(����)��//#include <GL/glew.h>
#include <GLFW/glfw3.h>//��������,�����¼��õ�
#include <iostream>
#include "Debug.h"
#include "shader.h"
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

	Shader uniformShader("ShaderFile/vertex/vertex.v","ShaderFile/fragment/fragmentFromUniform.f");
	Shader vertexShader("ShaderFile/vertex/vertex.v", "ShaderFile/fragment/fragmentFromVertex.f");


	//�����������Vertex Array Object��VAO
	//���㻺�����Vertex Buffer Object��VBO
	//�����������Element Buffer Object��EBO��Index Buffer Object��IBO

	////////////////////////////////////ʹ��VBO//////////////////////////////////////

	//��������
	float vertices[] = {
		-1.0f,-0.5f,0.0f,
		 0.0f,-0.5f,0.0f,
		 -0.5f, 0.5f,0.0f
	};

	float vertices2[] = {
		 0.0f,-0.5f,0.0f, 1.0f,0.0f,0.0f,//����
		 1.0f,-0.5f,0.0f, 0.0f,1.0f,0.0f,//����
		 0.5f, 0.5f,0.0f, 0.0f,0.0f,1.0f //����
	};

	//����VAO  VBO
	unsigned int VAOs[2],VBOs[2];
	glGenVertexArrays(2, VAOs);//��ID����VAO�����������
	glGenBuffers(2, VBOs);//��ID����VBO���㻺�����

	glBindVertexArray(VAOs[0]);//��VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);//��VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//������Ķ������ݸ��Ƶ�������
																				    //GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
																				    //GL_DYNAMIC_DRAW �����ݻᱻ�ı�ܶࡣ
																				    //GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	//���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAOs[1]);//��VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);//��VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);	//������Ķ������ݸ��Ƶ�������
																					//GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
																					//GL_DYNAMIC_DRAW �����ݻᱻ�ı�ܶࡣ
																					//GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	//���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////ʹ��EBO////////////////////////////////////////


	//float vertices[] = {
	//0.5f, 0.5f, 0.0f,   // ���Ͻ�
	//0.5f, -0.5f, 0.0f,  // ���½�
	//-0.5f, -0.5f, 0.0f, // ���½�
	//-0.5f, 0.5f, 0.0f   // ���Ͻ�
	//};

	//unsigned int indices[] = { // ע��������0��ʼ! 
	//	0, 1, 3, // ��һ��������
	//	1, 2, 3  // �ڶ���������
	//};

	//����VAO  EBO   VBO
	//unsigned int VAO,EBO,VBO;//EBO�������������
	//glGenVertexArrays(1, &VAO);//��ID����VAO���㻺�����
	//glGenBuffers(1, &VBO);//��ID����VBO���㻺�����
	//glGenBuffers(1, &EBO);//��ID����EBO���㻺�����

	//glBindVertexArray(VAO);//��VAO

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);//��VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//��EBO
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	//������Ķ������ݸ��Ƶ�������
	//																			
	//���ö�������ָ��
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);



	//////////////////////////////////////////////////////////////////////////

	//ѭ����Ⱦ֡
	while (!glfwWindowShouldClose(window))
	{
		//��Ⱦ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�趨��ɫ
		glClear(GL_COLOR_BUFFER_BIT);//���趨����ɫȥ���
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //�߿�ģʽ  Ĭ����ֱ�����  GL_FILL
		
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue);//glUniform4f(inputColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		uniformShader.use();
		GLfloat colors[4] = { 0.0f, greenValue, 0.0f, 1.0f };
		GLsizei size = 1;
		uniformShader.setFloa4("inputColor", colors);


		glBindVertexArray(VAOs[0]);
		//ʹ��VBO����
		glDrawArrays(GL_TRIANGLES,0,3);
		
		vertexShader.use();
		glBindVertexArray(VAOs[1]);
		//ʹ��VBO����
		glDrawArrays(GL_TRIANGLES, 0, 3); 

		//ʹ��EBO����
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//������ɫ���棬����¼�
		glfwSwapBuffers(window);
		glfwPollEvents();

		//�ⲿ����
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