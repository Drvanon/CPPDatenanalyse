//
//  RooFit Example:
//  Generate a D0 Mass Distribution according to LHCb measured values
//  and Fit the generated Values with a Maximum Likelihood or an
//  extended Maximum Likelihood fit.
//  As Model a simple Gaussian Distribution is used
//
//
//
#include <RooRealVar.h>
#include <RooGaussian.h>
#include <RooExtendPdf.h>
#include <RooDataSet.h>
#include <RooExponential.h>
#include <RooPlot.h>
#include <TMath.h>
#include <RooFitResult.h>
using namespace RooFit ;

void rooSimple() {
    // Number of generated Events
    Int_t nGen = 10000 ;
    //define variables
    RooRealVar t("t","D^0 t",0.1,10);
    RooRealVar signalMeanMass ("signalMeanMass ","mean of D^0 mass",1864.4,1839.5,1889.5);
    RooRealVar tau ("tau","tau in ps", -0.1, -0.4101, -10 );
    // Define the Gaussian PDF
    RooExponential signalTime ("signalTime","signal distribution time", t, tau);
    // Generate the nGen events  and Store the values in a RooFit Dataset
    RooDataSet *data = signalTime.generate(t,nGen);
    // Define an extended PDF to allow for fitting the absolute Number of events
    RooRealVar nSignal("nSignal","number of signal events",2000,0,1000000);
    RooExtendPdf eSignal("eSignal","extended signal D^0",signalTime,nSignal);
    // Fit either the gaussian distribution or the extended PDF
    //signalMass.fitTo(*data) ;
    RooFitResult* result = eSignal.fitTo(*data,Extended(kTRUE),NumCPU(2),Timer(kTRUE), Save()) ;
    // Plot the Data, Fit result, Residuals and Pull Distribution
    TCanvas* myC = new TCanvas("myC","RooFit Results",1000, 1500);
    myC->Divide(1,4);
    myC->cd(1);
    RooPlot *xframe0 = t.frame() ;
    data->plotOn(xframe0);
    signalTime.plotOn(xframe0) ;
    xframe0->Draw();
    myC->cd(2);
    RooHist* massResid    = xframe0->residHist();
    RooPlot* xframe1      = t.frame(Title("Residual Distribution")) ;
    xframe1->addPlotable(massResid,"P") ;
    xframe1->Draw();
    myC->cd(3);
    RooHist* massPull     = xframe0->pullHist();
    RooPlot* xframe2      = t.frame(Title("Pull Distribution")) ;
    xframe2->addPlotable(massPull,"P") ;
    xframe2->Draw();
    std::cout << "-------------------------------"<<endl;
    result->Print();
    myC->cd(4);
    RooAbsReal* nll = signalTime.createNLL(*data);
    RooAbsReal* pll_p = nll->createProfile(tau);
    RooPlot *LikeFrame0 = tau.frame(Bins(10),Range(-1,0),
         Title("LL and profileLL in Parameter"));
    nll->plotOn(LikeFrame0, ShiftToZero());
    //LikeFrame0->SetMinimum(0); LikeFrame0->SetMaximum(1) ;
    //pll_p->plotOn(LikeFrame0,LineColor(kRed)) ;
    LikeFrame0->Draw();
    // Calculate the fraction of events in the named range
    //RooAbsReal* signalIntegral = eSignal.createIntegral(mass,NormSet(mass),Range("center"));
    //cout << "Signal in range center:" << signalIntegral->getVal()<< endl;
}
