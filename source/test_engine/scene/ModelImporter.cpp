//
//  ModelImporter.cpp
//  TestEngine
//
//  Created by Vladas Zakrevskis on 2/8/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#ifdef USING_ASSIMP

#include <unordered_map>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Log.hpp"
#include "Mesh.hpp"
#include "Paths.hpp"
#include "Model.hpp"
#include "ModelImporter.hpp"

using namespace gm;
using namespace te;
using namespace scene;

static Assimp::Importer _importer;

static std::unordered_map<std::string, Mesh*> cache;

scene::Model* ModelImporter::import(const std::string& file, Image* image) {

    if (cache.find(file) != cache.end()) {
        return new scene::Model(cache[file]);
    }

    Log(std::string() + "Loading model: " + file);

    const aiScene* scene = _importer.ReadFile(Paths::models() / file,
                                              aiProcess_CalcTangentSpace       |
                                              aiProcess_Triangulate            |
                                              aiProcess_JoinIdenticalVertices  |
                                              aiProcess_SortByPType             );

    if (!scene) {
        Fatal(_importer.GetErrorString());
    }

    auto meshes = std::vector<aiMesh*> { scene->mMeshes, scene->mMeshes + scene->mNumMeshes };

    auto mesh                    = scene->mMeshes[0];
    auto has_texture_coordinates = mesh->HasTextureCoords(0);

    Vertex::Indices indices;

    Log(file);
    Log(mesh->HasTextureCoords(0));
    Logvar(scene->HasMaterials());

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const auto& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(static_cast<Vertex::Index>(face.mIndices[j]));
        }
    }

    if (image && has_texture_coordinates) {
        Vertex::Array vertices;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            vertices.emplace_back(mesh->mVertices[i],
                                  mesh->mNormals[i],
                                  Point { mesh->mTextureCoords[0][i].x, 1 - mesh->mTextureCoords[0][i].y });
        }

        return new Model(new Mesh(std::move(vertices),
                                  std::move(indices)),
                         image);
    }

    Vertex::Array vertices;


    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.emplace_back(mesh->mVertices[i],
                              mesh->mNormals[i]);
    }

    Log(mesh->mNumVertices);

    auto parsed_mesh = new scene::Mesh(std::move(vertices),
                                       std::move(indices));

    cache[file] = parsed_mesh;

    return new scene::Model(parsed_mesh);
}

#endif
