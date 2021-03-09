#include "BSM.h"
#include <math.h>
#include <time.h>


BSM::BSM(float ass, float strk, float grwth, float volty, float yrs, long steps, long sims)
{
    bsmAsset = ass;
    bsmStrike = strk;
    bsmGrowth = grwth;
    bsmVol = volty;
    bsmYears = yrs;
    bsmSteps = steps;
    bsmMonteCarloSims = sims;
}

BSM::~BSM(){std::cout << "Destroyed";}

/*

S{PHI}(d1) - Ke-rT{PHI}(d2) 

Asset price 100, Call option, strike price 110

100 -> 101 -> 99 -> 110 -> 125   (15)

100 -> 98 -> 97 -> 54 -> 109      (0)

100 -> 97 -> 112 -> 116 -> 116    (6) +
                                -----
                                  21/3 => 7


 */                               

void BSM::logNormalRandomWalk()
{
    srand((unsigned)time(0));

    double callPayoffPot = 0.0;
    double putPayoffPot = 0.0;

    double timeStep = (getBsmYears()/getBsmSteps());
    double sqrtTs = sqrt(timeStep);

    for (long i = 1; i <= getBsmMonteCarloSims(); i++)
    {
        double ass = getBsmSteps();

        for(int j = 1; j <= getBsmSteps(); j++)
        {
            ass = ass * (1 + getBsmGrowth()*timeStep + getBsmVol()*sqrtTs*(12*rn() - 6));

            std::cout << "Step: " << j << " ass: " << ass << std::endl;
        }
    }
}

double BSM::rn()
{
    return (double)rand()/(double)(RAND_MAX + 1.0);
}

float BSM::getBsmAsset(){return bsmAsset;}
float BSM::getBsmStrike(){return bsmStrike;}
float BSM::getBsmGrowth(){return bsmGrowth;}
float BSM::getBsmVol(){return bsmVol;}
float BSM::getBsmYears(){return bsmYears;}
long BSM::getBsmSteps(){return bsmSteps;}
long BSM::getBsmMonteCarloSims(){return bsmMonteCarloSims;}

double BSM::getCallPrice(){return bsmCallPrice;}
double BSM::getPutPrice(){return bsmPutPrice;}


