#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	// Inicializar GLFW
	glfwInit();

	// Indicar a GLFW qué versión de OpenGL estamos utilizando
	// En este caso estamos utilizando OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Indicar a GLFW que estamos utilizando el perfil CORE
	// Esto significa que solo tenemos las funciones modernas
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Crear un objeto GLFWwindow de 1200 por 800 píxeles, llamándolo "OpenGL_TG"
	GLFWwindow* window = glfwCreateWindow(1200, 800, "OpenGL_TG", NULL, NULL);
	// Comprobar si hubo un error al crear la ventana
	if (window == NULL)
	{
		std::cout << "Error al crear la ventana GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introducir la ventana en el contexto actual
	glfwMakeContextCurrent(window);

	// Cargar GLAD para que configure OpenGL
	gladLoadGL();
	// Especificar el área de la ventana en la que OpenGL dibujará
	// En este caso el área va desde x = 0, y = 0, hasta x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Especificar el color de fondo
	glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
	// Limpiar el buffer posterior y asignarle el nuevo color
	glClear(GL_COLOR_BUFFER_BIT);
	// Intercambiar el buffer posterior con el buffer frontal
	glfwSwapBuffers(window);

	// Bucle principal
	while (!glfwWindowShouldClose(window))
	{
		// Gestionar todos los eventos de GLFW
		glfwPollEvents();
	}

	// Eliminar la ventana antes de finalizar el programa
	glfwDestroyWindow(window);
	// Terminar GLFW antes de finalizar el programa
	glfwTerminate();
	return 0;
}