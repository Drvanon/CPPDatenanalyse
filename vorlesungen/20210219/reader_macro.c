using namespace RooFit;

void reader_macro () {
    TFile* tf = new TFile("workspace.root", "OPEN");
    RooWorkspace* w = (RooWorkspace*) tf->Get("w") ;

    RooRealVar *signal_1 = w->var("signal_1");
    RooAbsPdf *sig = w->pdf("sig");
    RooAbsData* data = w->data("data");

    w->Print();

    RooFitResult *result = w->pdf("sig")->fitTo(*data, Minos(kTRUE), Verbose(kTRUE), Timer(kTRUE), Save());
    // Generate Dataset
    RooDataSet *generated = w->pdf("sig")->generate(*signal_1, 1000);
    RooFitResult *result_monte_carlo = w->pdf("sig")->fitTo(*generated, Minos(kTRUE), Verbose(kTRUE), Timer(kTRUE), Save());
}
