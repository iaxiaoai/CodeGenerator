#include "genericrender.h"

GenericRender::GenericRender()
{
}
void GenericRender::initsize(QString filename, QImage &textureImg)
{
    program_.addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,"vsrc.vert");
    program_.addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,"fsrc.frag");
    program_.link();

    ObjLoader objModelLoader;
    objModelLoader.load(filename,vertPoints_,texturePoints_,normalPoints_);
    QVector<float> points;
    points << vertPoints_ << texturePoints_ << normalPoints_;
    vbo_.create();
    vbo_.bind();
    vbo_.allocate(points.data(),points.count() * sizeof(float));

    texture_ = new QOpenGLTexture(textureImg);
    texture_->setWrapMode(QOpenGLTexture::ClampToEdge);
    texture_->setMinMagFilters(QOpenGLTexture::Nearest,QOpenGLTexture::Linear);
}

void GenericRender::render(QOpenGLExtraFunctions *f, QMatrix4x4 &pMatrix, QMatrix4x4 &vMatrix, QMatrix4x4 &mMatrix, QVector3D &cameraLocation, QVector3D &lightCation)
{
    f->glEnable(GL_DEPTH_TEST);
    program_.bind();
    vbo_.bind();
    f->glActiveTexture(GL_TEXTURE0 + 0);
    program_.setUniformValue("uPMatrix",pMatrix);
    program_.setUniformValue("uVMatrix",vMatrix);
    program_.setUniformValue("uMMatrix",mMatrix);
    program_.setUniformValue("uLightLocation",lightCation);
    program_.setUniformValue("uCamera",cameraLocation);
    program_.setUniformValue("sTexture",0);

    program_.enableAttributeArray(0);
    program_.enableAttributeArray(1);
    program_.enableAttributeArray(2);
    program_.setAttributeBuffer(0,GL_FLOAT,0,3,3*sizeof(GLfloat));
    program_.setAttributeBuffer(1,GL_FLOAT,vertPoints_.count() * sizeof(GLfloat),2,2*sizeof(GLfloat));
    program_.setAttributeBuffer(2,GL_FLOAT,(vertPoints_.count() + texturePoints_.count()) * sizeof(GLfloat),3,3*sizeof(GLfloat));
    texture_->bind(0);
    f->glDrawArrays(GL_TRIANGLES,0,vertPoints_.count()/3);

    program_.disableAttributeArray(0);
    program_.disableAttributeArray(1);
    program_.disableAttributeArray(2);
    texture_->release();
    vbo_.release();
    program_.release();
    f->glDisable(GL_DEPTH_TEST);
}
