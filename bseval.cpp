//#include "bseval.h"

//GMlib::DMatrix<double> Bseval::evalBSp(float index, int d, float t, KnotVector knot)
//{


//    index=d;
//    knot_=knot;

////        if (t>knot_->get(index+1))//
////        {
////            index++;
////             // Initiate the result matrix
////        }

//            //myMatrix.setDim(degree +1 ,degree+1);
//        BMatrix.setDim(d+1,d+1);

//    GMlib::DVector<float> w(d);


//    BMatrix[d-1][0] = 1 - getW(t,1,index);
//    BMatrix[d-1][1] =  getW(t,1,index);

//    for(int i = d - 2,dc=2; i >= 0; i--,dc++){

//        w.setDim((dc));
//        for(int z=dc;z>0;z--)
//        {
//            w[z-1]=getW(t,dc,index-(dc-z));
//        }

//        BMatrix[i][0] = (1-w[0])*BMatrix[i+1][0];

//        for(int j = 1; j < d-i; j++){

//            BMatrix[i][j] = w[j-1]*BMatrix[i+1][j-1]+(1-w[j])*BMatrix[i+1][j];

//        }

//        BMatrix[i][d-i] = w[dc-1]*BMatrix[i+1][d-i-1];

//    }

//    BMatrix[d][0] = -getDW(1,index);//
//    BMatrix[d][1] = getDW(1,index);//

//    for(int k = 2; k <= d; k++){

//       // double s = k*scale;

//        for(int i = d, dc=2; i > d-k; i--,dc++){
//            w.setDim(dc);
//           // BMatrix[i][k] = s*BMatrix[i][k-1];
//            for(int s=1;s<dc;s++){
//                w[s-1]=s*getDW(dc,index-(dc-s));//
//            }

//            BMatrix[i][k]=w[0]*BMatrix[i][k-1];
//            for(int j = k-1, indexc=1; j > 0; j--,indexc ++){//

//                BMatrix[i][j] = w[indexc]*(BMatrix[i][j-1] - BMatrix[i][j]);

//            }

//            BMatrix[i][0] = -w[dc-1]*BMatrix[i][0];

//        }

//    }

//    return BMatrix;

//}

//float Bseval::getW(float t, float d, float index)
//{
//    if( t > knot_[index] && t <= knot_[index + d])

//      //(t-t[i])/(t[i+d]-t[i]);       //(equation 5.43)
//      return ( (t - knot_[index])/(knot_[index + d]- knot_[index]));
//    else
//      return 0.0;
//}

//float Bseval::getDW(float t,float d, float index)
//{
//    //1/(t[i+d]-t[i]); (equation 5.47)
//    if( t >= knot_[index] && t < knot_[index + deg])
//       return T(1)/(knot_[index+deg]-knot_[index]);
//    else
//       return 0.0;
//}
//}
