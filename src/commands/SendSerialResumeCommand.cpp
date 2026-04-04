
#include "SendSerialResumeCommand.h"

#include <cmath>

SendSerialResumeCommand::SendSerialResumeCommand(atmt::SerialReader* serial): // Side to side movements
    atmt::Command(),
    m_serial{ serial }
{
    
};
SendSerialResumeCommand::SendSerialResumeCommand(const SendSerialResumeCommand& command):
    atmt::Command(command)
{
    m_serial = command.m_serial;
};
SendSerialResumeCommand::~SendSerialResumeCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* SendSerialResumeCommand::clone() const {
    return new SendSerialResumeCommand(m_serial);
};

void SendSerialResumeCommand::initialize() {
    m_serial->sendMessage(Address_VexBot, Serial_AutonomousResume);
};
void SendSerialResumeCommand::execute() {
    
};
void SendSerialResumeCommand::end(bool interrupted) {
    
};
bool SendSerialResumeCommand::is_finished() {
    return true;
};
