#include "baseopenglwidget.h"
#include "GL/GLU.h"
#include <math.h>

BaseOpenGLWidget::BaseOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void BaseOpenGLWidget::setMesh(myMesh *value){
    delete mesh;
    mesh = value;
    clearArgs();
    update();
}

myMesh* BaseOpenGLWidget::getMesh() const{
    return mesh;
}

void BaseOpenGLWidget::setIsDrawPoints(bool value){
    isDrawPoints = value;
    update();
}

void BaseOpenGLWidget::setIsDrawLines(bool value){
    isDrawLines = value;
    update();
}

void BaseOpenGLWidget::setIsDrawFaces(bool value){
    isDrawFaces = value;
    update();
}

void BaseOpenGLWidget::clearArgs(){
    resetViewArgs();
    rotation[0] = rotation[1] = rotation[2] = 0.0;
    translation[0] = translation[1] = 0.0;
    translation[2] = -4.0;
    update();
}

/* protected */
// 【重写】OpenGL初始化
void BaseOpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.94117647, 0.94117647, 0.94117647, 1.0);
//    glClearColor(0.0, 0.0, 0.0, 1.0);
    // 设置光照信息
    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    //设置满散射
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glEnable(GL_LIGHT0);
    GLfloat light1_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

// 【重写】OpenGL调整大小
void BaseOpenGLWidget::resizeGL(int width, int height){
    glViewport(0, 0, width, height);
}

// 【重写】OpenGL绘制
void BaseOpenGLWidget::paintGL(){
    if(mesh != nullptr){
        prepareRedraw();
        if(isDrawPoints){
            drawPoints();
        }
        if(isDrawLines){
            drawLines();
        }
        if(isDrawFaces){
            drawFaces();
        }
//        glutSwapBuffers();
    }
//    GLubyte* buffer = (GLubyte*)malloc(sizeof(GLubyte) * 3);                                        // 开辟内存
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//    glReadPixels(0, 0, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, buffer);     // 读GL的屏幕像素点到内存
//    qDebug()<<(int)buffer[0]<<(int)buffer[1]<<(int)buffer[2];
}
void BaseOpenGLWidget::resetViewArgs(){
    float bbox[2][3] = { { 1.0E30F, 1.0E30F, 1.0E30F }, { -1.0E30F, -1.0E30F, -1.0E30F } };
    for (int i = 0; i < mesh->vert_number; i++) {
        Vertex& vert = mesh->verts[i];
        if (vert.x < bbox[0][0]) bbox[0][0] = vert.x;
        else if (vert.x > bbox[1][0]) bbox[1][0] = vert.x;
        if (vert.y < bbox[0][1]) bbox[0][1] = vert.y;
        else if (vert.y > bbox[1][1]) bbox[1][1] = vert.y;
        if (vert.z < bbox[0][2]) bbox[0][2] = vert.z;
        else if (vert.z > bbox[1][2]) bbox[1][2] = vert.z;
    }
    // Setup initial viewing scale
    float dx = bbox[1][0] - bbox[0][0];
    float dy = bbox[1][1] - bbox[0][1];
    float dz = bbox[1][2] - bbox[0][2];
    scale = 4.0 / sqrt(dx * dx + dy * dy + dz * dz);
    // Setup initial viewing center
    center[0] = 0.5 * (bbox[1][0] + bbox[0][0]);
    center[1] = 0.5 * (bbox[1][1] + bbox[0][1]);
    center[2] = 0.5 * (bbox[1][2] + bbox[0][2]);
    // write mesh bounding_box
    mesh->bounding_box.xMin = bbox[0][0];
    mesh->bounding_box.xMax = bbox[1][0];
    mesh->bounding_box.yMin = bbox[0][1];
    mesh->bounding_box.yMax = bbox[1][1];
    mesh->bounding_box.zMin = bbox[0][2];
    mesh->bounding_box.zMax = bbox[1][2];
    mesh->bounding_box.dx = dx;
    mesh->bounding_box.dy = dy;
    mesh->bounding_box.dz = dz;
    mesh->bounding_box.centre.x = center[0];
    mesh->bounding_box.centre.y = center[1];
    mesh->bounding_box.centre.z = center[2];
    mesh->bounding_box.scale = scale;
}

void BaseOpenGLWidget::prepareRedraw(){
    //进行空间的重绘
    glLoadIdentity();
    glScalef(scale, scale, scale);
    glTranslatef(translation[0], translation[1], 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width() / (GLfloat)height(), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(translation[0], translation[1], translation[2]);
    glScalef(scale, scale, scale);
    //刷新放缩的大小
    glRotatef(rotation[0], 1.0, 0.0, 0.0);
    glRotatef(rotation[1], 0.0, 1.0, 0.0);          //控制不同角度
    glRotatef(rotation[2], 0.0, 0.0, 1.0);
    glTranslatef(-center[0], -center[1], -center[2]);
    //改变旋转中心
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //设置光照
    //载入不同光源的位置
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    //定义材料信息
    //这里可以调整环境颜色和散射颜色数组
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, my_set_material);
}

void BaseOpenGLWidget::drawPoints(){
//    glColor3f(0.0, 1.0, 0.0);
    glPointSize(2);
    glBegin(GL_POINTS);
    for(int j = 0; j < mesh->vert_number; j++){
        glVertex3f(mesh->verts[j].x, mesh->verts[j].y, mesh->verts[j].z);
    }
    glEnd();
}

void BaseOpenGLWidget::drawLines(){
    double temp_x, temp_y, temp_z;
    for(int i = 0; i < mesh->face_number; i++){
        Face& face = mesh->faces[i];
//        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        for(int j = 0; j < face.vert_number; j++){
            Vertex* vert = face.verts[j];
            if(j == 0){
                temp_x = vert->x;
                temp_y = vert->y;
                temp_z = vert->z;
                continue;
            }
        glVertex3f(temp_x, temp_y, temp_z);
        glVertex3f(vert->x, vert->y, vert->z);
        temp_x = vert->x;
        temp_y = vert->y;
        temp_z = vert->z;
        }
        glEnd();
    }
}

void BaseOpenGLWidget::drawFaces(){
    for(int i = 0; i < mesh->face_number; i++){
        //注意我们的操作都是
        Face& face = mesh->faces[i];
//        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);                //绘制多边形即可！
        //在绘制面的过程中载入我们已经计算好的法线量信息
        glNormal3fv(face.normal);           //在绘制面的时候同时载入法向量信息
        for (int j = 0; j < face.vert_number; j++) {
            Vertex* vert = face.verts[j];
            glVertex3f(vert->x, vert->y, vert->z);
        }
        glEnd();
    }
}
