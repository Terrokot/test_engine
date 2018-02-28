
#include <stdio.h>
#include <fstream>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#include "ShaderCompiler.hpp"

#include "GL.hpp"

string ShaderCompiler::shaderVersion() {
    
#if WINDOWS || MAC_OS
    return "#version 330 core";
#elif IOS
    return "#version 300 core";
#else
    NOT_IMPLEMENTED;
    return "";
#endif
}

int ShaderCompiler::compile(const string &vertexPath, const string &fragmentPath)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	string VertexShaderCode = shaderVersion();
	ifstream VertexShaderStream(vertexPath.c_str(), std::ios::in);
    
	if (VertexShaderStream.is_open())
    {
		string Line = "";
        
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
        
		VertexShaderStream.close();
	}
    else
    {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertexPath.c_str());
		getchar();
		return 0;
	}

	string FragmentShaderCode = shaderVersion();
	ifstream FragmentShaderStream(fragmentPath.c_str(), std::ios::in);
    
	if (FragmentShaderStream.is_open())
    {
		string Line = "";
        
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
        
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;
    
    Log("Compiling shader :" << vertexPath.c_str());
    
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    
	if ( InfoLogLength > 0 )
    {
		vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

    Log("Compiling shader :" << fragmentPath.c_str());

	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    
	if ( InfoLogLength > 0 )
    {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        Error(&FragmentShaderErrorMessage[0]);
	}

    Log("Linking program");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    
	if (InfoLogLength > 0)
    {
		vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        Error(&ProgramErrorMessage[0]);
	}
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}


