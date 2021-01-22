//
//      // Calorimeter resolution parameters
//      double EnergyPar[3] = {0.05,0.07,0.01};
//      // Angular resolution parameters
//      double ThetaPar = 0.004 ;
//
//

// function to parametrize energy resolution
double sigmaEnergy(double *x, double *par) {
    //    sigma^2  =
    //               (0.05 * sqrt E)^2 +
    //               (0.07 GeV)^2 +
    //               (0.01 E )^2
    //    x[0] : energy [GeV]

    double sampling = par[0] ;
    double noise   = par[1] ;
    double constant  = par[2] ;


    double sig =   (sampling*TMath::Sqrt(x[0]))*(sampling*TMath::Sqrt(x[0]))
        + noise * noise
        + (constant*x[0])*(constant*x[0]) ;
    return TMath::Sqrt(sig)  ;
}
// function to parametrize position resolution
double sigmaTheta(double *x, double *par) {
    //    sigma   = angularRes / sqrt E [GeV]
    double angularRes = par[0] ;
    return  angularRes / TMath::Sqrt(x[0])  ;
}
