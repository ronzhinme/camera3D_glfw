
#include "MihTechCamera.h"
using namespace MihTech;

Camera::Camera()
{
  SetPosition(0.0f,0.0f,0.0f);
  SetViewPoint(0.0f,0.0f);
  SetUpSide(0.0f,0.0f,0.0f);
  _hangle = 0;
  _vangle = 0;
  _hsence=1;
  _vsence=1;
}

void Camera::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
  _pos.x=x;
  _pos.y=y;
  _pos.z=z;
}

void Camera::SetPosition(Point3 &p)
{
  _pos.x=p.x;
  _pos.y=p.y;
  _pos.z=p.z;
}

void Camera::SetUpSide(GLfloat x, GLfloat y, GLfloat z)
{
  _up.x=x;
  _up.y=y;
  _up.z=z;
}

void Camera::SetUpSide(Vector3 &v)
{
  _up.x=v.x;
  _up.y=v.y;
  _up.z=v.z;
}

Camera::~Camera()
{
}

GLfloat* Camera::GetSettings()
{
  _settings[0]=_pos.x;
  _settings[1]=_pos.y;
  _settings[2]=_pos.z;

  _settings[3]=_viewpoint.x;
  _settings[4]=_viewpoint.x;
  _settings[5]=_viewpoint.x;

  _settings[6]=_up.x;
  _settings[7]=_up.x;
  _settings[8]=_up.x;

}

void Camera::TurnHorizontal	(GLfloat angle, bool is_left)
{
  if(is_left)
    {
      _hangle -= angle;
    }
  else
    {
      _hangle += angle;
    }
  SetViewPoint(_hangle,_vangle);
}

void Camera::TurnVertical(GLfloat angle, bool is_up)
{
  if(is_up)
    {
      _vangle += angle;
    }
  else
    {
      _vangle -= angle;
    }
  SetViewPoint(_hangle,_vangle);
}

void Camera::SetViewPoint(GLfloat hangle, GLfloat vangle)
{
	if(hangle!=_hangle)
	{
		_hangle=hangle;
	}
	if(vangle!=_vangle)
	{
		_vangle=vangle;
	}
  _viewpoint.x = _pos.x + _hsence*cos(hangle*RAD_IN_DEGREE)*cos(vangle*RAD_IN_DEGREE);
  _viewpoint.y = _pos.y + _vsence*sin(vangle*RAD_IN_DEGREE);
  _viewpoint.z = _pos.z + _hsence*sin(hangle*RAD_IN_DEGREE)*cos(vangle*RAD_IN_DEGREE);
#ifdef _DEBUG
  printf("Xangle:%f Yangle:%f\nCurPos:%f %f %f\nViwPos:%f %f %f\n",_hangle,_vangle,_pos.x,_pos.y,_pos.z, _viewpoint.x,_viewpoint.y,_viewpoint.z);
#endif
}

void Camera::MoveFront(GLfloat shift, bool is_front)
{
  int koef =1;
  if(!is_front)
    {
      koef=-1;
    }
  _pos.x += cos(_hangle*RAD_IN_DEGREE)*cos(_vangle*RAD_IN_DEGREE)*koef;
  _pos.y += sin(_vangle*RAD_IN_DEGREE)*koef;
  _pos.z += sin(_hangle*RAD_IN_DEGREE)*cos(_vangle*RAD_IN_DEGREE)*koef;
  SetViewPoint(_hangle,_vangle);
}

void Camera::MoveSide(GLfloat shift, bool is_left)
{
  int koef =1;
  if(!is_left)
    {
      koef=-1;
    }
  GLfloat left_angle = _hangle-90;

  _pos.x += cos(left_angle*RAD_IN_DEGREE)*koef;
  _pos.z += sin(left_angle*RAD_IN_DEGREE)*koef;
  SetViewPoint(_hangle,_vangle);
}

GLfloat Camera::GetHSence()
{
  return _hsence;
}

void Camera::SetHSence(GLfloat x)
{
  _hsence = x;
}

GLfloat Camera::GetVSence()
{
  return _vsence;
}

void Camera::SetVSence(GLfloat x)
{
  _vsence = x;
}
