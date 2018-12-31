#include <load_shader.hpp>

// Read the contents of a file into a string. You must free the memory pointed to
// the return value after you are finished with it.
char* read_all(const char* path, size_t* file_size) {

    // Open file pointer or throw exception
    FILE* file_handle = fopen(path, "r");
    if (!file_handle) {
        fprintf(stderr, "Error when reading %s: %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Find file size
    fseek(file_handle, 0L, SEEK_END); // Seek to end
    *file_size = ftell(file_handle); // Read head position
    rewind(file_handle); // Rewind to the beginning

    // Allocate text buffer
    char* text = (char*)malloc(*file_size);

    // Read file into buffer
    fread(text, *file_size, sizeof(char), file_handle);

    // Close file
    fclose(file_handle);

    return text;
}

// Print a log from a shader compilation step
void print_shader_log(GLuint shader_handle, GLenum status_type) {
    // Set shader info type
    GLint result = GL_FALSE;
    glGetShaderiv(shader_handle, status_type, &result);

    // Get log length
    GLint info_log_length = 0;
    glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &info_log_length);

    // If there is a log, print it
    if (info_log_length > 0) {
        char* message = (char*)malloc(info_log_length);
        glGetShaderInfoLog(shader_handle, info_log_length, NULL, message);
        fprintf(stderr, "%.*s\n", info_log_length, message);
        free(message);
    }
}

// Load a single shader from a file
GLuint load_shader(const char* path, GLenum shader_type) {
    // Read vertex shader file
    size_t source_file_size;
    char* source = read_all(path, &source_file_size);

    // Create the handle
    GLuint shader_handle = glCreateShader(shader_type);

    // Load source
    GLint source_file_size_glint = source_file_size;
    glShaderSource(shader_handle, 1, &source, &source_file_size_glint);

    // Compile
    glCompileShader(shader_handle);

    // Check
    print_shader_log(shader_handle, GL_COMPILE_STATUS);

    // Free the memory we allocated for the source file
    free(source);

    return shader_handle;
}

// Load and link a program from shader files
GLuint load_shaders(const char *vertex_file_path, const char *fragment_file_path) {
    GLuint vertex_handle = load_shader(vertex_file_path, GL_VERTEX_SHADER);
    GLuint fragment_handle = load_shader(fragment_file_path, GL_FRAGMENT_SHADER);

    // Create program handle
    GLuint program_handle = glCreateProgram();

    // Attach shaders to program
    glAttachShader(program_handle, vertex_handle);
    glAttachShader(program_handle, fragment_handle);

    // Link program
    glLinkProgram(program_handle);

    // Check program
    print_shader_log(program_handle, GL_LINK_STATUS);

    // Detach shaders
    glDetachShader(program_handle, vertex_handle);
    glDetachShader(program_handle, fragment_handle);

    // Delete handles
    glDeleteShader(vertex_handle);
    glDeleteShader(fragment_handle);

    return program_handle;
}
