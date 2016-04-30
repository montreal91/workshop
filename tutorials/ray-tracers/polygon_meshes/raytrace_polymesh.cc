
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <utility>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <chrono>

#include "geometry.h"


static const float kInfinity = std::numeric_limits<float>::max();
static const float kEpsilon = 1e-8;
static const Vec3f kDefaultBackgroundColor = Vec3f(0.235294, 0.67451, 0.843137);

inline
float clamp(const float &lo, const float &hi, const float &v) {
    return std::max(lo, std::min(hi, v));
}

inline
float deg2rad(const float &deg) {
    return deg * M_PI / 180;
}

struct Options {
    uint32_t width = 640;
    uint32_t height = 480;
    float fov = 90;
    Vec3f backgroundColor = kDefaultBackgroundColor;
    Matrix44f cameraToWorld;
};

class Object {
public:
    Object() {}
    virtual ~Object() {}
    virtual bool intersect(
        const Vec3f &,
        const Vec3f &,
        float &,
        uint32_t &,
        Vec2f &
    ) const = 0;
    virtual void getSurfaceProperties(
        const Vec3f &,
        const Vec3f &,
        const uint32_t &,
        const Vec2f &,
        Vec3f &,
        Vec2f &
    ) const = 0;

};

bool rayTriangleIntersect(
    const Vec3f &orig,
    const Vec3f &dir,
    const Vec3f &v0,
    const Vec3f &v1,
    const Vec3f &v2,
    float &t,
    float &u,
    float &v
) {
    Vec3f v0v1 = v1 - v0;
    Vec3f v0v2 = v2 - v0;
    Vec3f pvec = dir.crossProduct(v0v2);
    float det = v0v1.dotProduct(pvec);

    if (fabs(det) < kEpsilon) return false;

    float invDet = 1 / det;

    Vec3f tvec = orig - v0;
    u = tvec.dotProduct(pvec) * invDet;
    if (u < 0 || u > 1) return false;

    Vec3f qvec = tvec.crossProduct(v0v1);
    v = dir.dotProduct(qvec) * invDet;
    if (v < 0 || v > 1) return false;

    t = v0v2.dotProduct(qvec) * invDet;

    return true;
}

class TriangleMesh : public Object {
public:
    // Build a triangle mest from a face index array and a vertex index array
    TriangleMesh(
        const uint32_t nfaces,
        const std::unique_ptr<uint32_t []> &faceIndex,
        const std::unique_ptr<uint32_t []> &vertsIndex,
        const std::unique_ptr<Vec3f []> &verts,
        std::unique_ptr<Vec3f []> &normals,
        std::unique_ptr<Vec2f []> &st
    ) :
    numTris(0) {
        uint32_t k = 0, maxVertexIndex = 0;

        for (uint32_t i = 0; i < nfaces; i++) {
            numTris += faceIndex[i] - 2;
            for (uint32_t j = 0; j < faceIndex[i]; j++) {
                if (vertsIndex[k + j] > maxVertexIndex) {
                    maxVertexIndex = vertsIndex[k + j];
                }
            }
            k += faceIndex[i];
        }
        maxVertexIndex += 1;

        // allocate memory to store the position of the mesh vertices
        P = std::unique_ptr<Vec3f []>(new Vec3f[maxVertexIndex]);
        for (uint32_t i = 0; i < maxVertexIndex; i++) {
            P[i] = verts[i];
        }

        // allocate memory to store triangle indices
        trisIndex = std::unique_ptr<uint32_t []>(new uint32_t [numTris * 3]);
        uint32_t l = 0;

        N = std::unique_ptr<Vec3f []>(new Vec3f[numTris * 3]);
        for (uint32_t i = 0, k = 0; i < nfaces; i++) {
            for (uint32_t j = 0; j < faceIndex[i] - 2; j++) {
                trisIndex[l] = vertsIndex[k];
                trisIndex[l + 1] = vertsIndex[k + j + 1];
                trisIndex[l + 2] = vertsIndex[k + j + 2];
                N[l] = normals[k];
                N[l + 1] = normals[k + j + 1];
                N[l + 2] = normals[k + j + 2];
                texCoordinates[l] = st[k];
                texCoordinates[l + 1] = st[k + j + 1];
                texCoordinates[l + 2] = st[k + j + 2];
                l += 3;
            }
            k += faceIndex[i];
        }
        // use move if the input geometry is already triangulated
        // N = std::move(normals);
        // sts = std::move(st);
    }

