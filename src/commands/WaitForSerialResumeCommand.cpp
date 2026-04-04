
#include "WaitForSerialResumeCommand.h"

#include <cmath>

WaitForSerialResumeCommand::WaitForSerialResumeCommand(atmt::SerialReader* serial): // Side to side movements
    atmt::Command(),
    m_serial{ serial },
    m_resume_triggered{ false },
    m_last_seen_id{ 0 }
{
    
};
WaitForSerialResumeCommand::WaitForSerialResumeCommand(const WaitForSerialResumeCommand& command):
    atmt::Command(command)
{
    m_serial = command.m_serial;
};
WaitForSerialResumeCommand::~WaitForSerialResumeCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* WaitForSerialResumeCommand::clone() const {
    return new WaitForSerialResumeCommand(m_serial);
};

void WaitForSerialResumeCommand::initialize() {
    m_last_seen_id = m_serial->getNextMessageId();
    m_resume_triggered = false;
};
void WaitForSerialResumeCommand::execute() {
    int total_messages = m_serial->availableMessagesCount();
    uint8_t prefix = 0;
    bool success = false;
    for (size_t i = total_messages; i-- > 0; ) { // Looks weird, but correct reverse iteration
        if (m_serial->getMessageId(i) == m_last_seen_id) {
            break;
        }
        success = m_serial->peekMessagePrefix(i, prefix);
        if (!success) {
            continue;
        }
        if (prefix == Serial_AutonomousResume) {
            m_resume_triggered = true;
            break;
        }
    }
    m_last_seen_id = m_serial->getNextMessageId();
};
void WaitForSerialResumeCommand::end(bool interrupted) {
    
};
bool WaitForSerialResumeCommand::is_finished() {
    return m_resume_triggered;
};
