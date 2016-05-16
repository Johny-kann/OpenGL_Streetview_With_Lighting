#include "texturemapping.h"
#include <QDebug>
#include <QScreen>


TextureMapping::TextureMapping(QWindow *parent):OpenGLWindow(parent)
{

}

TextureMapping::~TextureMapping()
{
    glDeleteTextures(1, &textureID);
       glDeleteBuffers(2, &vertexbuffer[0]);
       glDeleteBuffers(1, &index);
}

void TextureMapping::loadGLTexture()
{
    QImage image(":/image/Output.bmp");
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


    GLuint indices[] = {
                             0,1,2,2,3,0,
                            4,5,6,6,7,4,
                             8,9,10,10,8,11,
                            12,13,14,14,12,15,
                             16,17,18,18,16,19,
                             20,21,22,22,20,23
                           };

    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer[0]);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_data_mag), uv_data_mag,GL_STATIC_DRAW);

  qDebug()<<vertexbuffer[0]<<vertexbuffer[1]<<index;

}

void TextureMapping::loadShader()
{
    m_program = new QOpenGLShaderProgram(this);
       m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/tv2.vert");
       m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/tf2.frag");
       m_program->link();
       m_posAttr = m_program->attributeLocation("posAttr");
//       m_colAttr = m_program->attributeLocation("colAttr");
       m_texCoordAttr = m_program->attributeLocation("texCoordAttr");
       m_matrixUniform = m_program->uniformLocation("mvpMatrix");
       m_textureUniform = m_program->uniformLocation("texture");

       qDebug()<<m_posAttr<<m_colAttr<<m_texCoordAttr<<m_matrixUniform<<m_textureUniform;
}

void TextureMapping::initialize()
{

    initGeometry();
    loadGLTexture();
    loadShader();


    glEnable(GL_CULL_FACE);

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
        glViewport(0, 0, width() * retinaScale, height() * retinaScale);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);

        glDepthFunc(GL_LESS);

        m_program->bind();

        QMatrix4x4 matrix;
        matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
        matrix.translate(0, 0, -4);
 //       matrix.rotate(90,0,0,1);
        matrix.rotate(30,-1,0,0);

//        matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

        matrix.rotate(45,0,-1,0);
//        matrix.rotate(angle, 0,1,0);

        angle+=5;
        if(angle>360)
            angle %= 360;


        m_program->setUniformValue(m_matrixUniform, matrix);

        glActiveTexture(GL_TEXTURE0);

         glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
//        m_program->enableAttributeArray(m_posAttr);
        glEnableVertexAttribArray(m_posAttr);
//        m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);
        glVertexAttribPointer(m_posAttr,3,GL_FLOAT,GL_FALSE,0,(void*)0);


        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);

        glEnableVertexAttribArray(m_texCoordAttr);
        glVertexAttribPointer(m_texCoordAttr, 2, GL_FLOAT, GL_FALSE,0,(void*)0);

        glBindTexture(GL_TEXTURE_2D, textureID);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

        glDrawArrays(GL_TRIANGLES, 0, 3*2*6);
//        glDrawElements(GL_TRIANGLE_STRIP,9,GL_UNSIGNED_INT,(void*)0);
        glDisableVertexAttribArray(m_texCoordAttr);
        glDisableVertexAttribArray(m_posAttr);


        m_program->release();

        ++m_frame;
}
