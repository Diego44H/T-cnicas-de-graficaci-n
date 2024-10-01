#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Código fuente del Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Código fuente del Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.0f, 1.0f);\n" // Cambié el color del triángulo a naranja
"}\n\0";

int main()
{
    // Inicializar GLFW
    glfwInit();

    // Especificar la versión de OpenGL (3.3 en este caso)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Usamos el perfil CORE para funciones modernas
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear una ventana de 1200x1200 píxeles, llamada "OpenGL_TG"
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "OpenGL_TG", NULL, NULL);
    // Verificar si la ventana falla al crear
    if (window == NULL)
    {
        std::cout << "Falló al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introducir la ventana en el contexto actual
    glfwMakeContextCurrent(window);

    // Cargar GLAD para configurar OpenGL
    gladLoadGL();
    // Especificar el viewport de OpenGL en la ventana (desde 0, 0 hasta 1200, 1200)
    glViewport(0, 0, 1000, 1000);

    // Crear objeto de Vertex Shader y obtener su referencia
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Adjuntar el código fuente del Vertex Shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compilar el Vertex Shader
    glCompileShader(vertexShader);

    // Crear objeto de Fragment Shader y obtener su referencia
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Adjuntar el código fuente del Fragment Shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compilar el Fragment Shader
    glCompileShader(fragmentShader);

    // Crear el programa Shader y obtener su referencia
    GLuint shaderProgram = glCreateProgram();
    // Adjuntar los Shaders (Vertex y Fragment) al programa
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Vincular los Shaders al programa
    glLinkProgram(shaderProgram);

    // Eliminar los objetos de los Shaders ya que ahora están vinculados al programa
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Coordenadas de los vértices
    GLfloat vertices[] =
    {
        -0.9f, -0.9f, 0.0f, // Esquina inferior izquierda
         0.9f, -0.9f, 0.0f, // Esquina inferior derecha
         0.0f,  0.9f, 0.0f  // Esquina superior
    };

    // Crear referencias para el VAO y VBO
    GLuint VAO, VBO;

    // Generar VAO y VBO con solo 1 objeto cada uno
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Vincular el VAO actual
    glBindVertexArray(VAO);

    // Vincular el VBO, especificando que es un GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introducir los vértices en el VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configurar el atributo de los vértices para que OpenGL sepa cómo leer el VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Habilitar el atributo de los vértices
    glEnableVertexAttribArray(0);

    // Desvincular el VBO y VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Ciclo principal
    while (!glfwWindowShouldClose(window))
    {
        // Especificar el color del fondo (azul claro)
        glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
        // Limpiar el buffer trasero y asignar el nuevo color
        glClear(GL_COLOR_BUFFER_BIT);
        // Indicarle a OpenGL qué programa Shader usar
        glUseProgram(shaderProgram);
        // Vincular el VAO para que OpenGL lo use
        glBindVertexArray(VAO);
        // Dibujar el triángulo usando el primitivo GL_TRIANGLES
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Intercambiar los buffers trasero y delantero
        glfwSwapBuffers(window);
        // Manejar eventos de GLFW
        glfwPollEvents();
    }

    // Eliminar los objetos creados
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    // Eliminar la ventana antes de terminar el programa
    glfwDestroyWindow(window);
    // Terminar GLFW antes de finalizar
    glfwTerminate();
    return 0;
}
