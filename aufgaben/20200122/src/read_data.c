void read_data() {
    TFile* f = new TFile("test.root", "READ");
    TTree *tree = (TTree*) f->Get("particle_data");

    FourVector* particle;

    tree->SetBranchAddress("particles", &particle);

    for (int i=0; i<tree->GetEntries(); i++) {
        tree->GetEntry(i);
        std::cout << particle->getMomentum() << std::endl;
    }
}
