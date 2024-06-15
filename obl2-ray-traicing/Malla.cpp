#include "Malla.h"
#include "objloader.h"

void compute_max_min_vector(MathVector v, float& max_x, float& min_x,
    float& max_y, float& min_y, float& max_z, float& min_z, bool force) {

    if (force || v.x > max_x) {
        max_x = v.x;
    }

    if (force || v.x < min_x) {
        min_x = v.x;
    }

    if (force || v.y > max_y) {
        max_y = v.y;
    }

    if (force || v.y < min_y) {
        min_y = v.y;
    }

    if (force || v.z > max_z) {
        max_z = v.z;
    }

    if (force || v.z < min_z) {
        min_z = v.z;
    }

}

MallaClass::MallaClass(const char* path, MathVector traslacion, float escalar, const char* nomArchivoTextura) : Objeto() {
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> verticess;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    loadAssImp(path, indices, verticess, uvs, normals);

    int cantTriangulos = verticess.size() / 3;

    bool first = true;

    float max_x, min_x; 
    float max_y, min_y;
    float max_z, min_z;

    FIBITMAP* bitmap = nullptr;
    
    if (nomArchivoTextura != nullptr) {
        bitmap  = cargarImagen(nomArchivoTextura);
    }
    

    for (int i = 0; i < cantTriangulos; i++) {

        MathVector v1 = { verticess[i * 3].x     * escalar + traslacion.x , verticess[i * 3].y     * escalar + traslacion.y   , verticess[i * 3].z     * escalar + traslacion.z };
        compute_max_min_vector(v1, max_x, min_x, max_y, min_y, max_z, min_z, first);

        MathVector v2 = { verticess[i * 3 + 1].x * escalar + traslacion.x , verticess[i * 3 + 1].y * escalar + traslacion.y   , verticess[i * 3 + 1].z * escalar + traslacion.z };
        compute_max_min_vector(v2, max_x, min_x, max_y, min_y, max_z, min_z, first);

        MathVector v3 = { verticess[i * 3 + 2].x * escalar + traslacion.x , verticess[i * 3 + 2].y * escalar + traslacion.y   , verticess[i * 3 + 2].z * escalar + traslacion.z };
        compute_max_min_vector(v3, max_x, min_x, max_y, min_y, max_z, min_z, first);

        MathVector n_v1 = { normals[i * 3].x    , normals[i * 3].y     , normals[i * 3].z };
        MathVector n_v2 = { normals[i * 3 + 1].x, normals[i * 3 + 1].y , normals[i * 3 + 1].z };
        MathVector n_v3 = { normals[i * 3 + 2].x, normals[i * 3 + 2].y , normals[i * 3 + 2].z };
        
        if (nomArchivoTextura == nullptr) {
            triangulos.push_back(new Triangulo(v1, v2, v3, n_v1, n_v2, n_v3, { 255,255,255 }));
        }
        else {      
            MathVector t_v1 = { uvs[i * 3].x    , uvs[i * 3].y     , 0.0f };
            MathVector t_v2 = { uvs[i * 3 + 1].x, uvs[i * 3 + 1].y , 0.0f };
            MathVector t_v3 = { uvs[i * 3 + 2].x, uvs[i * 3 + 2].y , 0.0f };


            triangulos.push_back(new Triangulo(v1, v2, v3, n_v1, n_v2, n_v3, t_v1, t_v2, t_v3, bitmap, { 255,255,255 }));
        }

        

        first = false;
    }
    

    MathVector v0 = { max_x, min_y, min_z };
    MathVector v1 = { max_x, max_y, min_z };
    MathVector v2 = { min_x, max_y, min_z };
    MathVector v3 = { min_x, min_y, min_z };

    MathVector v4 = { min_x, min_y, max_z };
    MathVector v5 = { min_x, max_y, max_z };
    MathVector v6 = { max_x, max_y, max_z };
    MathVector v7 = { max_x, min_y, max_z };

    Color c = { 255,255,255 };

    volumenAcotante.push_back(new Triangulo(v0, v1, v3, c));
    volumenAcotante.push_back(new Triangulo(v2, v1, v3, c));

    volumenAcotante.push_back(new Triangulo(v2, v5, v4, c));
    volumenAcotante.push_back(new Triangulo(v2, v3, v4, c));

    volumenAcotante.push_back(new Triangulo(v1, v6, v7, c));
    volumenAcotante.push_back(new Triangulo(v1, v0, v7, c));

    volumenAcotante.push_back(new Triangulo(v5, v6, v7, c));
    volumenAcotante.push_back(new Triangulo(v5, v4, v7, c));

    volumenAcotante.push_back(new Triangulo(v2, v5, v6, c));
    volumenAcotante.push_back(new Triangulo(v2, v1, v6, c));

    volumenAcotante.push_back(new Triangulo(v3, v0, v7, c));
    volumenAcotante.push_back(new Triangulo(v3, v4, v7, c));



}

void MallaClass::intersepcion(Rayo rayo, int& idObjetoInterseptado, float& t_int) {

    bool intersepta = false;

    for (Triangulo* acc : volumenAcotante) {
        float t_a;
        int elem_a;
        acc->intersepcion(rayo, elem_a, t_a);

        if (elem_a != -1) {
            intersepta = true;
            break;
        }
    }

    if (!intersepta) {
        //printf("Salgo\n");
        idObjetoInterseptado = -1;
        t_int = -1;
        return;
    }

    t_int = -1;
    for (Triangulo* tri : triangulos) {
        float t;
        int id_choque;
        tri->intersepcion(rayo, id_choque, t);
        if (t != -1) {
            if (t_int == -1 || t_int > t) {
                t_int = t;
                idObjetoInterseptado = id_choque;
            }
        }
    }
}

MathVector MallaClass::getNormal(MathVector punto) {
    return { 0,0,0 }; // No se usa porque depende de los triangulos
}

Color MallaClass::getColorBase(MathVector punto) {
    return { 0,0,0 }; //o se usa porque depende de los triangulos
}

std::vector<Objeto*> MallaClass::getObjetosInternos() {
    std::vector<Objeto*> obj_internos;
    for (Triangulo* tri : triangulos) {
        obj_internos.push_back(tri);
    }

    return obj_internos;
}