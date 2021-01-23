#include <TRandom3.h>
#include <TH2.h>
#include <TF2.h>

void fill_fit () {
    TH2D* hist = new TH2D("hist", "filled histogram", 100, -10, 10, 100, -10, 10);
    TF2* F2 = new TF2("bigaus", "bigaus", -10, 10, -10, 10);
    F2->SetParameters(
        1, 5, 1, 5, 1, .8
    );
    TRandom3* T = new TRandom3(0);
    hist->FillRandom("bigaus", 1e4);

    hist->Draw("colz");

    hist->Fit("bigaus");
}
