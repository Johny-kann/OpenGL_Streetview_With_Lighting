#ifndef TEXTUREMAPPING_H
#define TEXTUREMAPPING_H

#include "openglwindow.h"
#include <QOpenGLShaderProgram>

class TextureMapping : public OpenGLWindow
{
    Q_OBJECT
public:
    TextureMapping(QWindow *parent = 0);
    ~TextureMapping();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;

};



#endif // TEXTUREMAPPING_H
