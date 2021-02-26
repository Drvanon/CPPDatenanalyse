#include <iostream>
#include <math.h>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TVirtualFFT.h"
#include "TMath.h"
#include "TFitResultPtr.h"
#include <TMinuit.h>

using namespace std;

double polynomial(double* x, double* par, int pars) {
    double res = 0;
    for (int i=0;i<pars;i++) {
        double contrib = par[i] * pow(x[0], i);
        res += contrib;
    }
    return res;
}

void do_fit(int pars) {
    TCanvas *c1 = new TCanvas("canvas", "canvas", 1200,800);

    // data to be fit by a polynomialconst
    int nP =  10 ;
    // Number of data pointsdouble
    double xData[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};
    double yData[] = {1.1, 2.3, 2.7, 3.2, 3.1, 2.4, 1.7, 1.5, 1.5, 1.7};
    double dyData[] = {0.15, 0.22, 0.29, 0.39, 0.31, 0.21, 0.13, 0.15, 0.19, 0.13};
    double dxData[] = {0.1, 0.1, 0.5, 0.1, 0.5, 0.1, 0.5, 0.1, 0.5, 0.1};

    TH1D * h = new TH1D("histogram", "Histogram", nP, 1, 10);
    for (int i=0; i<nP; i++) {
        h->SetBinContent(i, yData[i]);
        h->SetBinError(i, dyData[i]);
    }


    TF1* fit_func = new TF1("pol-robin", [pars](double* x, double* par){return polynomial(x, par, pars);}, 1, 10, pars);
    TFitResultPtr fres = h->Fit(fit_func, "S");
    h->Draw();
    TH1D *h2 = new TH1D("hist 2", "hist", 100, 0, 10);
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(h2);
    h2->SetFillColor(7);
    h2->Draw("E3");
    h->Draw("Same");
}

void macro(){
    do_fit(5);
}
