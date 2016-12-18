#include "scenario.h"

#include "testtorus.h"
#include "mycurve.h"
#include "subcurve.h"
#include "knotvector.h"
#include "bezier.h"
#include "erbs.h"
//// hidmanager
//#include "hidmanager/defaulthidmanager.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QQuickItem>
#include <QDebug>



void Scenario::initializeScenario() {

  // Insert a light
  GMlib::Point<GLfloat,3> init_light_pos( 2.0, 4.0, 10 );
  GMlib::PointLight *light = new GMlib::PointLight(  GMlib::GMcolor::White, GMlib::GMcolor::White,
                                                     GMlib::GMcolor::White, init_light_pos );
  light->setAttenuation(0.8, 0.002, 0.0008);
  scene()->insertLight( light, false );

  // Insert Sun
  scene()->insertSun();

  // Default camera parameters
  int init_viewport_size = 600;
  GMlib::Point<float,3> init_cam_pos(  0.0f, 0.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_dir( 0.0f, 1.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_up(  0.0f, 0.0f, 1.0f );

  // Projection cam
  auto proj_rcpair = createRCPair("Projection");
  proj_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
  proj_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  proj_rcpair.camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
  proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -50.0f, 43.0f ) );
  scene()->insertCamera( proj_rcpair.camera.get() );
  proj_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Front cam
  auto front_rcpair = createRCPair("Front");
  front_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, -50.0f, 0.0f ), init_cam_dir, init_cam_up );
  front_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( front_rcpair.camera.get() );
  front_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Side cam
  auto side_rcpair = createRCPair("Side");
  side_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( -50.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ), init_cam_up );
  side_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( side_rcpair.camera.get() );
  side_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Top cam
  auto top_rcpair = createRCPair("Top");
  top_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, 0.0f, 50.0f ), -init_cam_up, init_cam_dir );
  top_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( top_rcpair.camera.get() );
  top_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

//auto knot = new KnotVector(0,M_2PI,6);
//GMlib::DVector<float> vectknots = knot->getKnotVector();
//int sizeVec = vectknots.getDim();

//for (int j = 0; j < sizeVec; j++)
//{
//    qDebug() << vectknots[j];
//}


 // int heartSpeed=15;
  //int radiusRate=3
// float t;
// float r1 = 16*sin(t)*sin(t)*sin(t);
// float r2 = 13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t);

 //float x=(r1*cos(t)*(0.5+0.5*sin( t/heartSpeed*M_PI)));
// float yy=(r2*sin(t)*(0.5+0.5*sin( t/heartSpeed*M_PI)));


//  if (i < heartSpeed / 2)
//      ratio=sin( i/heartSpeed*M_PI);
//  if((i >= heartSpeed / 2) && (i < heartSpeed * 3/4))
//      ratio=2*cos(i/heartSpeed*2/3*M_PI);
//  else
//      ratio = 0;

//curve

//  auto curve= new Mycurve();
//  curve->toggleDefaultVisualizer();
//  curve->setColor(GMlib::GMcolor::Red);
//  curve->replot(100,2);
//  scene()->insert(curve->get);
_mycurve=new Mycurve();
_mycurve->toggleDefaultVisualizer();
_mycurve->setColor(GMlib::GMcolor::Black);
_mycurve->replot(100,2);
scene()->insert(_mycurve);

//subcurve

  //std::vector<GMlib::Color> Vector={GMlib::GMcolor::Blue,GMlib::GMcolor::Brown,GMlib::GMcolor::Gold,GMlib::GMcolor::White,GMlib::GMcolor::Green};
//for(int i=0;i<5;i++)
// {
////M_2PI means whole picture
//// auto subcurve =new Subcurve(curve,i*(M_2PI/6),(i+1)*(M_2PI/6));
// auto subcurve =new Subcurve(curve,vectknots[i],vectknots[i+1]);
// subcurve->toggleDefaultVisualizer();
// subcurve->setColor(Vector[i]);
// subcurve->translate(GMlib::Vector<float,3>(0,0,1));
// subcurve->replot(100,2);
// scene()->insert(subcurve);
// }

  //auto knot = new KnotVector(0,M_2PI,30);

 // auto knot= new Erbs(curve,30);
 // GMlib::DVector<float> vectknots = knot->getKnotVector();
 // int sizeVec = vectknots.getDim();

//  qDebug()<<sizeVec;
//  for (int j = 0; j < sizeVec; j++)
//  {
//      qDebug() << vectknots[j];
//  }


// erbs from subcurve
_erbsub=new Erbs(_mycurve,150);
_erbsub->toggleDefaultVisualizer();
//_erbsub->setVisible(false);
_erbsub->translate(GMlib::Vector<float,3>(0,0,4));

_erbsub->setColor(GMlib::GMcolor::Aqua);
_erbsub->replot(1000,2);
scene()->insert(_erbsub);

//auto erbs= new Erbs(_mycurve,200);
//erbs->toggleDefaultVisualizer();
////erbs->setVisible(false);
////erbs->setColor(GMlib::GMcolor::DarkGrey);
//erbs->translate(GMlib::Vector<float,3>(0,0,1));
//erbs->replot(100,1);
//scene()->insert(erbs);

//erbs from bezier
_erbs= new Erbs(_mycurve,150,2);
_erbs->toggleDefaultVisualizer();
//_erbs->setVisible(false);
_erbs->translate(GMlib::Vector<float,3>(0,0,2));

_erbs->setColor(GMlib::GMcolor::Aqua);
_erbs->replot(1000,2);
scene()->insert(_erbs);

//bezier curve
 // std::vector<GMlib::Color> Vector={GMlib::GMcolor::Blue,GMlib::GMcolor::Brown,GMlib::GMcolor::Gold,GMlib::GMcolor::Pink,GMlib::GMcolor::Green};
//  for (int j = 0; j < sizeVec-2; j++)//30

//  {
////      qDebug() << vectknots[j];
//      auto bezier=new Bezier(curve,vectknots[j],vectknots[j+2],vectknots[j+1],2);

//      bezier->toggleDefaultVisualizer();
//      bezier->replot(50,1);
//      bezier->setColor(GMlib::GMcolor::Green);
//      //bezier->setColor(Vector[j]);
//      bezier->translate(GMlib::Vector<float,3>(0,0,0));
//      scene()->insert(bezier);

 //}




}


void Scenario::reploterbs()
{
    _erbs->replot();
    _erbsub->replot();
}



void Scenario::cleanupScenario() {

}


