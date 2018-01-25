/** Lab 15 - Sine Wave Calculations
 *
 * Martina Nunvarova
 * 25/01/2018
 */

///includes
#include <math.h>
#include <iostream>
///namespace
using namespace std;



///define the class
class CSine {

private:                                            ///stuff not available to the outside world

    char x;                                         /// 'o': omega; 'f':frequency (which of them is the precise one) - not really used, could be used to reproduce the equation (with either omega or 2*pi*f)
    double a,f,o,t,dc;                              ///a-mplitude; f-requency; o-mega = 2pi*f; t-heta (phase?); dc-offset

    void readInput(bool negative, double *n)        ///a user input function only positive numbers - called internally only (private)
    {
        do {
            cin >> *n;
            if (!negative && *n<0)
                cout << "Invalid input, try again: ";
        } while (!negative && *n<0);
    }
    double abs(double n)                            ///absolute value - used in calculation of RMS
    {
        if (n<0)
            return -n;
        else
            return n;
    }


public:                                             ///the publicly available functions and variables

    double thePeriod, lastPeakValue, lastRmsValue;  ///data that are required to be stored

    CSine(bool userInput=false)                     ///constructor, parametre "userInput" can be omitted
    {
        double n;
        if (!userInput) {                           ///and it will prefill the values as spec
            a=1;
            t=0;
            dc=0;
            setFrequency(1000);                     ///set frequency, calculate omega and period in one go!
        } else {                                    ///if user input required, it will prompt and store the values (or uses defaults)
            cout << endl
                 << "Please enter the peak voltage [V]: ";
            readInput(false, &a);                   ///limit input to positive only
            if (!a) {
                a=1;
                cout << "Using the default 1V"<<endl;
            }
            cout << "Please enter frequency [Hz]: ";
            readInput(false, &n);                   ///limit input to positive only
            if (!n) {
                setFrequency(1000);
                cout << "Using the default 1kHz"<<endl;
            } else
                setFrequency(n);
            cout << "Please enter phase shift [rads]: ";
            cin >> t;

            cout << "Please enter DC offset [V]: ";
            cin >> dc;
        }
    }
    CSine(double aAmplitude, double aFreq, double aTheta, double aDCOffset) ///constructor, initialize to values passed as parametre
    {
        a=aAmplitude;
        t=aTheta;
        dc=aDCOffset;
        setFrequency(aFreq);
    }

    ///******************** SET functions               --- self explanatory

    void setOmega(double aOmega)
    {
        o=aOmega;
        f=o/2.0/M_PI;
        x='o';              ///if ever needed to know what was the input value exactly
        getPeriod();        ///also initialize the thePeriod variable, since it must be stored
    }
    void setFrequency(double aFreq)
    {
        f=aFreq;
        o=2*M_PI*f;
        x='f';              ///if ever needed to know what was the input value exactly
        getPeriod();        ///also initialize the thePeriod variable, since it must be stored
    }
    void setAmplitude(double aAmplitude)
    {
        a=aAmplitude;
    }
    void setPeriod(double aPeriod)
    {
        setFrequency(1/aPeriod);
    }
    void setPhaseShift(double aPhase)
    {
        t=aPhase;
    }
    void setDCOffset(double aDCOffset)
    {
        dc=aDCOffset;
    }
    ///*********************GET
    double getPeriod()
    {
        return thePeriod=1/f;
    }
    double getOmega()
    {
        return o;
    }
    double getFrequency()
    {
        return f;
    }
    double getPeakValue(double aTime)               ///instantaneous voltage
    {
        return lastPeakValue=a*sin(o*aTime+t)+dc;
    }
    double getAmplitude()
    {
        return a;
    }
    double getDCOffset()
    {
        return dc;
    }
    double getPhaseShift()
    {
        return t;
    }
    double getRMSValue(double aTime)
    {
        return lastRmsValue=abs(getPeakValue(aTime)/sqrt(2));
    }
};

int main(void)
{
    double  t;                                  ///temporary variable (time)

    CSine   signal1,                            ///no user input, just make it default
            signal2(5,2000,90*M_PI/180.0,0),    ///preset values
            signal3(true);                      ///try get values from user

    ///Display info (demonstrate the functions - self-explanatory)
    cout <<"Default object: "<<endl<<"T = "<< signal1.getPeriod()
         << " s; Amplitude = " << signal1.getAmplitude()<<" V"<<endl<<endl;

    cout <<"Readymade test: "<<endl
         <<"T = "<< signal2.getPeriod()
         << " s; V(@250us) = "<< signal2.getPeakValue(250e-6)
         << " V; Vrms (@ 250us) = " << signal2.getRMSValue(250e-6)<<" V"<<endl<<endl;
    cout <<"---------------------------------------------------------------------------"<<endl<<endl;

    cout << "Please enter the time for instantaneous voltages [s]: ";
    cin >>t;

    cout <<"User object: "<<endl
        <<"T = "<< signal3.getPeriod()
        << " s; V(@ "<<t<<"[s]) = " << signal3.getPeakValue(t)
        <<" V; Vrms(@ "<<t<<"[s]) = " << signal3.getRMSValue(t)<<" V"<<endl<<endl;

    cout <<"User object parametres: "<<endl<<endl
         <<"Amplitude: "<<signal3.getAmplitude()<<"[V]"<<endl
         <<"Frequency: "<<signal3.getFrequency()<<"[Hz]"<<endl
         <<"Ang.freq.: "<<signal3.getOmega()<<"[rad/sec]"<<endl
         <<"Period   : "<<signal3.getPeriod()<<"[s]"<<endl
         <<"DC Offset: "<<signal3.getDCOffset()<<"[V]"<<endl
         <<"Ph. shift: "<<signal3.getPhaseShift()<<"[rad]"<<endl
         <<"Last RMS : "<<signal3.lastRmsValue<<"[V]"<<endl
         <<"Last Peak: "<<signal3.lastPeakValue<<"[V]"<<endl;

    return 0;                                                       ///and finally exit to OS, no errors.
}
