#ifndef __SENSOR_UPDATE_H__
#define __SENSOR_UPDATE_H__

typedef enum __UserMode{
    E_USER_MODE_OFF = 0,
    E_USER_MODE_AUTO,
    E_USER_MODE_LOW,
    E_USER_MODE_HIGH,
    E_USER_MODE_MAX
}E_USERMODE_t;

typedef enum __RainLevel{
    E_RAIN_LEVEL_DRY = 0,
    E_RAIN_LEVEL_LIGHTWEIGHT,
    E_RAIN_LEVEL_HEAVY,
    E_RAIN_LEVEL_MAX
}E_RAINLEVEL_t;

typedef enum __SpeedLevel{
    E_SPEED_LEVEL_LOW = 0,
    E_SPEED_LEVEL_HIGH,
    E_SPEED_LEVEL_MAX
}E_SPEEDLEVEL_t;


int getUserMode();
int getRainData();
int getSpeedData();


#endif // __SENSOR_UPDATE_H__