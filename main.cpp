/**
 * @file   main.cpp
 * @author Bruno Jobard
 * @author Félix Baylac
 * @author Pierre Caretero
 * @date   Oct 2013
 *
 * @brief  Declares an application, a main window and a 3D scene
 *
 *
 */
#include <QApplication>
#include <tclap/CmdLine.h>
#include <string>
#include "my_main_window.h"


#include "my_object3d.h"
#include "objects/cube.h"
#include "objects/pyramid.h"
#include "objects/cubecorner.h"
#include "objects/disk.h"
#include "objects/diskhole.h"
#include "objects/cylinder.h"
#include "objects/cone.h"
#include "objects/sphere.h"
#include "objects/torus.h"
#include "objects/funcsurface.h"
#include "objects/off_loader.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    try{
        //Parsing cli
        TCLAP::CmdLine cmd("", ' ', "0.42");
        TCLAP::ValueArg<std::string> offFileArg("o","off","Draw an object contained in a off file.",false,"","Path to off file");
        TCLAP::SwitchArg meshSwitch("m","mesh","Draw procedurally generated meshs.", cmd, false);
        TCLAP::SwitchArg funcSwitch("f","funcSurface","Draw function surfaces.", cmd, false);
        cmd.add(offFileArg);
        cmd.parse(argc,argv);
        std::string offFile=offFileArg.getValue();
        bool drawMesh = meshSwitch.getValue();
        bool drawFunc = funcSwitch.getValue();

        // initialize my custom 3D scene
        float objectRadius = 1.;
        QPointer<MyScene> myScene = new MyScene(objectRadius);

        if(drawMesh || (!drawFunc && offFile==""))
        {
            //add simple objects
            myScene->addObject(new Cube());
            myScene->addObject(new Pyramid());
            myScene->addObject(new CubeCorner());
            myScene->addObject(new Disk());
            myScene->addObject(new DiskHole());
            myScene->addObject(new Cylinder());
            myScene->addObject(new Cone());
            myScene->addObject(new Sphere());
            myScene->addObject(new Torus());
        }
        if(drawFunc)
        {
            // add surface functions
            myScene->addObject(new FuncSurface(50,50,-3.14,3.14,-3.14,3.14,&FuncSurface::func_expcos));
            myScene->addObject(new FuncSurface(50,50,-3.14,3.14,-3.14,3.14,&FuncSurface::func_sqrt));
            myScene->addObject(new FuncSurface(50,50,-3.14,3.14,-3.14,3.14,&FuncSurface::func_cosi));
        }
        if(offFile!="")
        {
            // add user defined OFF files
            myScene->addObject(new OffLoader(offFile));
        }







        // initialize my custom main window
        QPointer<MyMainWindow> myMainWindow = new MyMainWindow(myScene);
        // display the window
        myMainWindow->show();
        // enter in the main loop
        return app.exec();
    }
    catch (TCLAP::ArgException &e)  // catch any exceptions
    { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
}

