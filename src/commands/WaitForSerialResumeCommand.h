
#ifndef STORMBOT_WAITFORSERIALRESUMECOMMAND_
#define STORMBOT_WAITFORSERIALRESUMECOMMAND_

#include "../Automat/automat.h"
#include "storm_serial_utils.h"

class WaitForSerialResumeCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        WaitForSerialResumeCommand(atmt::SerialReader* serial); // Put subsystems as parameters
        WaitForSerialResumeCommand(const WaitForSerialResumeCommand& command); // Copy constructor
        ~WaitForSerialResumeCommand();
        atmt::Command* clone() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made


    private:
        atmt::SerialReader* m_serial;
        int m_last_seen_id;
        bool m_resume_triggered;
};

#endif