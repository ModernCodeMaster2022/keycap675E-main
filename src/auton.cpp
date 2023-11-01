#include "main.h"

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed). When this is 87%, the robot is correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;
const int INTAKE_SPEED = 80;

///
// Combining Turn + Drive basic set-up as of 10/8/23
///
void drive_and_turn() {
  // chassis.set_drive_pid(5, DRIVE_SPEED, true);
  // chassis.wait_drive();

  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_turn_pid(-45, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_turn_pid(0, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  //  chassis.wait_drive();
}

///
// 10/15/23 auton
///
void triball_sweep() {
  // pros::Motor intake (INTAKE_PORT, pros::E_MOTOR_GEARSET_36);
  // chassis.set_drive_pid(1, DRIVE_SPEED, true);
  // chassis.wait_drive();

  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(20, DRIVE_SPEED, true);
  // chassis.wait_drive();

  

  // chassis.set_drive_pid(-20, DRIVE_SPEED, true);
  // chassis.wait_drive();

  
}

///
// 10/18/23 auton
///
void right_auton() {
  pros::ADIDigitalOut pistonL ('B');
  pistonL.set_value(false);
  pros::Motor intake(INTAKE_PORT, pros::E_MOTOR_GEARSET_36);


  chassis.set_drive_pid(-15, DRIVE_SPEED, true);
  chassis.wait_drive();
  pistonL.set_value(true);
  chassis.wait_drive();
  chassis.set_drive_pid(15, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(70, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(40, DRIVE_SPEED, true);
  chassis.wait_drive();


}

void auton_win() {
  pros::Motor intake(INTAKE_PORT, pros::E_MOTOR_GEARSET_36);
}

