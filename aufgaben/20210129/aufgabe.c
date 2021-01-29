void aufgabe () {
    TFile *f = new TFile("fftTTree.root");
    TTree *tr = (TTree*) f->Get("FFT");

    TH1D* thisto = new TH1D("time", "Time entries", 300, 2, 5);
    TH1D* shisto = new TH1D("signal", "Signal entries", 300, -2, 8);
    TH2D* tshisto = new TH2D("time and signal", "Signal entries", 300, 2, 5, 300, -2, 8);

    double t, s;
    tr->SetBranchAddress("t", &t);
    tr->SetBranchAddress("signal", &s);

    for (int i=0; i < 300; i++) {
        tr->GetEntry(i);

        thisto->Fill(t);
        shisto->Fill(s);
        tshisto->Fill(s, t);
    }

    // shisto->GetXaxis()->SetRangeUser(0, 1);
    shisto->Draw();
    // tshisto->Draw();

    TH1* s_fft_phase = 0;
    TH1* t_fft_phase = 0;
    TH1* ts_fft_phase = 0;
    TH1* s_fft_magnitude = 0;
    TH1* t_fft_magnitude = 0;
    TH2* ts_fft_magnitude = 0;

    s_fft_phase = shisto->FFT(s_fft_phase, "PH");
    // ts_fft_phase = tshisto->FFT(ts_fft_phase, "PH");
    // s_fft_phase->Draw();
    // ts_fft_phase->Draw();
}
