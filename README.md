# StormBot-Esp32-Codebase

Codebase for the University of Arkansas RIOT (Robotics Interdisciplinary Organization of Teams) robot built for the 2025 STORM (Student Tele-Operated Robotics Mission) competition Power Flash. The codebase also includes Automat, a WPILib-based library adapted to the VEX and Esp32 platforms.

Used in parallel with Explothusist/StormBot-Codebase. Our robot includes both a VEX v5 Brain and an Esp32 chip.

Esp32 Codebase: https://github.com/Explothusist/StormBot-Codebase

Uark RIOT website: https://riotrobotics.org/

STORM competition website: https://storm.soonerrobotics.org/about

# Automat (WPILib Imitation)

Under src/Automat, the repository Explothusist/Automat is included as a submodule.

Automat is a partial imitation of the FRC (FIRST Robotics Competition) robot control library WPILib, an open source library built and maintained by the Worchester Polytechnic Institute. WPILib's most outstanding benefit is its simple and efficient command-based robot framework dividing the robot into commands and subsystems. Automat provides most of the basic functionality of WPILib to VEX and Esp32 architectures.

Automat Library: https://github.com/Explothusist/Automat

WPILib: https://docs.wpilib.org/en/stable/docs/software/what-is-wpilib.html

Command-based architecture: https://docs.wpilib.org/en/stable/docs/software/commandbased/what-is-command-based.html