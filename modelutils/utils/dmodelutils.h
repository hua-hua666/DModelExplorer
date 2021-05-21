#ifndef DMODELUTILS_H
#define DMODELUTILS_H

#include <QObject>
#include <string>
#include <vector>

// 定义顶点数据结构
struct Vertex {
    float x, y, z;
};

// 定义面片数据结构，仅考虑三角形面的结构体
struct Face {
    Face(void) : vert_number(0), verts(0) {};       // 构造
    int vert_number;                                // 记录顶点的个数
    Vertex** verts;                                 // 这是一个面的所有 顶点数组（含有坐标）
    float normal[3];                                // 记录点的法向量，分别是x，y，z三个方向，需要通过计算得到
};

// 定义包围盒结构
struct BoundingBox{
    BoundingBox(void) : xMax(0), xMin(0), yMax(0), yMin(0), zMax(0), zMin(0) {};    // 构造
    float xMax, xMin, yMax, yMin, zMax, zMin;                           // 六方向包围盒
    float dx, dy, dz;                                                   // 三方向跨度
    Vertex centre;                                                      // 包围盒中心
    float scale;                                                        // 缩放比例
};

// 定义网格数据结构
struct myMesh {
    myMesh(void) : vert_number(0), verts(0), face_number(0), original_face_number(0), faces(0) {};   // 构造
    int vert_number;                                                        // 总的顶点个数
    Vertex* verts;                                                          // 点数组
    int face_number;                                                        // 面的数目
    int original_face_number;                                               // 面的数目
    Face* faces;                                                            // 面数组
    BoundingBox bounding_box;                                               // 包围盒
};

class DModelUtils
{
public:
    explicit DModelUtils();
    static myMesh* readStlFile(QString fname);
    static myMesh* readObjFile(QString fname);
    static myMesh* readOffFile(QString fname);

private:
    static void get_normal(Face& face);
    static std::vector<std::string> mySplit(const std::string& str, const std::string& pattern);
    static myMesh* ReadASCII(const char* cfilename);
    static myMesh* ReadBinary(const char* cfilename);
};

#endif // DMODELUTILS_H
