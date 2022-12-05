## Working code
The majority of the code in the linked repository is "working", although it does not have the final functionality intended.

### Outline

1. devices
    * Interfaces for the joystick, camera, and PWM driver
    * Joystick and PWM driver are implemented and tested.
    * Joystick interface includes a function for generating mock input for testing
    * No content yet in camera file.
2. motion_control
    * Includes inverse kinematics functions and structs for managing motors and joints
    * Implemented and tested IK functions
    * Joint calibration still in progress
3. robot_arm.c
    * Main function in this file
    * Includes setup and main control loop
    * Currently runs calibration function that accepts keyboard input to manipulate one joint at a time
        * Comment out line 257 to execute sequence of simulated inputs from joystick. Risk of damage to arm if servo limits not calibrated beforehand.
