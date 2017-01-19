#include <gtest/gtest.h>

#include "includes.h"

#include "ModelMesh.hpp"

using namespace std;

TEST(ModelMeshCnstructor, ModelMesh)
{
    
    /* OLD DECLARATION
     
     OriginVertex ov;
     ov.position = vec3(0.1f);
     ov.normal = vec3(0.2f);
     ov.texCoords = vec3(0.3f);
     
     GLuint id1 = 1;
     
     OriginTexture ot;
     ot.id = 1;
     ot.type = "first";
     
     vector<OriginVertex> vertices;
     vector<GLuint> indices;
     vector<OriginTexture> textures;
     
     vertices.push_back(ov);
     indices.push_back(id1);
     textures.push_back(ot);
     
     ModelMesh mm(vertices, indices, textures);
    */

    ModelMesh modelMesh(
        {
            {vec3(0.1f), vec3(0.2f), vec3(0.3f)},
            {vec3(0.4f), vec3(0.5f), vec3(0.6f)}
        },
        {
            1, 2, 3, 4
        },
        {
            {1, "first"},
            {2, "second"}
        }
    );
    
    EXPECT_FLOAT_EQ(0.1f, modelMesh.vertices[0].position.x);
    EXPECT_EQ(1, modelMesh.indices[0]);
    EXPECT_EQ("first", modelMesh.textures[0].type);
}
