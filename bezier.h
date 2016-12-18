#ifndef __BEZIERR_H__
#define __BEZIERR_H__

#include <gmParametricsModule>

class Bezier : public GMlib::PCurve<float,3> {
GM_SCENEOBJECT(Bezier)
public:
  Bezier( PCurve<float,3>* c, float s, float e, float t, int d);

  ~Bezier();

    bool                        isClosed()  const;

protected:
    float                                       _scaled;//
    float                                       _scalestep;//
    GMlib::DVector<GMlib::Vector<float,3>>      _cp; //control point

    PCurve<float,3>*                            _c;

    float                   _s;
    float                   _e;


    void                  eval(float t, int d, bool l);
    float                 getEndP();
    float                 getStartP();

    GMlib::DMatrix<double> BezierMatrix(int d, double t, double scale);
    GMlib::DMatrix<double> BMatrix;

    void localSimulate(double dt);

}; // END class Bezier

#endif
