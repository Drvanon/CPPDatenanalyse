#include "TDirectory.h"

// Klassendefinition mit Prototypen
class FourVector {
   public:
        FourVector();
        FourVector(double e );
        FourVector(double e, double x, double y, double z);
        FourVector(double x , double y, double z);
        ~FourVector();
        void setE (double e);
        void setP (double x, double y, double z);
        double getEnergy(void) const ;
        double getMomentum (void) const;

        ClassDef (FourVector,1)
    private:
        double  E;
        double  Px;
        double  Py;
        double  Pz;
};
