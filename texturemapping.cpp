#include "texturemapping.h"
#include <QDebug>
#include <QScreen>
#include <QMouseEvent>


QVector4D LightAmbient = QVector4D(0.5f, 0.5f, 0.5f, 1.0f);
QVector4D LightDiffuse = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
QVector4D LightPosition = QVector4D(0.0f, 0.0f, 2.0f, 1.0f);
QVector4D LightModelAmbient = QVector4D(0.2, 0.2, 0.2, 1.0);
QVector4D MaterialDiffuse = QVector4D(0.8f, 0.8f, 0.8f, 1.0f);
QVector4D MaterialAmbient = QVector4D(0.2f, 0.2f, 0.2f, 1.0f);

TextureMapping::TextureMapping(QWindow *parent):OpenGLWindow(parent)
{

    camera.position(0,0,0);
    press = false;
    m_light = true;

}

TextureMapping::~TextureMapping()
{
    glDeleteTextures(1, &textureID);
       glDeleteBuffers(2, &vertexbuffer[0]);
       glDeleteBuffers(1, &index);
}

void TextureMapping::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_A: LightDiffuse+=QVector4D(0.1, 0.1, 0.1, 0.0);
                        break;
        case Qt::Key_D: LightDiffuse-=QVector4D(0.1, 0.1, 0.1, 0.0);
                        break;

//    case Qt::Key_W: LightPosition.setY(LightPosition.y() + 0.2);
//                    break;

//    case Qt::Key_S: LightPosition.setY(LightPosition.y() - 0.2);
//                    break;

    case Qt::Key_L: m_light = !m_light;
                    break;

    case Qt::Key_N: camera.addPos(0,0,0.2);
                    break;

    case Qt::Key_M: camera.addPos(0,0,-0.2);
                    break;

    default: break;
    }
    qDebug()<<LightPosition;
}

void TextureMapping::mousePressEvent(QMouseEvent *event)
{
    press = true;
    last_mouse = event->pos();
}

void TextureMapping::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - last_mouse.x();
    int dy = event->y() - last_mouse.y();

    if (event->buttons() & Qt::LeftButton) {
        camera.addAngles((double)dy/4, (double)dx/4, 0);
    }

    last_mouse = event->pos();

}

void TextureMapping::mouseReleaseEvent(QMouseEvent *event)
{
    press = false;
}

void TextureMapping::loadGLTexture()
{
//    QImage image(":/image/Output.bmp");
    QImage image(":/image/Stitched_Image.jpg");
    image = image.convertToFormat(QImage::Format_RGB888);
//    image = image.mirrored();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void TextureMapping::initGeometry()
{
    glGenBuffers(2,&vertexbuffer[0]);
    glGenBuffers(1,&index);

    GLfloat vertices[] = {
        0.5f, 0.5f, -0.5f,      //Front
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        -0.5f, -0.5f,0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,      //Back

       0.5f, 0.5f, 0.5f,
       -0.5f, 0.5f, 0.5f,
       -0.5f, -0.5f,0.5f,

        -0.5f, -0.5f, -0.5f,    //Left
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,    //Right
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,     //Top

       -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,


        -0.5f, -0.5f, -0.5f,     //Bottom
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f
    };

    GLfloat normals[] =
    {
        0.0f, 0.0f, 1.0f,           //Front
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,

    //==============================================

        0.0f, 0.0f, -1.0f,           //Back
         0.0f, 0.0f, -1.0f,
         0.0f, 0.0f, -1.0f,

        0.0f, 0.0f, -1.0f,
         0.0f, 0.0f,-1.0f,
         0.0f, 0.0f,-1.0f,

   //===============================================

        1.0f, 0.0f, 0.0f,           //Left
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
         1.0f, 0.0f,0.0f,
         1.0f, 0.0f,0.0f,

  //=================================================

        -1.0f, 0.0f, 0.0f,           //Right
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

         -1.0f, 0.0f, 0.0f,
         -1.0f, 0.0f,0.0f,
         -1.0f, 0.0f,0.0f,

   //==================================================

         0.0f, -1.0f, 0.1f,           //Up
         0.0f, -1.0f, 0.1f,
         0.0f, -1.0f, 0.1f,

         0.0f, -1.0f, 0.0f,
         0.0f, -1.0f,0.0f,
         0.0f, -1.0f,0.0f,

   //=====================================================

        0.0f, 1.0f, 0.0f,           //Down
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

          0.0f, 1.0f, 0.0f,
         0.0f, 1.0f,0.0f,
         0.0f, 1.0f,0.0f,
    };

    GLfloat uv_data_mag[] = {

        0.75f, 0.333f,
        0.75f, 0.666f,
        1.0f, 0.666f,     //Front

        1.0f, 0.666f,
        1.0f, 0.333f,
        .75f, 0.333f,

        0.25f, 0.666f,
        0.5f, 0.666f,
        0.5f, 0.333f,

        0.5f, 0.333f,
        0.25f, 0.333f,     //Back
        0.25f, 0.666f,

        0.0f, 0.666f,     //Left
        0.25f, 0.666f,
        0.25f, 0.333f,

        0.25f, 0.333f,
        0.0f, 0.333f,
        0.0f, 0.666,

        0.5f, 0.333f,     //Right
        0.5f, 0.666f,
        0.75f, 0.666f,

        0.75f, 0.666f,
        0.75f, 0.333f,
        0.5f, 0.333,


        0.5f, 0.333f,
        0.5f, 0.0f,
        0.25f, 0.0f,

        0.25f, 0.0f,
        0.25f, 0.333f,     //Top
        0.5f, 0.333f,

        0.25f, 1.0f,
        0.5f, 1.0f,
        0.5f, 0.666f,

        0.5f, 0.666f,
        0.25f, 0.666f,     //Bottom
        0.25f, 1.0f,

    };



    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer[0]);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_data_mag), uv_data_mag,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[2]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);


}

