#ifndef ERBS_H
#define ERBS_H

#include <gmParametricsModule>

#include <memory>
#include <core/containers/gmdvector.h>
#include "mycurve.h"
#include "subcurve.h"
#include "knotvector.h"
#include "bezier.h"
#include <core/utils/gmtimer.h>
class Erbs : public GMlib::PCurve<float,3>{
 GM_SCENEOBJECT(Erbs)

public:
    Erbs(PCurve<float,3>* c, int n);
    Erbs(PCurve<float,3>* c, int n,int d );

    GMlib::DVector<float> getKnotVector();


protected:

    void                  eval(float t, int d, bool l);
    float                 getEndP();
    float                 getStartP();
   // void    getP();

    void localSimulate(double dt);

private:

    void subCurve();
    void bezier(int d);

    int                      findIndex( float t);
    GMlib::DVector<float>    VectorKnot(float s,float e, int n);
    GMlib::DVector<float>    _Vc;

    float                    _s;
    float                    _e;
    int                      _n;
    float                    _scale;

    int                      _d;
    GMlib::PCurve<float,3>*  _c;

    GMlib::DVector<PCurve*>                     _localc;
    bool                                        _bezier;

    bool                                        isClosed();
    bool                                        _isClosed=true;
    GMlib::DVector<float>     DeriB(float t, float d, float scale);
    GMlib::GMTimer            _time;

};


#endif
