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

float anguloTriangulo = 0.0f;
float anguloTrayectoria = 0.0f;
float velocidadAngular = 90;

float xCuadrado = -0.7f;
float yCuadrado = 0.7;

float velocidad = 0.9f;
float velocidadActual = 0.0f;
float aceleracion = 0.9f;
float desaceleracion = 0.2f;


double tiempoAnterior = 0.0;
double tiempoActual = 0.0;
double tiempoDiferencial = 0.0;

float rTriangulo = 1.0f;
float gTriangulo = 1.0f;
float bTriangulo = 1.0f;

void dibujarCuadrado() {
	glPushMatrix();

	//Transformaciones
	glTranslatef(xCuadrado, yCuadrado, 0.0f);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.4f, 0.5f);

	glVertex3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, 0.1f, 0.0f);

	glEnd();

	glPopMatrix();

}

void dibujarTriangulo() {
	//Utilizar una matrix identidad (para darle transformaciones)
	glPushMatrix();


	//Transformaciones (el orden importa)
	//			(angulo, x,     y,    z)
	glTranslatef(xTriangulo, yTriangulo, 0.0f);
	glRotatef(anguloTriangulo, 0.0f, 0.0f, 1.0f);
	//glScalef(0.2f, 0.2f, 0.2f);
			  
			   
	//Dibujar los vertices
	glBegin(GL_TRIANGLES);

	glColor3f(rTriangulo,gTriangulo,bTriangulo);

	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(-0.05f, -0.0f, 0.0f);
	glVertex3f(0.05f, -0.0f, 0.0f);

	glEnd();
	
	//Soltar la matriz
	glPopMatrix();

}

void moverTriangulo() {

	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoTeclaDerecha == GLFW_PRESS) {

		anguloTriangulo -= velocidadAngular * tiempoDiferencial;

		if (anguloTriangulo < 0) {

			anguloTriangulo += 360;

		}

	}

	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoTeclaIzquierda == GLFW_PRESS) {

		anguloTriangulo += velocidadAngular * tiempoDiferencial;
		
		if (anguloTriangulo > 360) {

			anguloTriangulo -= 360;

		}

	}

	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoTeclaArriba == GLFW_PRESS) {

		anguloTrayectoria = anguloTriangulo;
				
		if (velocidadActual <= velocidad) {
			velocidadActual += aceleracion * tiempoDiferencial;
		}

	}
	else {
		if (velocidadActual >= 0) {
			velocidadActual -= desaceleracion * tiempoDiferencial;

			if (velocidadActual < 0) {
				velocidadActual = 0.0f;
			}

		}

	}

	xTriangulo += cos((anguloTriangulo + 90.0f) * 3.14159f / 180.0f) * velocidadActual * tiempoDiferencial;
	if (xTriangulo < -1.1f) {
		xTriangulo += 2;
	}
	else if (xTriangulo > 1.1f) {
		xTriangulo -= 2;
	}

	yTriangulo += sin((anguloTriangulo + 90.0f) * 3.14159f / 180.0f) * velocidadActual * tiempoDiferencial;
	if (yTriangulo < -1.1f) {
		yTriangulo += 2;
	}
	else if (yTriangulo > 1.1f) {
		yTriangulo -= 2;
	}


	int estadoTeclaAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoTeclaAbajo == GLFW_PRESS) {

		yTriangulo -= velocidad * tiempoDiferencial;

	}

}

void dibujar() {

	dibujarTriangulo();
	dibujarCuadrado();

}

void checarColisiones() {
	//Si el triangulo colisiona con el cuadrado
	if (xTriangulo - 0.2f < xCuadrado + 0.1f && xTriangulo + 0.2f > xCuadrado - 0.1f && 
		yTriangulo - 0.2f < yCuadrado + 0.1f && yTriangulo + 0.2f > yCuadrado - 0.1f) {
		//cout << "Colisión " << endl;
		gTriangulo = 0.0f;
		bTriangulo = 0.0f;

		xCuadrado = (rand() % 2) - 1;
		yCuadrado = (rand() % 2) - 1;

	}
	else {

		gTriangulo = 1.0f;
		bTriangulo = 1.0f;

	}

}

void actualizar() {

	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;

	moverTriangulo();
	checarColisiones();

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

