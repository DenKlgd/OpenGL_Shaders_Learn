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

GLuint Shader::createProgram()
{
    GLuint progID = glCreateProgram();
    GLint status = 0;
    GLchar log[512];

    if (!progID)
        return progID;

    if (_vertex)
        glAttachShader(progID, _vertex);
    if (_fragment)
        glAttachShader(progID, _fragment);
    
    glLinkProgram(progID);
    glGetProgramiv(progID, GL_LINK_STATUS, &status);

    if (!status)
    {
        glGetProgramInfoLog(progID, 512, 0, log);
        glDeleteProgram(progID);
        printf("Error while linking shader program: \n%s", log);
    }

    glDeleteShader(_vertex);
    glDeleteShader(_fragment);
    _vertex = 0;
    _fragment = 0;

    return progID;
}

void Shader::use()
{
    glUseProgram(_program);
}

Shader::Shader(const std::string& fragFileName, const std::string& vertFileName)
{
    ifstream fragFile(fragFileName, ios::binary);
    char chr = 0;

    if (fragFile.is_open())
    {
        while (fragFile.read(&chr, 1))
        {
            _fragmentSrc += chr;
        }
    }
    fragFile.close();


    ifstream vertexFile(vertFileName, ios::binary);

    if (vertexFile.is_open())
    {
        while (vertexFile.read(&chr, 1))
        {
            _vertexSrc += chr;
        }
    }
    vertexFile.close();


    //_vertex = compileShader(GL_VERTEX_SHADER, _vertexSrc);
    _fragment = compileShader(GL_FRAGMENT_SHADER, _fragmentSrc);

    _program = createProgram();

    use();
}

Shader::~Shader()
{
    glUseProgram(0);

    glDeleteShader(_vertex);
    glDeleteShader(_fragment);

    glDeleteProgram(_program);
}
