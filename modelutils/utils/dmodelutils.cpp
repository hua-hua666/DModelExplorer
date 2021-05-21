#include "dmodelutils.h"
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <QDebug>

DModelUtils::DModelUtils(){

}

// 计算面的法线
void DModelUtils::get_normal(Face& face) {
    //通过公式计算
    face.normal[0] = face.normal[1] = face.normal[2] = 0;
    Vertex* v1 = face.verts[face.vert_number - 1];
    for (int i = 0; i < face.vert_number; i++) {
        Vertex* v2 = face.verts[i];
        //新建所有的点
        face.normal[0] += (v1->y - v2->y) * (v1->z + v2->z);
        face.normal[1] += (v1->z - v2->z) * (v1->x + v2->x);
        face.normal[2] += (v1->x - v2->x) * (v1->y + v2->y);
        //首先完成叉乘的工作
        v1 = v2;
    }
    //计算归一化法线
    float squared_normal_length = 0.0;
    squared_normal_length += face.normal[0] * face.normal[0];
    squared_normal_length += face.normal[1] * face.normal[1];
    squared_normal_length += face.normal[2] * face.normal[2];
    float normal_length = sqrt(squared_normal_length);
    //得到归一化长度
    if (normal_length > 1.0E-6){
        face.normal[0] /= normal_length;
        face.normal[1] /= normal_length;
        face.normal[2] /= normal_length;
    }
    //然后完成归一化任务
}

std::vector<std::string> DModelUtils::mySplit(const std::string& str, const std::string& pattern) {
    //进行字符串的切割
    //const char* convert to char*
    char* strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    std::vector<std::string> resultVec;
    char* tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL)
    {
        resultVec.push_back(std::string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }
    delete[] strc;
    return resultVec;
}

myMesh* DModelUtils::readStlFile(QString fname) {
    QByteArray ba = fname.toLatin1();
    const char *cfilename = ba.data();
    //只处理三角形足够了！
    if (cfilename == NULL)
        return 0;
    std::ifstream in(cfilename, std::ifstream::in);
    if (!in)
        return 0;
    std::string headStr;
    getline(in, headStr, ' ');
    in.close();
    if (headStr.empty())
        return 0;
    if (headStr[0] == 's')
        return ReadASCII(cfilename);
    else
        return  ReadBinary(cfilename);
}

myMesh* DModelUtils::ReadASCII(const char* cfilename) {
    std::vector<float> coorX;
    std::vector<float> coorY;
    std::vector<float> coorZ;
    int i = 0, j = 0, cnt = 0, pCnt = 4;
    char a[100];
    char str[100];
    double x = 0, y = 0, z = 0;

    std::ifstream in(cfilename, std::ifstream::in);

    if (!in)
        return 0;
    do {
        i = 0;
        cnt = 0;
        in.getline(a, 100, '\n');
        while (a[i] != '\0') {
            if (!islower((int)a[i]) && !isupper((int)a[i]) && a[i] != ' ')
                break;
            cnt++;
            i++;
        }

        while (a[cnt] != '\0') {
            str[j] = a[cnt];
            cnt++;
            j++;
        }
        str[j] = '\0';
        j = 0;
        if (sscanf(str, "%lf%lf%lf", &x, &y, &z) == 3) {
            coorX.push_back(x);
            coorY.push_back(y);
            coorZ.push_back(z);
        }
        pCnt++;
    } while (!in.eof());
    return 0;
}

