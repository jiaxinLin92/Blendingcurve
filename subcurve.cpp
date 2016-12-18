
#include "subcurve.h"

  Subcurve::Subcurve(PCurve<float,3>* c, float s, float e )
  {
    this->_dm = GMlib::GM_DERIVATION_EXPLICIT;

    set(c, s, e, (e+s)/2);

    _c=c;
    _s=s;
    _e=e;
    GMlib::DVector<GMlib::Vector<float,3> > tr = _c->evaluateParent(_t, 0);
    _trans = tr[0];
    this->translateParent( _trans );
  }

//  Subcurve::Subcurve( PCurve<float,3>* c, float s, float e, float t )
//  {
//    this->_dm = GMlib::GM_DERIVATION_EXPLICIT;

//    set(c, s, e, t);
//      _c=c;
//      _s=s;
//      _e=e;
//      _t=t;

//    GMlib::DVector<GMlib::Vector<float,3> > tr = _c->evaluateParent(_t, 0);
//    _trans = tr[0];
//    this->translateParent( _trans );
//  }


  Subcurve::~Subcurve() {}


  void Subcurve::eval( float t, int d, bool /*l*/ )
  {
    this->_p     = _c->evaluateParent(t , d);
    this->_p[0] -= _trans;
  }


  float Subcurve::getStartP()
  {
    return _s;
  }


  float Subcurve::getEndP()
  {
    return _e;
  }

  float Subcurve::getT()
  {
      return _t;
  }


  bool Subcurve::isClosed() const
  {
    return true;
  }

  void Subcurve::set(PCurve<float,3>* c, float s, float e, float t)
  {
    _c = c;
    _s = s;
    _t = t;
    _e = e;
  }

  void Subcurve::localSimulate(double dt)
  {
this->rotate(GMlib::Angle(M_2PI*dt),GMlib::Vector<float,3>(0.0f,0.0f,1.0f));

  }

