#ifndef SCENARIO_H
#define SCENARIO_H


#include "application/gmlibwrapper.h"

// qt
#include <QObject>

class Mycurve;
class Subcurve;
class Bezier;
class Erbs;

class Scenario : public GMlibWrapper {
  Q_OBJECT
public:
  using GMlibWrapper::GMlibWrapper;

  void    initializeScenario() override;
  void    cleanupScenario() override;
  void    reploterbs();


  Mycurve* _mycurve;
  Erbs* _erbs;
  Erbs* _erbsub;

};

#endif // SCENARIO_H
