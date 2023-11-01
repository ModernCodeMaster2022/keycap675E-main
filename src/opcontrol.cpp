#include "main.h"
#include "pros/adi.h"
#include "pros/misc.h"
#include "pros/motors.h"

// local variable defined
const int vel = 450;
bool plat_down = false;
bool cata_down = false;
bool Ractivern = false;
bool Lactivern = false;

// Defines how the catapult will lower and launch with limit switch: Ports 6 and E, R1
void catapult() {
    pros::Motor cata(CATAPULT_PORT, pros::E_MOTOR_GEARSET_36);
    // pros::c::adi_pin_mode(LIMIT_SWITCH, INPUT);
    pros::ADIDigitalIn limit_switch(LIMIT_SWITCH);
    while (true) {
        // If R1 is pressed, run catapult
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && plat_down && !cata_down) {
            while (limit_switch.get_value() == 0) {
                cata.move_velocity(60);
            }
            cata.move_velocity(0);
            cata_down = true;
        }
        
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && plat_down && cata_down) {
            cata.move_velocity(40);
            pros::delay(500);
            cata.move_velocity(0);
            cata_down = false;
        }
        // master.print(0, 0, "limit: %i", limit_switch.get_value());
    }
    pros::delay(ez::util::DELAY_TIME); 
}


// Defines how the robot will take in tri-balls: Port 5, L1/L2
int intake() {
    pros::Motor intake (INTAKE_PORT, pros::E_MOTOR_GEARSET_36);
    while (true) {
        // If L1 is pressed, intake. If pressed again, outtake.
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intake.move_velocity(-vel); // appro. velocity?
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake.move_velocity(vel);
        }
        else {
            intake.move_velocity(0);
        }
        pros::delay(ez::util::DELAY_TIME);
        
    }
    pros::delay(ez::util::DELAY_TIME); 
    return 1;
}

int outtake() {
        pros::Motor outtake (CATAPULT_PORT, pros::E_MOTOR_GEARSET_36);
    while (true) {
        // If L1 is pressed, intake. If pressed again, outtake.
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) 
            && master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            outtake.move_velocity(-vel); // appro. velocity?
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) 
            && master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            outtake.move_velocity(vel);
        }
        else {
            outtake.move_velocity(0);
        }
        pros::delay(ez::util::DELAY_TIME);
        
    }
    pros::delay(ez::util::DELAY_TIME); 
    return 1;
}


// defines how the polycarbon platform functions based on catapult position: Port H, R2
void platform() {
    pros::ADIDigitalOut plat ('H'); // port 'H'
    plat.set_value(false); // retracted
while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !plat_down) {
            plat.set_value(true);
            plat_down = true;
            pros::delay(355); 
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && plat_down && !cata_down) {
            plat.set_value(false);
            plat_down = false;
            pros::delay(355); 
        }
    }
    pros::delay(ez::util::DELAY_TIME); 
}


// Defines how the wings on the robot extend: Ports G and B, d-pad buttons
void Rwing() {
    // extends/retracts right piston when button(s) is pressed 
    pros::ADIDigitalOut pistonR ('G');
    pistonR.set_value(false);
    pros::ADIDigitalOut pistonL ('B');
    pistonL.set_value(false);

    while (true) {
        if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_B)
        || master.get_digital(pros::E_CONTROLLER_DIGITAL_A)
        || master.get_digital(pros::E_CONTROLLER_DIGITAL_X)
        || master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
        && !Ractivern) {
            pistonR.set_value(true);
            pistonL.set_value(true);
            Ractivern = true;
            pros::delay(305); 

        }
        else if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_B)
        || master.get_digital(pros::E_CONTROLLER_DIGITAL_A)
        || master.get_digital(pros::E_CONTROLLER_DIGITAL_X) 
        || master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
        && Ractivern) {
            pistonR.set_value(false);
            pistonL.set_value(false);
            Ractivern = false;
            pros::delay(305);
        }
    }
    pros::delay(ez::util::DELAY_TIME); 
    
}