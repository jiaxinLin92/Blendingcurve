#include "erbs.h"
#include "subcurve.h"
#include "time.h"

Erbs::Erbs(PCurve<float,3> *c, int n)
{
    _c=c;
    _n=n;
    _s=_c->getParStart();
    _e=_c->getParEnd();
    _bezier=false;
    if(_c->isClosed() == true)
    {
        _n += 1;
    }
     VectorKnot(_s,_e,_n);
     subCurve();


}

Erbs::Erbs(PCurve<float,3> *c, int n, int d)
{
    _c=c;
    _d=d;
    _n=n;
    //_scale=1;
    _bezier=true;
    _s=_c->getParStart();
    _e=_c->getParEnd();
    VectorKnot(_s,_e,_n);
    bezier(_d);

}



float Erbs::getEndP()
{
    return _Vc[_Vc.getDim()-1];
}



float Erbs::getStartP()
{
    return _Vc[1];
}



GMlib::DVector<float> Erbs::getKnotVector()
{
    return _Vc;

}

void Erbs::subCurve()
{
    _localc.setDim( _n);
    int size=_Vc.getDim();
    std::cout<<_Vc.getDim();
    for(int i = 0; i < size-1; i++){
        _localc[i] = new Subcurve(_c, _Vc[i+1], _Vc[i+2]);
        std::cout<<" 1: "<<_Vc[i+1]<<" 2: "<< _Vc[i+2]<<" "<<i<<" "<<_n<<std::endl;
         _localc[i]->toggleDefaultVisualizer();
//        _localc[i]->translate(GMlib::Vector<float,3>(0,0,1));
        _localc[i]->setColor(GMlib::GMcolor::Yellow);
        _localc[i]->setVisible(false);
       //_localc[i]->translate(GMlib::Vector<float,3>(0,0,1));
        _localc[i]->replot(50,2);
         insert(_localc[i]);
    }
    if(_c->isClosed())
    {
         _localc[_n-1] = _localc[0];
         //_localc[_n-1]=_localc[0];
         //std::cout<<*_localc[0]<<"and "<<*_localc[1]<<std::endl;
         insert(_localc[0]);
         // insert(_localc[0]);
    }

}

void Erbs::bezier(int d)//
{
    _localc.setDim( _n);

    int size=_Vc.getDim();
    for(int i = 0; i < size-2; i++){
        _localc[i] = new Bezier(_c, _Vc[i], _Vc[i+2], _Vc[i+1], d);
        std::cout<<_Vc[i-1]<<" "<<_Vc[i+1]<<" "<< _Vc[i]<<" "<<d<<" "<<_n<<" "<< i<<std::endl;
        _localc[i]->toggleDefaultVisualizer();
        _localc[i]->replot(50,2);
        //_localc[i]->translate(GMlib::Vector<float,3>(0,0,1));
        //_localc[i]->setColor(GMlib::GMcolor::Yellow);
        _localc[i]->setVisible(false);

        insert(_localc[i]);
    }
   if(_c->isClosed())
   {
        _localc[_n-2] = _localc[0];
        //std::cout<<*_localc[0]<<"and "<<*_localc[1]<<std::endl;
        insert(_localc[0]);
   }


}

int Erbs::findIndex(float t)
{

    for (int i = 1; i < _Vc.getDim() - 2; i++){
          if (t>=_Vc[i] && t<_Vc[i+1])
              return i;
      }

      return  _Vc.getDim() - 2;
}

GMlib::DVector<float> Erbs::VectorKnot(float s, float e, int n)
{
    float iterable = s;
    float step = (s+e)/(n-1);

    if(_bezier){
        int i = 0;
        while (i<n)
        {
            _Vc.append(iterable);
            iterable = iterable + step;
                i++;
        }

        if (isClosed())
        {

               // _Vc.append(e+step);

        }

        return _Vc;
    }
    if (isClosed())
    {
        //if(iterable!=0){
            _Vc.append(iterable-step);
        //}
    }
    int i = 0;
    while (i<n)
    {
        _Vc.append(iterable);
        iterable = iterable + step;
            i++;
    }

    if (isClosed())
    {

           // _Vc.append(e+step);

    }

    return _Vc;


}

bool Erbs::isClosed()
{
     return _isClosed;
}

GMlib::DVector<float> Erbs::DeriB(float t, float d, float scale)
{
    GMlib::DVector<float> v;
       v.setDim(d+1);
       v[0] = 3*pow(t,2) - 2*pow(t,3);
       if (d>0)
           v[1] = (6*t - 6*pow(t,2))*scale;
       if (d>1)
           v[2] = (6 - 12*t)*scale;
       if (d>2)
           v[3] = -12*scale*scale;

       return v;
}


