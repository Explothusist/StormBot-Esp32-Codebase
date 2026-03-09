
#ifndef STORMBOT_
#define STORMBOT_

#include "../Automat/automat.h"
#include "RobotContainer.h"

class StormBot : public atmt::TimedRobot {
    public:
        StormBot();
        ~StormBot();

        void robotInit() override;
        void robotPeriodic() override;
        void robotExit() override;
        
        void disabledInit() override;
        void disabledPeriodic() override;
        void disabledExit() override;
        
        void autonomousInit() override;
        void autonomousPeriodic() override;
        void autonomousExit() override;
        
        void teleopInit() override;
        void teleopPeriodic() override;
        void teleopExit() override;

        void addSerialReader(atmt::SerialReader* reader){} // Added as a placeholder for compilation

    private:
        RobotContainer* m_bot_cont;
};

#endif