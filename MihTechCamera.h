
#include <GL/glfw.h>
#include <math.h>
#include <stdio.h>

namespace MihTech
{
	#define RAD_IN_DEGREE 0.01745329251994329576923690768489

  class Point3
  {
    public:
      GLfloat x,y,z;
  };

  class Vector3
  {
    public:
      GLfloat x,y,z;
      void set(GLfloat dx, GLfloat dy, GLfloat dz){x=dx;y=dy;z=dz;}
      void set(Vector3& v3){x=v3.x;y=v3.y;z=v3.z;}
      void flip(){x=-x;y=-y;z=-z;}
      void setDiff(Point3& a, Point3& b){x=a.x-b.x; y=a.y-b.y; z=a.z-b.z;}
			void normalize();

			Vector3(GLfloat xx, GLfloat yy, GLfloat zz){x=xx;y=yy;z=zz;}
			Vector3(Vector3& v){x=v.x;y=v.y;z=v.z;}
			Vector3(){x=y=z=0;}

			Vector3 cross(Vector3 b);		//векторное произведение
			GLfloat dot(Vector3 b);			//скалярное произведение
  };

  class Camera
  {
    private:
      Point3 	_pos;
			Point3 	_viewpoint;
			Vector3 _up;
			GLfloat _settings[9];
			GLfloat _hsence;
			GLfloat _vsence;
			GLfloat _hangle;
			GLfloat _vangle;
    public:

      Camera();

      void SetPosition(GLfloat x, GLfloat y, GLfloat z);
      void SetPosition(Point3 &p);
			Point3 GetPosition(){return _pos;}

			void SetViewPoint(GLfloat hangle, GLfloat vangle);
			Point3 GetViewPoint(){return _viewpoint;}

			GLfloat GetHSence();
			void SetHSence(GLfloat x);
			GLfloat GetVSence();
			void SetVSence(GLfloat x);

			void SetUpSide(GLfloat x, GLfloat y, GLfloat z);
			void SetUpSide(Vector3 &v);

			void TurnHorizontal	(GLfloat angle, bool is_left);
			void TurnVertical		(GLfloat angle, bool is_up);

			GLfloat GetHAngle(){return _hangle;}
			GLfloat GetVAngle(){return _vangle;}

			void MoveFront(GLfloat shift, bool is_front);
			void MoveSide(GLfloat shift, bool is_left);

			GLfloat* GetSettings();

      ~Camera();
  };
}