    // Test if the ray intersects this triangle mesh
    bool intersect(
        const Vec3f &orig,
        const Vec3f &dir,
        float &tNear,
        uint32_t &triIndex,
        Vec2f &uv
    ) const {
        uint32_t j = 0;
        bool isect = false;
        for (uint32_t i = 0; i < numTris; i++) {
            const Vec3f &v0 = P[trisIndex[j]];
            const Vec3f &v1 = P[trisIndex[j + 1]];
            const Vec3f &v2 = P[trisIndex[j + 2]];
            float t = kInfinity, u, v;
            if (rayTriangleIntersect(orig, dir, v0, v1, v2, t, u, v) && t < tNear) {
                tNear = t;
                uv.x = u;
                uv.y = v;
                triIndex = i;
                isect = true;
            }
            j += 3;
        }
        return isect;
    }

    void getSurfaceProperties(
        const Vec3f &hitPoint,
        const Vec3f &viewDirection,
        const uint32_t &triIndex,
        const Vec2f &uv,
        Vec3f &hitNormal,
        Vec2f &hitTextureCoordinates
    ) const {
        const Vec3f &v0 = P[trisIndex[triIndex * 3]];
        const Vec3f &v1 = P[trisIndex[triIndex * 3 + 1]];
        const Vec3f &v2 = P[trisIndex[triIndex * 3 + 2]];
        hitNormal = (v1 - v0).crossProduct(v2 - v0);
        hitNormal.normalize();

        const Vec2f &st0 = texCoordinates[triIndex * 3];
        const Vec2f &st1 = texCoordinates[triIndex * 3 + 1];
        const Vec2f &st2 = texCoordinates[triIndex * 3 + 2];
        hitTextureCoordinates = (1 - uv.x - uv.y) * st0 + uv.x * st1 + uv.y * st2;
    }

    uint32_t numTris;
    std::unique_ptr<Vec3f []> P;
    std::unique_ptr<uint32_t []> trisIndex;
    std::unique_ptr<Vec3f []> N;
    std::unique_ptr<Vec2f []> texCoordinates;
};

TriangleMesh* loadPolyMeshFromFile(const char *file) {
    std::ifstream ifs;
    try {
        ifs.open(file);
        if (ifs.fail()) throw;

        std::stringstream ss;
        ss << ifs.rdbuf();
        uint32_t numFaces;
        ss >> numFaces;
        std::unique_ptr<uint32_t []> faceIndex(new uint32_t[numFaces]);
        uint32_t vertsIndexArraySize = 0;

        // Reading face index array
        for (uint32_t i = 0; i < numFaces; i++) {
            ss >> faceIndex[i];
            vertsIndexArraySize += faceIndex[i];
        }

        std::unique_ptr<uint32_t []> vertsIndex(new uint32_t[vertsIndexArraySize]);
        uint32_t vertsArraySize = 0;

        // Reading vertex index array
        for (uint32_t i = 0; i < vertsIndexArraySize; i++) {
            ss >> vertsIndex[i];
            if (vertsIndex[i] > vertsArraySize) vertsArraySize = vertsIndex[i];
        }
        vertsArraySize += 1;

        // Reading vertices
        std::unique_ptr<Vec3f []> verts(new Vec3f[vertsArraySize]);
        for (uint32_t i = 0; i < vertsArraySize; i++) {
            ss >>verts[i].x >> verts[i].y >> verts[i].z;
        }

        // Reading normals
        std::unique_ptr<Vec3f []> normals(new Vec3f[vertsIndexArraySize]);
        for (uint32_t i = 0; i < vertsIndexArraySize; i++) {
            ss >> normals[i].x >> normals[i].y >> normals[i].z;
        }

        // Reading st coordinates
        std::unique_ptr<Vec2f []> st(new Vec2f[vertsIndexArraySize]);
        for (uint32_t i = 0; i < vertsIndexArraySize; i++) {
            ss >> st[i].x >> st[i].y;
        }

        return new TriangleMesh(numFaces, faceIndex, vertsIndex, verts, normals, st);
    } catch (...) {
        ifs.close();
    }
    ifs.close();
    return nullptr;
}

