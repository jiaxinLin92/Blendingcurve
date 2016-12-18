
/*! \file gmpsubcurve.h
 *
 *  Interface for the PSurfCurve class.
 */

#ifndef __SUBCURVE_H__
#define __SUBCURVE_H__

#include "mycurve.h"

  class Subcurve : public GMlib::PCurve<float,3> {
    GM_SCENEOBJECT(Subcurve)
  public:
    Subcurve( PCurve<float,3>* c, float s, float e);
    //Subcurve( PCurve<float,3>* c, float s, float e, float t);
    virtual ~Subcurve();

    // virtual functions from PSurf
    virtual bool            isClosed() const;
    // Local functions
    void                    togglePlot();

  protected:

    PCurve<float,3>*        _c;
    float                   _s;
    float                   _t;
    float                   _e;
    GMlib::Vector<float,3>         _trans;

    // virtual functions from PSurf
    void                    eval( float t, int d, bool l = false );
    float                   getEndP();
    float                   getStartP();
    float                   getT();
    void localSimulate(double dt) override;

  private:

    // Local help functions
    void set(PCurve<float,3>* c, float s, float e, float t);

  }; // END class Subcurve






#endif // __SUBCURVE_H__