void Erbs::eval(float t, int d, bool l)
{
    //number of derivatives to compute
       this->_p.setDim(d+1);

       int index = findIndex(t);

       float w = (t -_Vc[index])/(_Vc[index+1] -_Vc[index]);

       _scale=1/(_Vc[index+1] -_Vc[index]);

       GMlib::DVector<float> BFunction = DeriB(w, d, _scale);

       if (_bezier){
           float tb1=(t - _Vc[index])/(_Vc[index+2] -_Vc[index]);
           float tb2=(t - _Vc[index+1])/(_Vc[index+3] -_Vc[index+1]);

           GMlib::DVector<GMlib::Vector<float,3>> c1 = _localc[index-1]->evaluateParent(tb1, d);
           GMlib::DVector<GMlib::Vector<float,3>> c2 = _localc[index]->evaluateParent(tb2, d);

           this->_p[0] = c1[0]+ BFunction[0]*(c2[0] - c1[0]);
           if( d > 0)
               this->_p[1] = c1[1]+ BFunction[0]*( c2[1] - c1[1])+ BFunction[1]*( c2[0] -  c1[0]) ;
           if( d > 1)
               this->_p[2] = c1[2]+ BFunction[0]*( c2[2] -  c1[2])+ 2*BFunction[1]*( c2[1] -  c1[1])+ BFunction[2]*(c2[0] -  c1[0]) ;

       }
       else{

        GMlib::DVector<GMlib::Vector<float,3>> c1 = _localc[index-1]->evaluateParent(t, d);
        GMlib::DVector<GMlib::Vector<float,3>> c2 = _localc[index]->evaluateParent(t, d);

//        _scale=1/(_Vc[index+1] -_Vc[index]);
//        float w2=((t - _Vc[index])/(_Vc[index+1]-_Vc[index]));
//
//        GMlib::DVector<float> BFunction = DeriB(w2,d,_scale);
        this->_p[0] = c1[0]+ BFunction[0]*(c2[0] - c1[0]);
        if( d > 0)
            this->_p[1] = c1[1]+ BFunction[0]*( c2[1] - c1[1])+ BFunction[1]*( c2[0] -  c1[0]) ;
        if( d > 1)
            this->_p[2] = c1[2]+ BFunction[0]*( c2[2] -  c1[2])+ 2*BFunction[1]*( c2[1] -  c1[1])+ BFunction[2]*(c2[0] -  c1[0]) ;


       }

       }
void Erbs::localSimulate(double dt)
{

    // int rate=1;
     std::vector<GMlib::Color> Vector={GMlib::GMcolor::Blue,GMlib::GMcolor::Brown,GMlib::GMcolor::Gold,GMlib::GMcolor::Pink,GMlib::GMcolor::Green};

     double time;
     time=_time.getSec();
    // int etime=120;
     int stime=11;
     int elapsed=1;

     //std::cout<<dt<<" "<<time<<std::endl;
    // _localc[3]->translate(GMlib::Vector<float,3>(0,0,0.01));
    //  _localc[3]->setColor(Vector[2]);
 //_localc[4]->translate(GMlib::Vector<float,3>(0,0,0.01));
 // _localc[4]->setColor(Vector[0]);
// _localc[5]->translate(GMlib::Vector<float,3>(0,0,0.01));
//  _localc[5]->setColor(Vector[1]);

     int size=_Vc.getDim();
     for(int i = 0; i < size-2; i++)
     {
         if(time>2&&time<4)
         {
         _localc[i]->translate(GMlib::Vector<float,3>(0,0,0.06));
         }

         if(time>4&& time<6)
         {
             _localc[i]->translate(GMlib::Vector<float,3>(0,0,-0.06));

            //_localc[i]->setColor(Vector[i]);
         }

         if(time>6&&time<8)
         {
         _localc[i]->translate(GMlib::Vector<float,3>(0,0,0.06));
         }

         if(time>8&& time<10)
         {
             _localc[i]->translate(GMlib::Vector<float,3>(0,0,-0.06));

             _localc[i]->setColor(Vector[i]);
         }


       if(time>stime&&time<stime+elapsed)
       {
       _localc[i]->translate(GMlib::Vector<float,3>(0,0,0.03));
       }
       stime=stime+elapsed;
       if(time>stime&& time<stime+elapsed)
       {
           _localc[i]->translate(GMlib::Vector<float,3>(0,0,-0.03));
       }

    }


}
