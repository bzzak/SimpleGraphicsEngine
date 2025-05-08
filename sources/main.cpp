#include <iostream>
#include "../headers/Buffer.h"
#include "../headers/TgaBuffer.h"
#include "../headers/Rasterizer.h"
#include "../headers/SimpleRasterizer.h"
#include "../headers/Math.h"
#include "../headers/VertexProcessor.h"
#include "../headers/SimpleTriangle.h"
#include "../headers/Cube.h"
#include "../headers/Cone.h"
#include "../headers/Cylinder.h"
#include "../headers/Sphere.h"
#include "../headers/Torus.h"
#include "../headers/DirectionalLight.h"
#include "../headers/PointLight.h"


int main() {

    auto simpleRasterizer = SimpleRasterizer(1500,1500);

    simpleRasterizer.setEye({0.0f, 0.0f, 3.0f});
    simpleRasterizer.setCenter({0.0f, 0.0f, -1.0f});
    simpleRasterizer.setUp({0.0f, 1.0f, 0.0f});

    simpleRasterizer.setFovy(65.0f);
    //simpleRasterizer.setAspect(16.0f/9.0f);
    simpleRasterizer.setAspect(1.0f);
    //simpleRasterizer.setAspect(4.0f/3.0f);
    simpleRasterizer.setPlanes(0.1f, 100.0f);


    std::vector<Light*> lights;

    auto* directionalLight1 = new DirectionalLight({0.0f, -1.0f, -2.0f});
    directionalLight1->setAmbientColor({0.05f, 0.05f, 0.05f});
    directionalLight1->setDiffuseColor({0.7f, 0.7f, 0.7f});
    directionalLight1->setSpecularColor({0.2f, 0.2f, 0.2f});

    lights.push_back(directionalLight1);

    auto* pointLight1 = new PointLight({-1.5f, 0.0f, 0.0f});
    pointLight1->setAmbientColor({0.05f, 0.05f, 0.05f});
    pointLight1->setDiffuseColor({1.0f, 0.0f, 0.0f});
    pointLight1->setSpecularColor({0.0f, 1.0f, 0.0f});

    lights.push_back(pointLight1);





    //Mesh* mesh = new SimpleTriangle();

    //mesh->scale(simpleRasterizer,{0.5f, 0.5f, 1.0f});
    //mesh->rotate(simpleRasterizer, 90.0f, {0.0f, 0.0f, 1.0f});
    //mesh->translate(simpleRasterizer, {0.5f, 0.5f, 0.0f});

    //Mesh* cube = new Cube();

    //cube->rotate(simpleRasterizer, 45.0f, {0.0f, 1.0f, 0.0f});
    //cube->rotate(simpleRasterizer, 45.0f, {1.0f, 0.0f, 0.0f});

    Mesh* cone = new Cone(50);
    cone->makeNormals();

    cone->setDiffuseColor({0.0f, 0.0f, 1.0f});
    cone->setSpecularColor({0.25f, 0.25f, 0.25f});
    cone->setShininess(16.0f);

    cone->scale(simpleRasterizer,{1.0f, 1.0f, 1.0f});
    cone->uniformScale(simpleRasterizer,0.75f);
    cone->rotate(simpleRasterizer, -30.0f, {1.0f, 0.0f, 0.0f});
    cone->translate(simpleRasterizer, {0.6f, 2.5f, -0.5f});

   // Mesh* cylinder = new Cylinder(30,6);
    //cylinder->makeNormals();

    //cylinder->scale(simpleRasterizer,{2.0f, 2.0f, 1.0f});
    //cylinder->rotate(simpleRasterizer, 0.0f, {1.0f, 0.0f, 0.0f});

    Mesh* sphere = new Sphere(30, 30);
    sphere->makeNormals();

    sphere->setDiffuseColor({0.0f, 1.0f, 1.0f});
    sphere->setSpecularColor({0.6f, 0.6f, 0.6f});
    sphere->setShininess(64.0f);

    sphere->scale(simpleRasterizer,{1.0f, 1.0f, 1.0f});
    sphere->uniformScale(simpleRasterizer,0.75f);
    sphere->rotate(simpleRasterizer, 45.0f, {1.0f, 0.0f, 0.0f});
    sphere->translate(simpleRasterizer, {1.5f, 0.0f, 0.0f});

    simpleRasterizer.resetTransformations();

    Mesh* sphere2 = new Sphere(30, 30);
    sphere2->makeNormals();

    sphere2->setDiffuseColor({0.0f, 1.0f, 1.0f});
    sphere2->setSpecularColor({0.6f, 0.6f, 0.6f});
    sphere2->setShininess(64.0f);

    sphere2->scale(simpleRasterizer,{1.0f, 1.0f, 1.0f});
    sphere2->uniformScale(simpleRasterizer,0.75f);
    sphere2->rotate(simpleRasterizer, 45.0f, {1.0f, 0.0f, 0.0f});
    sphere2->translate(simpleRasterizer, {1.5f, 0.5f, -1.0f});

    simpleRasterizer.resetTransformations();

    Mesh* torus = new Torus(30, 30);
    torus->makeNormals();

    torus->setDiffuseColor({1.0f, 1.0f, 0.0f});
    torus->setSpecularColor({1.0f, 1.0f, 1.0f});
    torus->setShininess(128.0f);

    torus->scale(simpleRasterizer,{1.0f, 1.0f, 1.0f});
    torus->uniformScale(simpleRasterizer,1.2f);
    torus->rotate(simpleRasterizer, 45.0f, {1.0f, 0.0f, 0.0f});
    torus->translate(simpleRasterizer, {-0.7f, 0.0f, 0.0f});

    simpleRasterizer.setBackground(0,0,0);

    //mesh->draw(simpleRasterizer, {255, 0, 0});
    //cube->draw(simpleRasterizer, {255, 255, 0}, {0, 255, 255}, {255, 0, 255});
    cone->setTransformations(simpleRasterizer);
    //cone->draw(simpleRasterizer, {255, 255, 0}, {0, 255, 255}, {255, 0, 255});
    cone->drawPhongPixel(simpleRasterizer, lights);
    //cylinder->draw(simpleRasterizer, {255, 255, 0}, {0, 255, 255}, {255, 0, 255});
    sphere->setTransformations(simpleRasterizer);
    //sphere->draw(simpleRasterizer, {255, 255, 0}, {0, 255, 255}, {255, 0, 255});
    sphere->drawPhongPixel(simpleRasterizer, lights);
    sphere2->setTransformations(simpleRasterizer);
    //sphere2->draw(simpleRasterizer, {255, 255, 0}, {0, 255, 255}, {255, 0, 255});
    sphere2->drawPhong(simpleRasterizer, lights);
    torus->setTransformations(simpleRasterizer);
    //torus->draw(simpleRasterizer, {255, 255, 0}, {0, 255, 255}, {255, 0, 255});
    torus->drawPhongPixel(simpleRasterizer, lights);




    simpleRasterizer.save();

    //delete mesh;
    //delete cube;
    delete cone;
    //delete cylinder;
    delete sphere;
    delete sphere2;
    delete torus;

    for (auto light : lights) {
        delete light;
    }


    return 0;
}



