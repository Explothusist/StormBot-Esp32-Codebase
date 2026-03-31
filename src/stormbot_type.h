#ifndef STORMBOT_ROBOT_TYPE_
#define STORMBOT_ROBOT_TYPE_

// #define STORMBOT_ESPNOW_CONTROLLER_
#define STORMBOT_ROBOT_DASHBOARD_

#if defined(STORMBOT_ESPNOW_CONTROLLER_) + defined(STORMBOT_ROBOT_DASHBOARD_) != 1
    #error "Exactly one StormBot control system should be defined"
#endif

#endif