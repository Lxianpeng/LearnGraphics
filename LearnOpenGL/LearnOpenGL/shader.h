#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	//Shader程序ID
	unsigned int ID;
	//构造函数
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) 
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//读取数据流
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//编译着色器
		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileShader(vertex, GL_VERTEX_SHADER);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileShader(fragment, GL_FRAGMENT_SHADER);

		//创建着色器并链接
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkLinkShader(ID);

		//删除着色器
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	//激活
	void use() 
	{
		glUseProgram(ID);
	}

	void destroy()
	{
		glDeleteProgram(ID);
	}


	//uniform工具函数
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloa4(const std::string &name, const GLfloat *value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, value);
	}
	void setFloa3(const std::string &name, const GLfloat *value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, value);
	}
	void setFloa2(const std::string &name, const GLfloat *value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, value);
	}

private:

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
			printf("CompileShader=================================END=================================\n");
			return false;
		}
		printf("Succeed Compile \n");
		printf(shadertypename);
		printf(" Shader\n");
		printf("CompileShader=================================END=================================\n");
		return true;
	}

	bool checkLinkShader(unsigned int shaderProgram)
	{
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			printf("ERROR::SHADER");
			printf("::LINK_SHADER_PROGRAM");
			printf("::COMPILATION_FAILED\n");
			return false;
		}
		printf("Succeed Link Shader\n");
		return true;
	}

	
	
};





#endif