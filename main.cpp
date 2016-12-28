
#include <GL/glfw.h>
#include "MihTechCamera.h"
using namespace MihTech;

bool    running = true;
int screen_width=1440, screen_height=900;
Camera *cam;

#define KEY_MOVE_FORWARD 	'W'
#define KEY_MOVE_REAR 		'S'
#define KEY_MOVE_LEFT			'A'
#define KEY_MOVE_RIGHT 		'D'

void drawLineXYZ(int line_length)
{
  GLfloat centpoint = 0.0f;
  GLfloat center[]= {centpoint,centpoint,centpoint};

  GLfloat xpoint, ypoint, zpoint;
  if(centpoint>=0)
    {
      xpoint=centpoint+line_length;
      ypoint=centpoint+line_length;
      zpoint=centpoint+line_length;
    }
  else
    {
      xpoint=centpoint-line_length;
      ypoint=centpoint-line_length;
      zpoint=centpoint-line_length;
    }
  GLfloat x[]= {xpoint,centpoint,centpoint};
  GLfloat y[]= {centpoint,ypoint,centpoint};
  GLfloat z[]= {centpoint,centpoint,zpoint};

  glLineWidth(5.0f);
  glBegin(GL_LINES);
  //x красный
  glColor3f(1.0f,0.0f,0.0f);
  glVertex3fv(center);
  glVertex3fv(x);
  //y зеленый
  glColor3f(0.0f,1.0f,0.0f);
  glVertex3fv(center);
  glVertex3fv(y);
  //z синий
  glColor3f(0.0f,0.0f,1.0f);
  glVertex3fv(center);
  glVertex3fv(z);
  glEnd();
  glLineWidth(1.0f);
}

void drawBox(int x, int y, int z, int width, int height, int length)
{
  int x1=x+width;
  int y1=y+height;
  int z1=z+length;

  glBegin(GL_QUADS);
  //front
  glColor3f(1.0f,0.0f,0.0f);
  glNormal3f(0.0f,0.0f,1.0f);
  glVertex3f(x ,y1,z1);
  glVertex3f(x1,y1,z1);
  glVertex3f(x1,y ,z1);
  glVertex3f(x ,y ,z1);

  //back
  glColor3f(0.5f,0.0f,0.0f);
  glVertex3f(x ,y ,z);
  glVertex3f(x1,y ,z);
  glVertex3f(x1,y1,z);
  glVertex3f(x ,y1,z);

  //Top
  glColor3f(1.0f,1.0f,1.0f);
  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(x ,y1,z);
  glVertex3f(x1,y1,z);
  glVertex3f(x1,y1,z1);
  glVertex3f(x ,y1,z1);

  //Bottom
  glColor3f(0.2f,0.2f,0.2f);
  glVertex3f(x ,y,z);
  glVertex3f(x ,y,z1);
  glVertex3f(x1,y,z1);
  glVertex3f(x1,y,z);

  //Left
  glColor3f(0.0f,0.0f,0.5f);
  glNormal3f(1.0f,0.0f,0.0f);
  glVertex3f(x1,y ,z1);
  glVertex3f(x1,y1,z1);
  glVertex3f(x1,y1,z);
  glVertex3f(x1,y ,z);

  //Right
  glColor3f(0.0f,0.0f,1.0f);
  glVertex3f(x,y1,z);
  glVertex3f(x,y1,z1);
  glVertex3f(x,y,z1);
  glVertex3f(x,y,z);

  glEnd();

}

//===================================================================
// рендеринг
//===================================================================
void render()
{
  glViewport(0, 0, screen_width, screen_height );

  // очистка
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // сцена
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(60.0f, (GLfloat)screen_width/(GLfloat)screen_height, 0.0f, 100.0f );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  // точка обзора
  Point3 cam_pos = cam->GetPosition();
  Point3 cam_eye = cam->GetViewPoint();
  gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z,
            cam_eye.x, cam_eye.y, cam_eye.z,
            0.0f, 1.0f, 0.0f );

  drawLineXYZ(10.0f);

  //пол
  glColor3f(0.0f,0.3f,0.5f);
  glBegin(GL_QUADS);
//  glNormal3f(0.0f,-1.0f,0.0f);
  glVertex3f(0.0f		,0.0f,0.0f);
  glVertex3f(200.0f	,0.0f,0.0f);
  glVertex3f(200.0f	,0.0f,200.0f);
  glVertex3f(0.0f		,0.0f,200.0f);
  glEnd();

  //крышка
  glColor3f(0.0f,0.3f,0.3f);
  glBegin(GL_QUADS);
//  glNormal3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f,	100.0f,200.0f);
  glVertex3f(200.0f,100.0f,200.0f);
  glVertex3f(200.0f,100.0f,0.0f);
  glVertex3f(0.0f,	100.0f,0.0f);
  glEnd();

    //боковина1
  glColor3f(0.3f,0.0f,0.2f);
  glBegin(GL_QUADS);
//  glNormal3f(1.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f	,200.0f);
  glVertex3f(0.0f,100.0f,200.0f);
  glVertex3f(0.0f,100.0f,0.0f);
  glVertex3f(0.0f,	0.0f,0.0f);
  glEnd();

    //боковина2
  glColor3f(0.3f,0.0f,0.3f);
  glBegin(GL_QUADS);