myMesh* DModelUtils::ReadBinary(const char* cfilename) {
    std::vector<float> coorX;
    std::vector<float> coorY;
    std::vector<float> coorZ;
    char str[80];
    std::ifstream in(cfilename, std::ifstream::in | std::ifstream::binary);
    if (!in)
        return 0;
    //首先使用二进制读入文件
    myMesh* meshs = new myMesh();        //建立我们的mesh类
    in.read(str, 80);
    int triangles;                  //triangles 记录了三角面的数目
    in.read((char*)&triangles, sizeof(int));
    if (triangles == 0)
        return 0;
    for (int i = 0; i < triangles; i++)
    {
        //开始处理三角片  所以面的数量计数器++
        float coorXYZ[12];
        in.read((char*)coorXYZ, 12 * sizeof(float));
        for (int j = 1; j < 4; j++)
        {
            //三个四字节信息
            //分别处理每个坐标点
            coorX.push_back(coorXYZ[j * 3]);
            coorY.push_back(coorXYZ[j * 3 + 1]);
            coorZ.push_back(coorXYZ[j * 3 + 2]);
            //将点的信息压入暂存数组
            //由于stl文件特性只需要保持三个一组进行最后的划分即可！
        }
        in.read((char*)coorXYZ, 2);
    }
    in.close();
    //向结构体进行转换
    int vert_number = coorX.size();
    int face_number = triangles;
    meshs->verts = new Vertex[vert_number + 1];
    assert(meshs->verts);
    //处理点的信息
    for (int i = 0; i < vert_number; i++)
    {
        Vertex& vert = meshs->verts[meshs->vert_number++];
        vert.x = coorX[i];
        vert.y = coorY[i];
        vert.z = coorZ[i];
    }
    //处理面的信息
    meshs->faces = new Face[face_number];
    assert(meshs->faces);
    int index = 0;
    for (int i = 0; i < face_number; i++)
    {
        Face fa;
        fa.vert_number = 3;                  //这里直接设置为定3即可！ STL三角片决定的！
        fa.verts = new Vertex * [fa.vert_number];
        for (int j = 0; j < 3; j++) {
            fa.verts[j] = &meshs->verts[index++];
        }
        get_normal(fa);
        meshs->faces[meshs->face_number++] = fa;
        //首先分配第一维数组
    }
    return meshs;
}

//读取obj文件
myMesh* DModelUtils::readObjFile(QString fname) {
    std::string fname2 = fname.toStdString();
    std::string line;
    std::fstream f;
    f.open(fname2, std::ios::in);
    if (!f.is_open()) {
//        qDebug() << "文件打开出错";
    }
    std::vector<std::vector<float>> vset;
    std::vector<std::vector<int>> fset;
    int v_counter = 1;
    int f_counter = 1;
    int original_f_counter = 0;
    while (!f.eof()) {
        getline(f, line);//拿到obj文件中一行，作为一个字符串
        std::vector<std::string>parameters;
        std::string tailMark = " ";
        std::string ans = "";
        line = line.append(tailMark);
        if (line[0] != 'v' && line[0] != 'f') {
            continue;
        }
        for (int i = 0; i < line.length(); i++) {
            char ch = line[i];
            if (ch != ' ') {
                ans += ch;
            }
            else {
                if (ans != "") {
                    parameters.push_back(ans); //取出字符串中的元素，以空格切分
                    ans = "";
                }
            }
        }
        if (parameters[0] == "v") {   //如果是顶点的话
            std::vector<float>Point;
            v_counter++;
            //            cout <<atof( parameters[1].c_str()) << "--" << atof( parameters[2].c_str()) <<" --  " << atof( parameters[3].c_str());
            Point.push_back(atof(parameters[1].c_str()));
            Point.push_back(atof(parameters[2].c_str()));
            Point.push_back(atof(parameters[3].c_str()));
            vset.push_back(Point);
        }
        else if (parameters[0] == "f") {   //如果是面的话，存放顶点的索引
            original_f_counter++;
            std::vector<int>vIndexSets;          //临时存放点的集合
//            for (int i = 1; i < 4; i++) {
//                std::string x = parameters[i];
//                std::string ans = "";
//                for (int j = 0; j < x.length(); j++) {   //跳过‘/’
//                    char ch = x[j];
//                    if (ch != '/') {
//                        ans += ch;
//                    }
//                    else {
//                        break;
//                    }
//                }
//                std::vector<std::string>res = mySplit(ans, "/");
//                int index = atof(res[0].c_str());
//                index--;//因为顶点索引在obj文件中是从1开始的，而我们存放的顶点vector是从0开始的，因此要减1
//                vIndexSets.push_back(index);
//            }
//            fset.push_back(vIndexSets);
            for (int i = 1; i < parameters.size(); i++) {
                std::string x = parameters[i];
                std::string ans = "";
                for (int j = 0; j < x.length(); j++) {   //跳过‘/’
                    char ch = x[j];
                    if (ch != '/') {
                        ans += ch;
                    }
                    else {
                        break;
                    }
                }
                std::vector<std::string>res = mySplit(ans, "/");
                int index = atof(res[0].c_str());
                index--;//因为顶点索引在obj文件中是从1开始的，而我们存放的顶点vector是从0开始的，因此要减1
                vIndexSets.push_back(index);
                if(i > 2){
                    std::vector<int>vIndexTriFace;          //临时存放一个三角面
                    vIndexTriFace.push_back(vIndexSets[0]);
                    vIndexTriFace.push_back(vIndexSets[i-2]);
                    vIndexTriFace.push_back(vIndexSets[i-1]);
                    fset.push_back(vIndexTriFace);
                }
            }
        }
    }
    f.close();
    myMesh* meshs = new myMesh();        //建立我们的mesh类
//    cout << fset.size() << endl;
//    cout << vset.size() << endl;
    //向结构体进行转换
    int vert_number = vset.size();
    int face_number = fset.size();
    meshs->verts = new Vertex[vert_number + 1];
    assert(meshs->verts);
    //处理mesh的信息
    //----------------处理点的信息 --------------
    for (int i = 0; i < vset.size(); i++) {
        Vertex& vert = meshs->verts[meshs->vert_number++];
        vert.x = vset[i][0];
        vert.y = vset[i][1];
        vert.z = vset[i][2];
    }
    //----------------处理面信息 --------------
    meshs->faces = new Face[face_number];
    assert(meshs->faces);
    for (int i = 0; i < fset.size(); i++) {
        Face a;
        a.vert_number = fset[i].size();
        a.verts = new Vertex * [fset[i].size()];
        for (int j = 0; j < fset[i].size(); j++) {
            a.verts[j] = &meshs->verts[fset[i][j]];
        }
        get_normal(a);
        meshs->faces[meshs->face_number++] = a;
        //首先分配第一维数组
    }
    meshs->original_face_number = original_f_counter;
    return meshs;
}

