/**
 * @file   main.cpp
 * @author Bruno Jobard
 * @author Author1
 * @author Author2
 * @date   Sep 2012
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
#include "objects/funcsurface.h"
#include "objects/off_loader.h"

/**
* Program usage
* Should be handled with the tclap library
*/
void usage(char* name){
  cout<< "usage: " << name << " [options]" <<endl;
  cout<< "options:" <<endl;
  cout<< "  -h, --help                 shows this message" <<endl;
  cout<< "  -o, --off file                 loads OFF file" <<endl;
}

float func_expcos(float x, float y) {
 return exp(-(x*x/2+y*y/2))*cos(2*x*x+2*y*y);
}

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    try{
        //Parsing cli
        TCLAP::CmdLine cmd("", ' ', "0.42");
        TCLAP::ValueArg<std::string> offFileArg("o","off",".off file path",false,"","string");
        cmd.add(offFileArg);
        cmd.parse(argc,argv);
        std::string offFile=offFileArg.getValue();

        // initialize my custom 3D scene
        float objectRadius = 1.;
        QPointer<MyScene> myScene = new MyScene(objectRadius);

        //add simple objects
        myScene->addObject(new Cube());
        myScene->addObject(new Pyramid());
        myScene->addObject(new CubeCorner());
        myScene->addObject(new Disk());
        myScene->addObject(new DiskHole());
        myScene->addObject(new Cylinder());
        myScene->addObject(new Cone());
        myScene->addObject(new FuncSurface(50,50,-3.14,3.14,-3.14,3.14,&func_expcos));
        if(offFile!="")
        {
            myScene->addObject(new OffLoader(offFile));
            myScene->slotSetCurrentObject(8);
        }


        // add surface functions
        // ...

        // add user defined OFF files
        // ...

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

