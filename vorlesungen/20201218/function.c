#include <TMath.h>
#include <TF1.h>

void function( ) {
    TF1 *f1 = new TF1("total sigma", sigma_total, 0, 150);
}

double sigma_total (double* x, double* p) {
    return TMath::sqrt( 1/x[0] * p[0]);
}
