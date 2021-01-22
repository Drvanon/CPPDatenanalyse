//
// This macro demonstrates a simulation of pi0 -> gamma gamma decays
// within ROOT.
// For given pi0 energy with momentum along Z the decay is isotrop in the
// center of mass system (cms). The cms decay angle thetaCM is drawn from
// [0,pi]. No phi dependence is simulated. The photon energies in the
// laboratory system are calculated using thetaCM and beta and
// gamma.
// Units: c = 1 , Energy in GeV
//
// WS 2016 J.M.
//

double sigmaEnergy(double *x, double *par);
double sigmaTheta(double *x, double *par);

#include <iostream>
#include <tuple>
#include <TRandom3.h>
#include <TMath.h>
#include <TLorentzVector.h>

using namespace std;

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

void pi0Decay(){
    TTree *t = new TTree("tree", "data tree");
    TNtuple* generated_tuple = new TNtuple("pi0Decay", "ground truth data","E1:E2:theta1:theta2:mpi0");
    TNtuple* measured_tuple = new TNtuple("pi0DecayMeasured", "measured data", "E1:E2:theta1:theta2:mpi0");

    for (int i=0;i<100;i++) {
        //void pi0Decay(double pi0Energy = 2.){
        // setup, choose the energy of the pi0, units are GeV
        double pi0Energy = 2. ;
        // Pi0 Mass
        const double pi0Mass = 0.1349766 ;
        // Get relativistic quantities
        double pi0Mass2 = pi0Mass * pi0Mass ;
        double beta = TMath::Sqrt(pi0Energy*pi0Energy - pi0Mass*pi0Mass)/pi0Energy;
        double gamma = pi0Energy / pi0Mass ;
        cout << "Pi0 energy is set to  " << pi0Energy << endl;
        cout << "beta = " << beta << "   gamma= "<< gamma << endl << endl ;

        // Initialize random number generator
        TRandom3 *R = new TRandom3();
        // R->SetSeed(7892344);  // fixed seed for testing
        R->SetSeed(0);  // set seed to machine clock

        // generate decay angle in the center of mass system, decay should be
        // isotropic
        double thetaCM;
        thetaCM = R->Uniform(0.,TMath::Pi());
        cout << "Generated theta in CM: " << thetaCM << endl;

        // Photon energies in the Lab system are
        double E1 = gamma * pi0Mass * (1. + (beta * TMath::Cos(thetaCM))) / 2. ;
        double E2 = gamma * pi0Mass * (1. - (beta * TMath::Cos(thetaCM))) / 2. ;

        //Scattering angles of the Photons
        double Theta1 = TMath::ATan(TMath::Sin(thetaCM) / (gamma * ( beta + TMath::Cos(thetaCM) )));
        double Theta2 = TMath::ATan(TMath::Sin(thetaCM + TMath::Pi()) / (gamma * ( beta + TMath::Cos(thetaCM + TMath::Pi()) )));

        //Opening angle just using energies
        double cosalpha = (1.0 - (pi0Mass2 /(2.*E1*E2)));
        double alpha = TMath::ACos(cosalpha);

        cout << "Photon1: E = " << E1 << " theta = " << Theta1 << "      Photon2:  E = " << E2  << "  theta = " << Theta2 <<   endl;

        //Set FourVector of the photons
        TLorentzVector photon1 , photon2;
        photon1.SetPxPyPzE(E1*TMath::Cos(Theta1),0.,E1*TMath::Sin(Theta1),E1);
        photon2.SetPxPyPzE(E2*TMath::Cos(Theta2),0.,E2*TMath::Sin(Theta2),E2);

        //Opening angle as function of thetaCM
        //double temp = gamma * gamma * (1. - (beta* beta * TMath::Cos(thetaCM)*TMath::Cos(thetaCM))) ;
        //double alpha =  TMath::ACos(1. - (2./temp));

        //minimum opening angle
        double alphaMin = 2. * TMath::ASin(1./gamma) ;
        //minimum and maximum values of the energy
        double EMax = gamma * pi0Mass/2. * (1. + beta ) ;
        double EMin = gamma * pi0Mass/2. * (1. - beta ) ;
        cout << "Minimum opening angle : " << alphaMin << endl;
        cout << "Maximum photon energy : " << EMax << endl;
        cout << "Minimum photon energy : " << EMin << endl;

        double mpi0Calc = TMath::Sqrt(2.* E1 * E2 * (1. - cosalpha));
        double mpi0FourVec =  TMath::Sqrt((photon1+photon2)*(photon1+photon2));

        cout << "Calculated Mass pi0 = " << mpi0Calc  <<  "     Input pi0 Mass  " << pi0Mass <<  "  using FourVectors " << mpi0FourVec <<   endl;

        generated_tuple->Fill(E1, E2, Theta1, Theta2, mpi0FourVec);

        double E_par[3] = {0.07, 0.05, 0.1};
        double theta_par[1] = {0.004};
        double E1_measured = R->Gaus(E1, sigmaEnergy(&E1, E_par));
        double E2_measured = R->Gaus(E2, sigmaEnergy(&E2, E_par));
        double Theta1_measured = R->Gaus(Theta1, sigmaTheta(&E1, theta_par));
        double Theta2_measured = R->Gaus(Theta2, sigmaTheta(&E2, theta_par));


        TLorentzVector measured_photon1 , measured_photon2;
        measured_photon1.SetPxPyPzE(E1_measured*TMath::Cos(Theta1_measured),0.,E1_measured*TMath::Sin(Theta1_measured),E1_measured);
         measured_photon2.SetPxPyPzE(E2_measured*TMath::Cos(Theta2_measured),0.,E2_measured*TMath::Sin(Theta2_measured),E2_measured);

        double measured_mpi0FourVec =  TMath::Sqrt((measured_photon1+measured_photon2)*(measured_photon1+measured_photon2));
        measured_tuple->Fill(E1_measured, E2_measured, Theta1_measured, Theta2_measured, measured_mpi0FourVec);
    }

    TFile* f = new TFile("pi0DecayData.root", "RECREATE");
    generated_tuple->Write();
    measured_tuple->Write();
}