bool trace(
    const Vec3f &orig,
    const Vec3f &dir,
    const std::vector<std::unique_ptr<Object>> &objects,
    float &tNear,
    uint32_t &index,
    Vec2f &uv,
    Object **hitObject
) {
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); k++) {
        float tNearTriangle = kInfinity;
        uint32_t indexTriangle;
        Vec2f uvTriangle;
        if (objects[k]->intersect(
            orig, dir, tNearTriangle, indexTriangle, uvTriangle
        ) && tNearTriangle < tNear ) {
            *hitObject = objects[k].get();
            tNear = tNearTriangle;
            index = indexTriangle;
            uv = uvTriangle;
        }
    }
    return (*hitObject != nullptr);
}

Vec3f castRay(
    const Vec3f &orig,
    const Vec3f &dir,
    const std::vector<std::unique_ptr<Object>> &objects,
    const Options &options
) {
    Vec3f hitColor = options.backgroundColor;
    float tnear = kInfinity;
    Vec2f uv;
    uint32_t index = 0;
    Object *hitObject = nullptr;
    if (trace(orig, dir, objects, tnear, index, uv, &hitObject)) {
        Vec3f hitPoint = orig + dir * tnear;
        Vec3f hitNormal;
        Vec2f hitTexCoordinates;
        hitObject->getSurfaceProperties(
            hitPoint, dir, index, uv, hitNormal, hitTexCoordinates
        );
        float NdotView = std::max(0.0f, hitNormal.dotProduct(-dir));
        const int M = 10;
        float checker = (fmod(hitTexCoordinates.x * M, 1.0) > 0.5) ^ (fmod(
            hitTexCoordinates.y * M, 1.0
        ) < 0.5);
        float c = 0.3 * (1 - checker) + 0.7 * checker;

        hitColor = c * NdotView;
    }
    return hitColor;
}

void render(
    const Options &options,
    const std::vector<std::unique_ptr<Object>> &objects,
    const uint32_t &frame
) {
    std::unique_ptr<Vec3f []> framebuffer(new Vec3f[options.width * options.height]);
    Vec3f *pix = framebuffer.get();
    float scale = tan(deg2rad(options.fov * 0.5));
    float imageAspectRatio = options.width / (float)options.height;
    Vec3f orig;
    options.cameraToWorld.multVecMatrix(Vec3f(0), orig);
    auto timeStart = std::chrono::high_resolution_clock::now();
    for (uint32_t j = 0; j < options.height; j++) {
        for (uint32_t i = 0; i < options.width; i++) {
            // Generate primary ray direction
            float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
            Vec3f dir;
            options.cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
            dir.normalize();
            *(pix++) = castRay(orig, dir, objects, options);
        }
        fprintf(stderr, "\r%3d%c", uint32_t(j / (float)options.height * 100), '%');
    }
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto passedTime = std::chrono::duration<double, std::milli>(timeEnd - timeStart).count();
    fprintf(stderr, "\rDone: %.2f (sec)\n", passedTime / 1000);

    // Save framebuffer to file
    char buff[256];
    sprintf(buff, "out.%04d.ppm", frame);
    std::ofstream ofs;
    ofs.open(buff);
    ofs << "P6\n" << options.width << " " << options.height << "\n255\n";
    for (uint32_t i = 0; i < options.height * options.width; i++) {
        char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
        char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
        char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
        ofs << r << g << b;
    }
    ofs.close();
}

int main(int argc, char const *argv[]) {
    Options options;
    Matrix44f tmp = Matrix44f(
        0.707107, -0.331295, 0.624695, 0,
        0, 0.883452, 0.468521, 0,
        -0.707107, -0.331295, 0.624695, 0,
        -1.63871, -5.747777, -40.400412, 1
    );
    options.cameraToWorld = tmp.inverse();
    options.fov = 50.0393;

    std::vector<std::unique_ptr<Object>> objects;
    TriangleMesh *mesh = loadPolyMeshFromFile("./cow.geo");
    if (mesh != nullptr) objects.push_back(std::unique_ptr<Object>(mesh));
    render(options, objects, 0);
    return 0;
}