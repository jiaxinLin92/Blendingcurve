
#include "bezier.h"

//s=i
//e=i+2
//t=i+1
Bezier::Bezier(PCurve<float,3>* c, float s, float e, float t, int d) {

    _s=s;
    _e=e;
    GMlib::DVector<GMlib::Vector<float,3> > Curve = c->evaluateParent(t, d);

    _scalestep=(t-_s)/(_e-_s);//7.32
    _scaled = 1.0/(_e - _s);//8.11

   // BezierMatrix(Curve.getDim()-1,_scalestep,1/_scaled);
    //BMatrix=BezierMatrix(Curve.getDim()-1,_scalestep,_scaled).invert();

    //（C0，C1，C2，C3）=(C01，C12，C23)/BezierMatrix
    _cp=(BezierMatrix(d,_scalestep,_scaled).invert())*Curve;

    for(int i = 0; i < Curve.getDim(); i++)
    {
        _cp[i] -= Curve(0);

    }
    this->translateParent(Curve(0));
}


Bezier::~Bezier() {}


void Bezier::eval( float t, int d, bool /*l*/) {

    GMlib::DMatrix<double> bhp = BezierMatrix(_cp.getDim()-1,t,_scaled);

    this->_p = bhp *_cp;
}


float Bezier::getStartP() {

    //return _s;
    return 0.0;
}

float Bezier::getEndP() {

    //return _e;
    return 1.0;
}

bool Bezier::isClosed()  const{

    return true;
}


//matrix of basis functions
//Generalized Bernstein/Hermite matrix
GMlib::DMatrix<double> Bezier::BezierMatrix(int d, double t, double scale){

        if (d < 1)
        {
            BMatrix.setDim (1 , 1) ;
            BMatrix[0][0] = 1 ;
             // Initiate the result matrix
        }
        else
            //myMatrix.setDim(degree +1 ,degree+1);
            BMatrix.setDim(d+1,d+1);

        //equation 4.30 p88
    BMatrix[d-1][0] = 1 - t;
    BMatrix[d-1][1] =  t;

    for(int i = d - 2; i >= 0; i--){

        BMatrix[i][0] = (1-t)*BMatrix[i+1][0];

        for(int j = 1; j < d-i; j++){

            BMatrix[i][j] = t*BMatrix[i+1][j-1]+(1-t)*BMatrix[i+1][j];

        }

        BMatrix[i][d-i] = t*BMatrix[i+1][d-i-1];

    }


    BMatrix[d][0] = -scale;
    BMatrix[d][1] = scale;

    for(int k = 2; k <= d; k++){

        double s = k*scale;

        for(int i = d; i > d-k; i--){

            BMatrix[i][k] = s*BMatrix[i][k-1];

            for(int j = k-1; j > 0; j--){

                BMatrix[i][j] = s*(BMatrix[i][j-1] - BMatrix[i][j]);

            }

            BMatrix[i][0] = (-s)*BMatrix[i][0];

        }

    }

    return BMatrix;

}

void Bezier::localSimulate(double dt)
{
this->rotate(GMlib::Angle(M_2PI*dt),GMlib::Vector<float,3>(0.0f,0.0f,1.0f));
}



