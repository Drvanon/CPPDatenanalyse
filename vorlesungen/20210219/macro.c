#include "RooStudyManager.h"

using namespace RooFit;

void macro () {
    //define variable to be read from the ntuple
    RooRealVar signal_1("signal_1", "Signal", 0, 5);
    // Import unbinned data from Tree
    // exponential background + gaussian signal
    TFile* tf = new TFile("FitTestTTree.root", "OPEN");
    TTree* myTree = (TTree*) gDirectory->Get("FitTest");
    RooDataSet data("data", "data", signal_1, RooFit::Import(*myTree));

    //create workspace
    RooWorkspace* workspace = new RooWorkspace("w", "Gaussian on exponential background");
    workspace->import(data);

    // define PDFs
    workspace->factory("Gaussian::g(signal_1,s_mean[1,3],s_sigma[0.05,0.35])");
    workspace->factory("Exponential::e(signal_1,s_alpha[-1,0])") ;
    // this is an extended pdf
    workspace->factory("SUM::sig(nBck[0,10000]*e,nSig[0,10000]*g)") ;

    RooFitResult *result = workspace->pdf("sig")->fitTo(data, Minos(kTRUE), Verbose(kTRUE), Timer(kTRUE), Save());
    // Print the correlation matrix
    result->correlationMatrix().Print();
    // Print fit result
    result->Print();
    // print workspace content
    workspace->Print();
    TCanvas* myC = new TCanvas("myC","RooFit Results",1000, 1000);
    myC->Divide(1,3);
    myC->cd(1);
    RooPlot *xframe = signal_1.frame() ;
    data.plotOn(xframe);

    // Plot Error
    workspace->pdf("sig")->plotOn(xframe,VisualizeError(*result));
    workspace->pdf("sig")->plotOn(xframe,Components("g"),LineStyle(kDashed),LineColor(kRed));
    workspace->pdf("sig")->plotOn(xframe,Components("e"),LineStyle(kDotted),LineColor(kGreen));
    workspace->pdf("sig")->plotOn(xframe);
    // Draw xframe
    xframe->Draw();

    // plot residual
    myC->cd(2);
    RooHist* sigResid = xframe->residHist();
    RooPlot* xframe1 = signal_1.frame(Title("Residual Distribution")) ;
    xframe1->addPlotable(sigResid,"P") ;
    xframe1->Draw();

    // plot pull
    myC->cd(3);
    RooHist* sigPull = xframe->pullHist();
    RooPlot* xframe2 = signal_1.frame(Title("Pull Distribution")) ;
    xframe2->addPlotable(sigPull,"P") ;
    xframe2->Draw();

    // Do study
    RooGenFitStudy gfs;
    RooStudyManager mgr(*workspace, gfs);

    gfs.setGenConfig("sig", "signal_1", NumEvents(1000));
    gfs.setFitConfig("sig", "signal_1", PrintLevel(-1));
    gfs.storeDetailedOutput(kTRUE);
    int nToys = 100;
    mgr.run(nToys); // execute nToy toys inline
    // mgr.runProof(nToys,"") ; // execute nToys through PROOF-lite
    gfs.summaryData()->Print();

    RooDataSet * myMC = gfs.summaryData();
    RooRealVar s_mean("s_mean", "Toy MC Mean Signal", 1.9, 2.1);
    RooRealVar s_sigma("s_sigma", "Toy MC Sigma Signal", 0.1, 0.35);
    RooRealVar MeanMCmean("MeanMCmean", "Toy Mean Signal Mean", 1.9, 2.1);
    RooRealVar MeanMCsigma("MeanMCsigma","Toy Sigma Signal Mean",0.2,0.15,0.25);
    RooGaussian MCmeanG ("MCmeanG","mean signal distribution", s_mean, MeanMCmean, MeanMCsigma);

    MCmeanG.fitTo(*myMC, NumCPU(4), Timer(kTRUE));

    TCanvas* mySecondC = new TCanvas("mySecondC", "RooFit Results", 1000, 1000);
    RooPlot *yframe = s_mean.frame();
    myMC->plotOn(yframe);
    MCmeanG.plotOn(yframe);
    yframe->Draw();


    double AlphaTrue = 2.0;
    // Create pull dist
    for (int j = 0 ; j< nToys ; j++ ){
        const RooArgSet* row = myMC->get();
        // RooRealVar* xrow = (RooRealVar*) row->find("s_alpha");
        RooRealVar* xrow = (RooRealVar*) (myMC->get(j)->find("s_alpha"));
        PullMeanAlpha = (xrow->getVal() - AlphaTrue ) / xrow->getError();
    }
    // Write workspace to file
    // workspace->writeToFile("workspace.root");
}
