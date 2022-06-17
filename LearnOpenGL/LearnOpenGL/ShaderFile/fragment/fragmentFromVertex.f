#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
void main()
{
	FragColor = vertexColor;
	//FragColor = vec4(1.0f,0f,0f,1f);
};