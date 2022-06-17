//#define USE_VBO
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

	//���������������Я����������
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

	printf("���������������%d \n" , nrAttributes);



	//ָ�����ڴ�С�ı��ʱ����ú���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader uniformShader("ShaderFile/vertex/vertex.v","ShaderFile/fragment/fragmentFromUniform.f");
	Shader vertexShader("ShaderFile/vertex/vertex.v", "ShaderFile/fragment/fragmentFromVertex.f");


	//�����������Vertex Array Object��VAO
	//���㻺�����Vertex Buffer Object��VBO
	//�����������Element Buffer Object��EBO��Index Buffer Object��IBO



#ifdef USE_VBO
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

	//����VAO 
	unsigned int VAOs[2];

	//����VBO
	unsigned int VBOs[2];
	glGenVertexArrays(2, VAOs);//��ID����VAO�����������
	glGenBuffers(2, VBOs);//��ID����VBO���㻺�����

	glBindVertexArray(VAOs[0]);//��VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);//��VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//������Ķ������ݸ��Ƶ�������
																				    //GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
																				    //GL_DYNAMIC_DRAW �����ݻᱻ�ı�ܶࡣ
																				    //GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	//���ö�������ָ��
	//index���ڼ������ԣ���0��ʼȡ��0��1��2��˳���Լ����壬���綥��λ�ã���������

	//size��һ�������������ݵĸ���������ÿ����������������������ֵ��������3

	//type�������������ݵ����ͣ�����position�����е�����ȫ��Ϊfloat��������GL_FLOAT

	//normalized���Ƿ���Ҫ�Կ���æ�����ݹ�һ���� - 1�� + 1���䣬���ﲻ��Ҫ����������GL_FALSE

	//stride��������һ������ռ�е��ܵ��ֽ����������Ķ���������֮��ļ��������Ϊ����float��������sizeof(float) * 3

	//pointer����ǰָ��ָ���vertex�ڲ���ƫ���ֽ���������Ψһ�ı�ʶ����ĳ�����Ե�ƫ����

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAOs[1]);//��VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);//��VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);	//������Ķ������ݸ��Ƶ�������
																					//GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
																					//GL_DYNAMIC_DRAW �����ݻᱻ�ı�ܶࡣ
																					//GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	////���ö�������ָ��
	////������2  �������㣬ÿ������6��float  ��������ָ��������2��ȫ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	////������2  ������ָ��������2�Ķ���ɫ��  ����ɫ������float,��3��float��ʼƫ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//���VBO��VAO�İ�
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
#else
	//
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

	//�����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
	
	//////////////////////////////////////////////////////////////////////////

	//ѭ����Ⱦ֡
	while (!glfwWindowShouldClose(window))
	{
		//��Ⱦ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�趨��ɫ
		glClear(GL_COLOR_BUFFER_BIT);//���趨����ɫȥ���
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //�߿�ģʽ  Ĭ����ֱ�����  GL_FILL
		

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

		//������ɫ���棬����¼�
		glfwSwapBuffers(window);
		glfwPollEvents();

		//�ⲿ����
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