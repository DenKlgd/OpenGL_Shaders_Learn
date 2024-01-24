#include <fstream>
#include <string>
#include "glad/glad.h"


class Shader
{
private:
    std::string _fragmentSrc = "";
    std::string _vertexSrc = "";
    GLuint _fragment = 0;
    GLuint _vertex = 0;
    GLuint _program = 0;

private:
    GLuint compileShader(GLenum shaderType, std::string& src);
    GLuint createProgram();
    void unload();

public:
    void reload(const std::string& fragFileName, const std::string& vertFileName);
    GLint getUniformAttr(const char* uniformName);
    void use();
    void unuse();
    Shader() = default;
    Shader(const std::string& fragFileName, const std::string& vertFileName);
    ~Shader();
};


