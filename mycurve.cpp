
#include "mycurve.h"
#include "C:\quadcopter\gmlib\modules\parametrics\src\gmpcurve.h"
#include <math.h>

  Mycurve::Mycurve( ) {
  }

  Mycurve::~Mycurve() {}


  void Mycurve::eval( float t, int d, bool /*l*/ ) {


      this->_p.setDim( d + 1 );

         //
         this->_p[0][0] = 16*sin(t)*sin(t)*sin(t);
         this->_p[0][1] = 13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t);
         this->_p[0][2] = 0;


         if( this->_dm == GMlib::GM_DERIVATION_EXPLICIT ) {
             //first

             if( d > 0 ) {
                 this->_p[1][0] = 48*pow(sin(t),2)*cos(t);
                 this->_p[1][1] = -13*sin(t) + 10*sin(2*t) + 6*sin(3*t) + 4*sin(4*t);
                 this->_p[1][2] = 0;
             }

             //second
             if( d > 1 ) {

                 this->_p[2][0] = -12*(sin(t))-3*sin(3*t);
                 this->_p[2][1] = -13*cos(t) + 20*cos(2*t) + 18*cos(3*t) + 16*cos(4*t);
                 this->_p[2][2] = 0;
             }
             //third
             if( d > 2 ) {

                 this->_p[2][0] = -12*(cos(t))-9*cos(3*t);
                 this->_p[2][1] = 13*sin(t)-40*sin(2*t)-54*sin(3*t)-64*sin(4*t);
                 this->_p[2][2] = 0;
             }
             //fourth
             if( d > 3 ) {

                 this->_p[2][0] = 12*(sin(t))-27*sin(3*t);
                 this->_p[2][1] = 13*cos(t)- 80*cos(2*t) - 162*cos(3*t) -256*cos(4*t);
                 this->_p[2][2] = 0;
             }
         }
  }



  float Mycurve::getEndP() {

    return float( M_2PI );
  }


  float Mycurve::getStartP() {

      return float(0);
  }


  



  bool Mycurve::isClosed() const {

    return true;
  }

