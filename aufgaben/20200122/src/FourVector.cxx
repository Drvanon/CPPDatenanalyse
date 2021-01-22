#include "FourVector.h"
#include <iostream>
#include <cmath>

using namespace std;

ClassImp(FourVector);
FourVector::~FourVector() {
    cout << "FourVector destructor called" << endl;
}
FourVector::FourVector(){
    E=0.;Px=0.;Py=0.;Pz=0.;
    cout << "FourVector constructor I called" << endl;
}
FourVector::FourVector(double e ){
    E=e; Px=0.;Py=0.;Pz=0.;
    cout << "FourVector constructor II called" << endl;
}
FourVector::FourVector(double x, double y, double z){
    cout << "FourVector constructor III called" << endl;
    E=0.; Px=x;Py=y;Pz=z;
}
FourVector::FourVector(double e,double x,double y, double z):
    E(e),Px(x),Py(y),Pz(z)
{
    cout << "FourVector constructor IV called" << endl;
}

void FourVector::setE  (double e) {
    E = e ;
}
void FourVector::setP (double x, double y, double z) {
    Px = x ;
    Py = y ;
    Pz = z;
}
double FourVector::getEnergy(void) const {
    return E ;
}
double FourVector::getMomentum (void) const {
    return sqrt (Px*Px + Py*Py + Pz*Pz);
}
