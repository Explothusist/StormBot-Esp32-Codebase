
#ifndef STORMBOT_SendSerialResumeCommand_
#define STORMBOT_SendSerialResumeCommand_

#include "../Automat/automat.h"
#include "storm_serial_utils.h"

class SendSerialResumeCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        SendSerialResumeCommand(atmt::SerialReader* serial); // Put subsystems as parameters
        SendSerialResumeCommand(const SendSerialResumeCommand& command); // Copy constructor
        ~SendSerialResumeCommand();
        atmt::Command* clone() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made


    private:
        atmt::SerialReader* m_serial;
};

#endif