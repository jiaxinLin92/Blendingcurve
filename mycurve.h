#ifndef MYCURVE_H
#define MYCURVE_H

#include <gmParametricsModule>



//  template <typename float>
  class Mycurve : public GMlib::PCurve<float,3> {
    GM_SCENEOBJECT(Mycurve)
  public:
    Mycurve();
    ~Mycurve();

    bool            isClosed() const;

  protected:

    void	          eval(float t, int d, bool l);
    float             getEndP();
    float             getStartP();
    //void              getP();
   // void localSimulate(double dt);
  };



#endif
