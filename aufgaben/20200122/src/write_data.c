void write_data() {
    std::cout << "Initializing four vectors." << std::endl;
    FourVector* pion = new FourVector(100, 1, 1, 1);
    FourVector* kaon = new FourVector(50, 1, 4 , 5);

    std::cout << "Opening file" << std::endl;
    TFile* f = new TFile("test.root", "RECREATE");

    std::cout << "Creating tree" << std::endl;
    TTree *t = new TTree("particle_data","Data on particles");

    std::cout << "Setting branches" << std::endl;
    FourVector particle;
    t->Branch("particles", &particle);
    particle = *pion;
    t->Fill();
    particle = *kaon;
    t->Fill();

    std::cout << "Writing tree" << std::endl;
    t->Write();
    f->Write();
}
