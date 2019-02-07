// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
// PONER EL X86 

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

//Declaramos apuntador de ventana
GLFWwindow *window;

/*
float posicionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;

float angulo = 0.0f;

enum Direccion { Izquierda, Derecha, Arriba, Abajo };
Direccion direccionTrianguloH = Izquierda; //Horizontal
Direccion direccionTrianguloV = Abajo; //Vertical
*/

float xTriangulo = 0.0f;
float yTriangulo = 0.0f;

float velocidad = 0.8f;

double tiempoAnterior = 0.0;
double tiempoActual = 0.0;
double tiempoDiferencial = 0.0;

void dibujarTriangulo() {
	//Utilizar una matrix identidad (para darle transformaciones)
	glPushMatrix();


	//Transformaciones (el orden importa)

	glTranslatef(xTriangulo, yTriangulo, 0.0f);

	//glScalef(0.2f, 0.2f, 0.2f);
			  //(angulo, x,     y,    z)
	//glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
			   
	//Dibujar los vertices
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.8f, 0.0f);

	glVertex3f(-0.2f, -0.2f, 0);
	glVertex3f(0.2f, -0.2f, 0);
	glVertex3f(0.0f, 0.2f, 0);

	glEnd();
	
	//Soltar la matriz
	glPopMatrix();

}

void moverTriangulo() {

	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoTeclaDerecha == GLFW_PRESS) {
		xTriangulo += velocidad * tiempoDiferencial;
	}

	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoTeclaIzquierda == GLFW_PRESS) {
		xTriangulo -= velocidad * tiempoDiferencial;
	}

	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoTeclaArriba == GLFW_PRESS) {
		yTriangulo += velocidad * tiempoDiferencial;
	}

	int estadoTeclaAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoTeclaAbajo == GLFW_PRESS) {
		yTriangulo -= velocidad * tiempoDiferencial;
	}

}

void dibujar() {

	dibujarTriangulo();

}

void actualizar() {

	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;

	moverTriangulo();

	tiempoAnterior = tiempoActual;


/*
	if (angulo >= 360){
		angulo = 0.0f;
	}
	angulo += 0.1f;

	if (direccionTrianguloH == Direccion::Izquierda) {
		if (posicionXTriangulo > -0.8f) {

			posicionXTriangulo -= 0.001f;

		}
		else {
			direccionTrianguloH = Direccion::Derecha;
		}
	}

	if (direccionTrianguloH == Direccion::Derecha) {
		if (posicionXTriangulo < 0.8f) {
			posicionXTriangulo += 0.001f;
		}
		else {
			direccionTrianguloH = Direccion::Izquierda;
		}
	}

	if (direccionTrianguloV == Direccion::Arriba) {
		if (posicionYTriangulo > -0.8f) {

			posicionYTriangulo -= 0.0005f;

		}
		else {
			direccionTrianguloV = Direccion::Abajo;
		}
	}

	if (direccionTrianguloV == Direccion::Abajo) {
		if (posicionYTriangulo < 0.8f) {

			posicionYTriangulo += 0.0005f;

		}
		else {
			direccionTrianguloV = Direccion::Arriba;
		}
	}
	
*/

}

void teclado_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		xTriangulo += velocidad;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		xTriangulo -= velocidad;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		yTriangulo -= velocidad;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		yTriangulo += velocidad;
	}
}

int main()
{	

	//Si no se pudo iniciar glfw
	//terminamos ejecución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Si se pudo iniciar GLFW
	//Entonces inicializamos la ventana
	window = glfwCreateWindow(1024,768,"Ventana",NULL,NULL);

	//Si no podemos iniciar la ventana 
	//Entonces terminamos ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto, activamos funciones modernas
	//Esto solo va a funcionar si ya establecido el contexto
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {

		cout << glewGetErrorString(errorGlew);

	}

	//Variable para la version de OPENGL
	const GLubyte *versionGL = glGetString(GL_VERSION);
	//Imprimir la variable
	cout << "Versión OPENGL: " << versionGL; //Salida de C++

	//Ejecuta el evento void teclado_callback
	//glfwSetKeyCallback(window, teclado_callback);

	tiempoAnterior = glfwGetTime();

	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establece region de dibujo
		glViewport(0, 0, 1024, 768);

		//Establece el color de borrado
		glClearColor(0.2, 0.2, 1, 1);
		
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();


		//Cambiar los buffers
		glfwSwapBuffers(window);

		//Reconocer si hay entradas
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;

}

