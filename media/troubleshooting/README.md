### Troubleshooting

Screen capture of oscilloscope/logic analyzer during I2C testing and PWM frequency tuning. PCA9685 chip has inaccurate clock and output can be prescaled to obtain exact frequency desired. Freqeuncy of clock was determined experimentally and is `#define`'d in `robot_arm.c` in development repo. Note measured PWM frequency within 0.2% of target 50 Hz.
The logic analyzer pane at the bottom shows the controller sending a series of PWM commands to the PCA9685. The register address 0x06 is the first byte for channel 0, 0x0A is the first byte for channel 1, etc.

![](i2c_debug.PNG)