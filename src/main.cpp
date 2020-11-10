#include "GL/freeglut.h" 
//#include <GL/gl.h>
//#include <functional>
#include "App.h"

#include <string_view>
//#include <filesystem>
//
//    // specify the clear value for the depth buffer
//    glClearDepth(1.0f);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//
//    // specify implementation-specific hints
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//
//    GLfloat amb_light[] = { 0.2, 0.2, 0.2, 1.0 };
//    GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1 };
//    GLfloat specular[] = { 0.0, 0.99, 0.0, 1 };
//
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_COLOR_MATERIAL);
//    glShadeModel(GL_SMOOTH);
//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
//    glDepthFunc(GL_LEQUAL);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glClearColor(0.3, 0.7, 0.4, 0.5);
//}

void display(){
    App::instance()->display();
}
void idle(void) {
    display();
}
void reshape(int w, int h){
    App::instance()->reshape(w, h);
}
void keyboard(unsigned char key, int mousePositionX, int mousePositionY){
    App::instance()->keyboard(key, mousePositionX, mousePositionY);
}
void keyboardUp(unsigned char key, int mousePositionX, int mousePositionY){
    App::instance()->keyboardUp(key, mousePositionX, mousePositionY);
}
void mouse(int but, int state, int X, int Y){
    App::instance()->mouseButton(but, state, X, Y);
}
void mousemoved(int X, int Y){
    App::instance()->mouseMoved(X, Y);
}
void pressedmousemoved(int X, int Y){
    App::instance()->mouseMovedPressed(X, Y);
}


int main(int argc, char* argv[])
{
    //std::filesystem::current_path()
    //setlocale(LC_ALL, "");
    glutInit(&argc, argv);//начальная инициализация окна
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE /*| GLUT_DEPTH*/);//установка режима отображения
    glutInitWindowSize(400, 400);//размер окна
    //glutInitWindowPosition(200, 200);//начальная позиция на экране
    //вы заметили что вначале идут функции с приставкой glutInit...?, так вот они должны быть первыми, а потом уже все остальные ф-ии.
    glutCreateWindow("Window");//заголовок окна
    glClearColor(0.08f, .08f, .08f, 0);//цвет фона

    //glutFullScreen();
    //setting up PROJECTION
    //App::instance()->reshape(100,100);

    //glShadeModel(GL_SMOOTH);
    //

    glutDisplayFunc(display);    
    glutIdleFunc(&idle);				// register Idle Function
    glutKeyboardFunc(keyboard);			// register Keyboard Handler
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);	//(butt state x y)					// register Keyboard Handler
    //	glutButtonBoxFunc(keyboard);
    glutMotionFunc(pressedmousemoved); //- pressed and moved(x,y) 
    glutPassiveMotionFunc(mousemoved);//moved(x,y) 
    glutReshapeFunc(reshape);//(W,H)
    //glutSetCursor(GLUT_CURSOR_NONE);
    //init_gl();
    //initExtensions();//libExt




    glutMainLoop();//запускаем всё проинициализированное, проще говоря та же ф-я main, только в данном случае glut'овская ф-я main.
    return 0;
}