void TextureMapping::loadShader()
{
    m_program = new QOpenGLShaderProgram(this);
       m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/tv2.vert");
       m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/tf2.frag");
       m_program->link();
       m_posAttr = m_program->attributeLocation("posAttr");
       m_colAttr = m_program->uniformLocation("mvMatrix");
       m_texCoordAttr = m_program->attributeLocation("texCoordAttr");
       m_matrixUniform = m_program->uniformLocation("mvpMatrix");
       m_textureUniform = m_program->uniformLocation("texture");
       m_normalAttr = m_program->attributeLocation("normalAttr");


       qDebug()<<m_posAttr<<m_colAttr<<m_texCoordAttr<<m_matrixUniform<<m_textureUniform<<m_normalAttr;
}


void TextureMapping::initialize()
{

    initGeometry();
    loadGLTexture();
    loadShader();


 //   glEnable(GL_CULL_FACE);

    glShadeModel(GL_SMOOTH);

    glDepthFunc(GL_LESS);
//    glDepthMask(GL_TRUE);
    glEnable(GL_TEXTURE_2D);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

}

void TextureMapping::render()
{

    static int angle = 0;

    const qreal retinaScale = devicePixelRatio();
    m_program->bind();

        glViewport(0, 0, width() * retinaScale, height() * retinaScale);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_program->setUniformValue("lightPos", LightPosition);
        m_program->setUniformValue("lightDiffuse", LightDiffuse);
        m_program->setUniformValue("lightAmbient", LightAmbient);
        m_program->setUniformValue("lightModelAmbient", LightModelAmbient);
        m_program->setUniformValue("materialDiffuse", MaterialDiffuse);
        m_program->setUniformValue("materialAmbient", MaterialAmbient);
        m_program->setUniformValue("enableLight", m_light);


        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);

        glDepthFunc(GL_LESS);


        QMatrix4x4 matrix, perspective, cam_matrix;

        matrix.setToIdentity();
        perspective.setToIdentity();
        cam_matrix.setToIdentity();

 //       qDebug()<<camera.position_axis;
        cam_matrix.translate(camera.position_axis);

        perspective.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);

        matrix.translate(0, 0, 0);

        cam_matrix.rotate(camera.angle.x()*2, 1, 0, 0);
        cam_matrix.rotate(camera.angle.y()*2, 0, 1, 0);
        cam_matrix.rotate(camera.angle.z()*2, 0, 0, 1);

    //    if(!press)
   //     {
        matrix.rotate(angle, 0,1,0);

        angle+=1;
        if(angle>360)
            angle %= 360;
      //  }


       m_program->setUniformValue("mvMatrix", cam_matrix * matrix);
        m_program->setUniformValue(m_matrixUniform, perspective*cam_matrix*matrix);

        glActiveTexture(GL_TEXTURE0);

         glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);

        glEnableVertexAttribArray(m_posAttr);

        glVertexAttribPointer(m_posAttr,3,GL_FLOAT,GL_FALSE,0,(void*)0);


        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[2]);

        glEnableVertexAttribArray(m_normalAttr);
        glVertexAttribPointer(m_normalAttr, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);

        glEnableVertexAttribArray(m_texCoordAttr);
        glVertexAttribPointer(m_texCoordAttr, 2, GL_FLOAT, GL_FALSE,0,(void*)0);



        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawArrays(GL_TRIANGLES, 0, 3*2*6);
        glDisableVertexAttribArray(m_texCoordAttr);
        glDisableVertexAttribArray(m_posAttr);


        m_program->release();

        ++m_frame;
}
