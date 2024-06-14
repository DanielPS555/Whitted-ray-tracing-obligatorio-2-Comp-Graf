#include "Malla.h"
#include "objloader.h"

Malla::Malla(const char* path, MathVector traslacion, float escalar) {
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> verticess;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    loadAssImp(path, indices, verticess, uvs, normals);

    int cantTriangulos = verticess.size() / 3;

    for (int i = 0; i < cantTriangulos; i++) {

        MathVector v1 = { verticess[i * 3].x     * escalar + traslacion.x , verticess[i * 3].y     * escalar + traslacion.y   , verticess[i * 3].z     * escalar + traslacion.z };
        MathVector v2 = { verticess[i * 3 + 1].x * escalar + traslacion.x , verticess[i * 3 + 1].y * escalar + traslacion.y   , verticess[i * 3 + 1].z * escalar + traslacion.z };
        MathVector v3 = { verticess[i * 3 + 2].x * escalar + traslacion.x , verticess[i * 3 + 2].y * escalar + traslacion.y   , verticess[i * 3 + 2].z * escalar + traslacion.z };

        MathVector n_v1 = { normals[i * 3].x    , normals[i * 3].y     , normals[i * 3].z };
        MathVector n_v2 = { normals[i * 3 + 1].x, normals[i * 3 + 1].y , normals[i * 3 + 1].z };
        MathVector n_v3 = { normals[i * 3 + 2].x, normals[i * 3 + 2].y , normals[i * 3 + 2].z };


        triangulos.push_back(new Triangulo(v1, v2, v3, n_v1, n_v2, n_v3, { 255,255,255 }));
    }

}

float Malla::intersepcion(Rayo rayo) {

}

MathVector Malla::getNormal(MathVector punto) {

}

std::vector<Objeto*> Malla::getObjetosInternos() {
    std::vector<Objeto*> obj_internos;
    for (Triangulo* tri : triangulos) {
        obj_internos.push_back(tri);
    }

    return obj_internos;
}