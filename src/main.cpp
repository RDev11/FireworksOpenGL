#include "GL/freeglut.h" 
//#include <GL/gl.h>
//#include <functional>
#include "App.h"
#include <string_view>
#include <Windows.h>

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
    #ifndef NDEBUG
        ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    #endif // !1
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    //std::filesystem::current_path()
    //setlocale(LC_ALL, "");
    glutInit(&argc, argv);//начальная инициализация окна
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE /*| GLUT_DEPTH*/);//установка режима отображения
    glutInitWindowSize(800, 600);//размер окна
    
    //glutInitWindowPosition(200, 200);//начальная позиция на экране
    //вы заметили что вначале идут функции с приставкой glutInit...?, так вот они должны быть первыми, а потом уже все остальные ф-ии.
    glutCreateWindow("Fireworks!!!");//заголовок окна
    glClearColor(0.08f, .08f, .08f, 0);//цвет фона

    //glutFullScreen();
    //setting up PROJECTION
    //App::instance()->reshape(100,100);

    glutDisplayFunc(display);    
    glutIdleFunc(&idle);				// register Idle Function
    glutKeyboardFunc(keyboard);			// register Keyboard Handler
    glutKeyboardUpFunc(keyboardUp); // register Keyboard Handler
    glutMouseFunc(mouse);	//(butt state x y)					
                            
    //	glutButtonBoxFunc(keyboard);
    glutMotionFunc(pressedmousemoved);//- pressed and moved(x,y) 
    glutPassiveMotionFunc(mousemoved);//moved(x,y) 
    glutReshapeFunc(reshape);//(W,H)
    //glutSetCursor(GLUT_CURSOR_NONE);
    //init_gl();
    //initExtensions();//libExt


    glutMainLoop();
    return 0;
}