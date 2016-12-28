#include <GL/glfw.h>

namespace MihTech
{
  class Direction
  {
    private:
      GLfloat _Position[3];
      GLfloat _Direction[3];
      GLfloat _BaseDirection[3];
      GLfloat _CamUp[3];
			GLfloat _SphereRadius;
			GLfloat *_settings;
    public:
      Camera();
      Camera(GLfloat X, GLfloat Y, GLfloat Z);
      ~Camera();

			void SetPosition(GLfloat X, GLfloat Y, GLfloat Z);
      void Move(GLfloat X, GLfloat Y, GLfloat Z);
      void Direction(GLfloat X, GLfloat Y, GLfloat Z);
      void SetUpSide(GLfloat X, GLfloat Y, GLfloat Z);

      GLfloat* GetSettings();
  };
}

