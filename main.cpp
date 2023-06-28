/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include<stdlib.h>
#include<math.h>
#include<stdio.h>

//*********************************************************************   FOGUETE   *********************************************************************

GLfloat tx=0.0;
GLfloat ty=-9.2;
GLfloat tz=0.0;

void foguete(GLfloat x0, GLfloat y0, GLfloat tam){
   // Corpo do foguete - Vermelho
  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
    glVertex2f(-0.2f, -0.5f);
    glVertex2f(-0.2f, 0.5f);
    glVertex2f(0.2f, 0.5f);
    glVertex2f(0.2f, -0.5f);
  glEnd();

  // Base do foguete - Rosa
  glColor3f(1.0f, 0.0f, 1.0f);
  glBegin(GL_TRIANGLES);
    glVertex2f(-0.2f, 0.5f);
    glVertex2f(0.2f, 0.5f);
    glVertex2f(0.0f, 0.8f);
  glEnd();

  // Fogo do foguete - Amarelo
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_TRIANGLES);
    glVertex2f(-0.15f, -0.5f);
    glVertex2f(-0.1f, -0.8f);
    glVertex2f(-0.05f, -0.5f);
  glEnd();

  glBegin(GL_TRIANGLES);
    glVertex2f(0.15f, -0.5f);
    glVertex2f(0.1f, -0.8f);
    glVertex2f(0.05f, -0.5f);
  glEnd();

  // Barbatanas do foguete - Azul
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f(-0.4f, -0.5f);
        glVertex2f(-0.2f, -0.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(0.4f, -0.5f);
        glVertex2f(0.2f, -0.5f);
    glEnd();

  // Janela do foguete - Azul claro
  glColor3f(0.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(0.1f, 0.2f);
    glVertex2f(0.1f, 0.1f);
  glEnd();
}

void teclado(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            if (ty + 0.1 <= 9.2) { // verifica se a nova posi��o est� dentro da janela
                ty += 0.1;
            }
            break;
        case GLUT_KEY_DOWN:
            if (ty - 0.1 >= -9.2) { // verifica se a nova posi��o est� dentro da janela
                ty -= 0.1;
            }
            break;
        case GLUT_KEY_LEFT:
            if (tx - 0.1 >= -9.0) { // verifica se a nova posi��o est� dentro da janela
                tx -= 0.1;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (tx + 0.1 <= 9.0) { // verifica se a nova posi��o est� dentro da janela
                tx += 0.1;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Marca a janela como precisando ser redesenhada
}

//*********************************************************************   METEOROS   *********************************************************************

//meteoros
#define NUM_METEOROS 50
GLfloat meteoros[NUM_METEOROS][2]; // posi��o (x,y)
GLfloat velocidade_meteoro = 0.2;

void draw_meteoro(GLfloat pos_x, GLfloat pos_y) {
  glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
    glTranslatef(pos_x, pos_y, 0.0);
    glutSolidSphere(0.3, 5, 2);
    glPopMatrix();

    float distancia = sqrt((pos_x - tx) * (pos_x - tx) + (pos_y - ty) * (pos_y - ty));
    if(pos_x > 10.0) pos_x = -10.0;
    if(pos_x < -10.0) pos_x = 10.0;
    if(pos_y > 10.0) pos_y = -10.0;
    if(pos_y < -10.0) pos_y = 10.0;

    if (distancia < 0.6) { // Valor do raio do foguete
        // Reseta a posi��o do foguete
        tx = 0.0;
        ty = -9.2;
        tz = 0.0;
    }
  glEnd();
}

void draw_meteoros() {
  for (int i = 0; i < NUM_METEOROS; i++) {
    meteoros[i][1] -= velocidade_meteoro; // move o meteoro para baixo
    if (meteoros[i][1] < -10.0) {  // se sair da tela, reposiciona acima dela
      meteoros[i][0] = (rand() % 200 - 100) / 5.0; // posi��o aleat�ria no eixo x
      meteoros[i][1] = (rand() % 80 + 20) / 5.0;   // posi��o aleat�ria no eixo y (acima da tela)
    }
    draw_meteoro(meteoros[i][0], meteoros[i][1]); // desenha o meteoro
  }
}

//*********************************************************************   ESTRELAS   *********************************************************************

void draw_estrelas() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
        GLfloat x = (rand() % 2000) / 100.0f - 10.0f; // posi��o x aleat�ria
        GLfloat y = (rand() % 2000) / 100.0f - 10.0f; // posi��o y aleat�ria
        glVertex2f(x, y); // desenha a estrela como um ponto
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(tx,ty,tz);
    foguete(0,-9.2,0); // Posiciona a figura na posi��o atual
    glPopMatrix();
    glFlush();

    draw_meteoros();
    draw_estrelas();
    glutSwapBuffers();
}

// Fun��o de atualiza��o de tempo
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

// Fun��o de inicializa��o
void init() {
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);

    //configurando uma janela
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(500,200);    // Posi��o da janela
    glutInitWindowSize(1080, 720);     // Tamanho da janela
    glutCreateWindow("Foguete em OpenGL");
    glutDisplayFunc(display); // Registra a fun��o de exibi��o
    glutSpecialFunc(teclado); // Registra a fun��o de teclado
    init();

    //iniciando variaveis
    glutTimerFunc(30, timer, 0);
    glutMainLoop();

    return EXIT_SUCCESS;

}
