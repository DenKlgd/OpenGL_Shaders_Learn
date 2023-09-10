#include "Shader.h"

using std::string;
using std::ifstream;
using std::ios;

GLuint Shader::compileShader(GLenum shaderType, std::string& src)
{
    const GLchar* srcPtr = src.c_str();
    GLint isCompiled = 0;
    GLchar log[512];

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &srcPtr, 0);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

    if (!isCompiled)
    {
        glGetShaderInfoLog(shader, 512, 0, log);
        glDeleteShader(shader);
        printf("Error while compiling shader: \n%s", log);
        shader = 0;
    }

    return shader;
}

GLuint Shader::createProgram(GLuint shaderID)
{
    GLuint progID = glCreateProgram();

    

    return progID;
}

Shader::Shader(const std::string& fragFileName, const std::string& vertFileName)
{
    ifstream fragFile(fragFileName, ios::binary);
    
    if (fragFile.is_open())
    {
        while (fragFile >> _fragmentSrc);
    }
    fragFile.close();


    ifstream vertexFile(vertFileName, ios::binary);

    if (vertexFile.is_open())
    {
        while (vertexFile >> _vertexSrc);
    }
    vertexFile.close();


}

Shader::~Shader()
{
}