//读取off文件
myMesh* DModelUtils::readOffFile(QString fname) {
    QByteArray ba = fname.toLatin1();
    const char *filename = ba.data();
    /*
     函数说明： 对文件进行读取,读取的是off文件
     */
    int i;
    FILE* fp;                                         //开始读入文件
    if (!(fp = fopen(filename, "r"))) {
//        qDebug() << "无法打开文件";
        return 0;
    }
    myMesh* mesh = new myMesh();        //建立我们的mesh类
    //进行读入文件的操作
    int vert_number = 0;                            //记录顶点个数
    int face_number = 0;                                    //记录面的个数
    int line_number = 0;                                   //记录边的个数
    int line_count = 0;                               //这个是我读入了几行
    char buffer[1024];
    while (fgets(buffer, 1023, fp)) {
        line_count++;
        char* bufferp = buffer;
        while (isspace(*bufferp)) bufferp++;
        if (*bufferp == '#') continue;
        if (*bufferp == '\0') continue;
        if (vert_number == 0) {
            if (!strstr(bufferp, "OFF")) {
                if ((sscanf(bufferp, "%d%d%d", &vert_number, &face_number, &line_number) != 3) || (vert_number == 0)) {
//                    qDebug() << "存在语法错误！";
                    fclose(fp);
                    return NULL;
                }
                //存储顶点的信息
//                qDebug() << "aa" << vert_number << "--" << face_number;
                mesh->verts = new Vertex[vert_number];
                assert(mesh->verts);
                //存储面的信息
                mesh->faces = new Face[face_number];
                assert(mesh->faces);
                //如果头文件信息合适那么开辟内存空间
            }
        }
        else if (mesh->vert_number < vert_number) {
            Vertex& vert = mesh->verts[mesh->vert_number++];
            if (sscanf(bufferp, "%f%f%f", &(vert.x), &(vert.y), &(vert.z)) != 3) {
//                qDebug() << "点的信息中，数据量不足（3个）";
                fclose(fp);
                return NULL;
            }
        }
        else if (mesh->face_number < face_number) {
            Face& face = mesh->faces[mesh->face_number++];          //新建一个face对象
            bufferp = strtok(bufferp, " \t");
            if (bufferp) face.vert_number = atoi(bufferp);
            else {
                fclose(fp);
                return NULL;
            }
            face.verts = new Vertex * [face.vert_number];
            //建立面的数组
            assert(face.verts);
            for (i = 0; i < face.vert_number; i++) {
                bufferp = strtok(NULL, " \t");
                if (bufferp) face.verts[i] = &(mesh->verts[atoi(bufferp)]);
                else {
                    fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
                    fclose(fp);
                    return NULL;
                }
            }
            get_normal(face);
        }
        else {
//            qDebug() << "格式存在错误！";
            break;
        }
    }
    //判断实际的 面 的数目是否和要求数目一样！
    if (face_number != mesh->face_number) {
//        qDebug() << "面的数目与实际不符";
    }
    fclose(fp);
    return mesh;
}
