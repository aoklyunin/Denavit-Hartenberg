#include "../include/robot.h"

Robot::Robot()
{
    TH = Matrix<double, 4, 4>::Identity();
    jointCnt = 0;
}

Robot::~Robot()
{

    delete base;
    delete b1;
    delete b2;
    delete b3;
    delete b4;
    delete b5;
    delete b6;

}

void Robot::inicializar()
{
    base = new Model3D();

    b1 = new Model3D();
    b2 = new Model3D();
    b3 = new Model3D();
    b4 = new Model3D();
    b5 = new Model3D();
    b6 = new Model3D();

    base->leer("models/base.STL");
    b1->leer("models/b1.STL");
    b2->leer("models/b1.STL");
    b3->leer("models/b1.STL");
    b4->leer("models/b1.STL");
    b5->leer("models/b1.STL");
    b6->leer("models/b1.STL");


    models.push_back(base);
    models.push_back(b1);
    models.push_back(b2);
    models.push_back(b3);
    models.push_back(b4);
    models.push_back(b5);
    models.push_back(b6);

}

void Robot::rotateLink(int j, double alpha)
{
    if (j < jointCnt) {
        dhParams.at(j).at(4) += alpha;
    }
}

void Robot::configurarTH(std::string dh_file_path)
{
    Json::Reader reader;
    Json::Value obj;

    //info_msg(dh_file_path);

    std::ifstream ifs(dh_file_path.c_str(), std::ios_base::binary);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));

    reader.parse(content, obj); // reader can also read strings
    info_msg("Robot name: ", obj["name"].asString());

    const Json::Value &characters = obj["links"]; // array of characters

    jointCnt = 0;

    for (int i = 0; i < characters.size(); i++) {
        double d = characters[i]["d"].asDouble() / 10;
        double a = characters[i]["a"].asDouble() / 10;
        double alpha = characters[i]["alpha"].asDouble();
        double theta = characters[i]["theta"].asDouble();
        vector<double> dhParam{theta, d, a, alpha, 0};
        dhParams.push_back(dhParam);
        jointCnt++;
    }
}

Matrix4d getDHMatrix(vector<double> dh)
{
    double theta = dh.at(0) + dh.at(4);
    double d = dh.at(1);
    double a = dh.at(2);
    double alpha = dh.at(3);

    Matrix4d m;
    m << cos(theta), -sin(theta) * cos(alpha), sin(theta) * sin(alpha), a * cos(theta),
        sin(theta), cos(theta) * cos(alpha), -cos(theta) * sin(alpha), a * sin(theta),
        0, sin(alpha), cos(alpha), d,
        0, 0, 0, 1;
    return m;
}
void Robot::renderizar()
{

    TH = Matrix<double, 4, 4>::Identity();

    Model3D *model;

    Vector3d pos(0, 0, 0);
    Vector3d nx(1, 0, 0);
    Vector3d ny(0, 1, 0);
    Vector3d nz(0, 0, 1);


    OpenGL_wrapper::drawArrow3D(pos, pos + 4 * nx, new double[3]{1, 0.1, 0.2}, 0.3);
    OpenGL_wrapper::drawArrow3D(pos, pos + 4 * ny, new double[3]{.1, 1, 0.2}, 0.3);
    OpenGL_wrapper::drawArrow3D(pos, pos + 4 * nz, new double[3]{0.1, 0.2, 1}, 0.3);

    for (auto &dhParam : dhParams) {
        Matrix4d DH = getDHMatrix(dhParam);
        TH = TH * DH;

        Vector3d nx(TH(0, 0), TH(1, 0), TH(2, 0));
        Vector3d ny(TH(0, 1), TH(1, 1), TH(2, 1));
        Vector3d nz(TH(0, 2), TH(1, 2), TH(2, 2));

        Vector3d pos(TH(0, 3), TH(1, 3), TH(2, 3));

        // info_msg(pos);

        OpenGL_wrapper::drawArrow3D(pos, pos + 4 * nx, new double[3]{1, 0.1, 0.2}, 0.3);
        OpenGL_wrapper::drawArrow3D(pos, pos + 4 * ny, new double[3]{.1, 1, 0.2}, 0.3);
        OpenGL_wrapper::drawArrow3D(pos, pos + 4 * nz, new double[3]{0.1, 0.2, 1}, 0.3);

        model = models[1];
        glColor3d(0.5, 0.5, 0.5);

        glEnable(GL_BLEND);
        glBegin(GL_TRIANGLES);

        glFrontFace(GL_FRONT_AND_BACK);
        for (int i = 0; i < model->ntriangles; i++) {

            Vector3d v1 = model->triangleList[i].vertices[0];   //posiciones locales
            Vector3d v2 = model->triangleList[i].vertices[1];
            Vector3d v3 = model->triangleList[i].vertices[2];
            Vector4d v14(v1(0), v1(1), v1(2), 1),
                v24(v2(0), v2(1), v2(2), 1),
                v34(v3(0), v3(1), v3(2), 1);

            v14 = TH * v14;
            v24 = TH * v24;
            v34 = TH * v34;


            v1 = {v14(0), v14(1), v14(2)};
            v2 = {v24(0), v24(1), v24(2)};
            v3 = {v34(0), v34(1), v34(2)};

            OpenGL_wrapper::vectorVertex(v1);
            OpenGL_wrapper::vectorVertex(v2);
            OpenGL_wrapper::vectorVertex(v3);
        }
        glEnd();

        glDisable(GL_BLEND);

    }

}