//  glNormal3f(0.0f,0.0f,1.0f);
	glVertex3f(200.0f,	0.0f,0.0f);
  glVertex3f(0.0f,	0.0f,0.0f);
  glVertex3f(0.0f,	100.0f,0.0f);
  glVertex3f(200.0f,100.0f,0.0f);
  glEnd();

  drawBox(0,0,0,4,4,4);
  drawBox(60,0,0,4,100,4);
  drawBox(60,0,60,4,34,4);
  drawBox(0,0,60,4,20,4);

  //свет
	//фоновый
	GLfloat backgrounglight[] = {0.2f,0.2f,0.2f,1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,backgrounglight);

	//лини€ прожектора
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3f(62.0f,0.0f,0.0f);
	glVertex3f(62.0f,34.0f,59.0f);
	glEnd();
	//прожектор
  GLfloat l_amb[] = {0.3f,0.3f,0.3f,0.0f};
  GLfloat l_dif[] = {0.5f,0.5f,0.5f,0.0f};
  GLfloat l_spe[] = {0.4f,0.4f,0.4f,0.0f};
  GLfloat l_dir[] = {0.0f,-34.0f,-60.0f,1.0f};
  GLfloat l_pos[] = {62.0f,34.0f,60.0f,1.0f};

	glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.0001);
  glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.1);
  glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,20);
  glLightfv(GL_LIGHT1,GL_AMBIENT,l_amb);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,l_dif);
  glLightfv(GL_LIGHT1,GL_SPECULAR,l_spe);
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,l_dir);
  glLightfv(GL_LIGHT1,GL_POSITION,l_pos);



/* TODO (1#1#): --изучени€--
загрузка сцены из 3ds и др форматов
ѕрозрачность
Ќаложение цветов
“ени
Ўейдеры */

}

//===================================================================
// обработка нажатий клавиатуры
//===================================================================
void CheckKeyboard()
{
  if(glfwGetKey(KEY_MOVE_FORWARD)==GLFW_PRESS)
    {
      cam->MoveFront(0.01f,true);
    }
  if(glfwGetKey(KEY_MOVE_REAR)==GLFW_PRESS)
    {
      cam->MoveFront(0.01f,false);
    }
  if(glfwGetKey(KEY_MOVE_LEFT)==GLFW_PRESS)
    {
      cam->MoveSide(0.01f,true);
    }
  if(glfwGetKey(KEY_MOVE_RIGHT)==GLFW_PRESS)
    {
      cam->MoveSide(0.01f,false);
    }
}

void key_pressed(int key, int state)
{
  if(state==GLFW_PRESS)
    {
      switch(key)
        {
          case GLFW_KEY_ESC:
            {
              running=false;
              break;
            }
          case GLFW_KEY_UP:
            {
              break;
            }
        }
    }
}

//===================================================================
// обработка движений мыши
//===================================================================
void mouse_moved(int xmousepos, int ymousepos)
{
  int centerx = screen_width/2;
  int centery = screen_height/2;

  // изменить угол горизонтали
  if(xmousepos<centerx)
    {
      GLfloat f = centerx-xmousepos;
      cam->TurnHorizontal(0.5f*f,true);//влево
    }
  else if(xmousepos>centerx)
    {
      GLfloat f = xmousepos-centerx;
      cam->TurnHorizontal(0.5f*f,false);//вправо
    }

  // изменить угол вертикали
  if(ymousepos<centery && cam->GetVAngle()<80.0f)
    {
      GLfloat f = centery-ymousepos;
      cam->TurnVertical(0.5f*f,true);//вверх
    }
  else if(ymousepos>centery && cam->GetVAngle()>-80.0f)
    {
      GLfloat f = ymousepos-centery;
      cam->TurnVertical(0.5f*f,false);//вниз
    }

  glfwSetMousePos(centerx,centery);
}

int main()
{
  cam = new Camera();
  cam->SetUpSide(0.0f,1.0f,0.0f);
  cam->SetPosition(30.0f,10.0f,30.0f);

  glfwInit();

  int window_type=GLFW_FULLSCREEN;
#ifdef _DEBUG
  window_type=GLFW_WINDOW;
#endif
  //создать окно
  if( !glfwOpenWindow( screen_width, screen_height, 32, 32, 32, 32, 32, 32, window_type ) )
    {
      glfwTerminate();
      return 0;
    }
  //опции
  glfwDisable(GLFW_MOUSE_CURSOR);
  glfwEnable(GLFW_KEY_REPEAT);

	glEnable(GL_NORMALIZE);
  glCullFace(GL_FRONT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT,GL_AMBIENT);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  glEnable(GL_LIGHTING);
//  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);

  //обработчики
  glfwSetKeyCallback(key_pressed);
  glfwSetMousePosCallback(mouse_moved);

  cam->SetViewPoint(215.0f,0.0f);

  //основной цикл
  while(running && glfwGetWindowParam(GLFW_OPENED))
    {
      render();
      glfwSwapBuffers();
      CheckKeyboard();
    }

  //завершение
  glfwTerminate();
  delete cam;
  return 0;
}
