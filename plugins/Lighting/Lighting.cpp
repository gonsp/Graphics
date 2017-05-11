#include "Lighting.h"
#include "glwidget.h"

void Lighting::onPluginLoad() {
	loadShaders();
} 

void Lighting::onObjectAdd() {} 

void Lighting::preFrame() {
	if(program && program->isLinked()) {
		program->bind();
		const Camera* cam=camera();
		program->setUniformValue("modelViewProjectionMatrix", cam->projectionMatrix()*cam->viewMatrix());
		program->setUniformValue("modelViewMatrix", cam->viewMatrix());
		program->setUniformValue("normalMatrix", cam->viewMatrix().normalMatrix());
	    //lightAmbient = Vector(0.1,0.1,0.1);
	    //lightDiffuse = Vector(1,1,1);
	    //lightSpecular = Vector(1,1,1);
	    //lightPosition = QVector4D(0,0,0,1);
		program->setUniformValue("lightAmbient", QVector4D(Vector(0.1,0.1,0.1),1));
		program->setUniformValue("lightDiffuse", QVector4D(Vector(1,1,1),1));
		program->setUniformValue("lightSpecular", QVector4D(Vector(1,1,1),1));
		program->setUniformValue("lightPosition", QVector4D(0,0,0,1));
	    //materialAmbient = Vector(0.8, 0.8, 0.6);
	    //materialDiffuse = Vector(0.8, 0.8, 0.6);
	    //materialSpecular = Vector(1.0, 1.0, 1.0);
	    //materialShininess = 64.0;
		program->setUniformValue("matAmbient", QVector4D(Vector(0.8, 0.8, 0.6),1));
		program->setUniformValue("matDiffuse", QVector4D(Vector(0.8, 0.8, 0.6),1));
		program->setUniformValue("matSpecular", QVector4D(Vector(1.0, 1.0, 1.0),1));
		program->setUniformValue("matShininess", GLfloat(64.0));
	}
} 

void Lighting::postFrame() {
	if(program && program->isLinked()) {
		program->release();
	}
} 

bool Lighting::paintGL() {return false;} 

bool Lighting::drawScene() {return false;} 

void Lighting::keyPressEvent(QKeyEvent *) {} 

void Lighting::keyReleaseEvent(QKeyEvent *) {} 

void Lighting::mouseMoveEvent(QMouseEvent *) {} 

void Lighting::mousePressEvent(QMouseEvent *) {} 

void Lighting::mouseReleaseEvent(QMouseEvent *) {} 

void Lighting::wheelEvent(QWheelEvent *) {}

void Lighting::loadShaders() {
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("plugins/Lighting/Lighting.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("plugins/Lighting/Lighting.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

