#pragma once

#include <libindi/indiguiderinterface.h>
#include <libindi/inditelescope.h>

#define TelescopeMotionNS INDI_DIR_NS
#define TelescopeMotionWE INDI_DIR_WE

class ArduinoGEMDriver : public INDI::Telescope, public INDI::GuiderInterface
{
public:
    ArduinoGEMDriver();

    virtual const char *getDefaultName() override;
    virtual bool Connect() override;
    virtual bool Disconnect() override;
    virtual bool ReadScopeStatus() override;
    virtual bool Handshake() override;
    virtual bool initProperties() override;
    // virtual void ISGetProperties(const char *dev) override;
    virtual bool updateProperties() override;

    // virtual bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override;
    // virtual bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override;

protected:
    // General device functions
    // bool Connect();
    // bool Connect(const char *port);
    // bool Disconnect();
    // const char *getDefaultName();
    // bool initProperties();

    // Telescope specific functions
    char ACK();
    void flushSerialBuffer(int timeout);
    // bool ReadScopeStatus();
    bool get_static_properties();
    bool Goto(double,double);
    bool Sync(double ra, double dec);

    virtual bool MoveNS(INDI_DIR_NS dir, TelescopeMotionCommand command) override;
    virtual bool MoveWE(INDI_DIR_WE dir, TelescopeMotionCommand command) override;
    virtual bool Abort() override;

    virtual IPState GuideNorth(uint32_t ms) override;
    virtual IPState GuideSouth(uint32_t ms) override;
    virtual IPState GuideEast(uint32_t ms) override;
    virtual IPState GuideWest(uint32_t ms) override;
    
private:
    double currentRA;
    double currentDEC;
    double targetRA;
    double targetDEC;
    
    double DECToAxisDegrees(double dec);
    double AxisDegreesToDec(double degrees);
    
    bool serialCommand(char *command, char *responseBuffer, bool getResponse);
    
    int RA_gearpos;
    int DEC_gearpos;
    int RA_gearpos_target;
    int DEC_gearpos_target;
    int RA_gearpos_max;
    int DEC_gearpos_max;

    unsigned int DBG_SCOPE;

    INumber GuideRateN[2];
    INumberVectorProperty GuideRateNP;

};

