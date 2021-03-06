#include <fstream>

#include "shader.h"

namespace GGE
{
    Shader::Shader(const char *filename, GLenum shaderType) :
            shaderType(shaderType)
    {
        // TODO: Do this with logging class
        printf("Loading %s\n", filename);
        // Flush stdout buffer
        fflush(stdout);

        // Line buffer
        std::string line;

        // Stream for file
        std::ifstream shaderFileStream(filename);

        // Exit if file doesn't exist
        if (!shaderFileStream)
        {
            fprintf(stderr, "Could not open shader '%s': File Does Not Exist\n", filename);

            // Set shader ID to 0 to stop problems from occurring
            shaderID = 0;

            // Prematurely return from the constructor
            // TODO: Find a better way of doing this
            return;
        }

        while (std::getline(shaderFileStream, line))
        {
            shaderString += line;

            // Add newline if not at end of file
            if (shaderFileStream.peek() != EOF) shaderString += '\n';
        }

        // Create OpenGL Shader
        shaderID = glCreateShader(shaderType);

        // TODO: Put this in logger
        printf("Compiling %s\n", filename);
        // Flush stdout buffer
        fflush(stdout);

        // Set source for shader
        const GLchar *cShaderString = shaderString.c_str();
        glShaderSource(shaderID, 1, &cShaderString, NULL);

        // Compile
        glCompileShader(shaderID);

        // Check for error in compiling shader
        GLint compileStatus;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

        if (compileStatus != GL_TRUE)
        {
            // Get length of compiler log
            GLint compileLogLength;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &compileLogLength);

            // Get compile log
            GLchar *compileLog = new GLchar[compileLogLength + 1]; // Add 1 for null terminator
            glGetShaderInfoLog(shaderID, compileLogLength + 1, NULL, compileLog);

            // Print status
            fprintf(stderr, "Shader '%s' failed to compile:\n%s\n", filename, compileLog);

            // TODO: Figure out what to do when a shader fails to compile. It will currently just result
            // in graphical bugs
            return;
        }

        printf("%s Successfully Compiled as Shader %d\n", filename, shaderID);
        fflush(stdout);
    }

    Shader::~Shader()
    {
        glDeleteShader(shaderID);
    }

    GLuint Shader::getShaderID()
    {
        return shaderID;
    }
}