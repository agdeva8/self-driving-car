#include "math.h"

// keeping pins so to revmove collisions:
int pin_motor_left_speed    = A5;
int pin_motor_left_dir      = 4;
int pin_motor_right_speed   = A6;
int pin_motor_right_dir     = 7;

int pin_ir_left             = A0;
int pin_ir_center           = A1;
int pin_ir_right            = A2;

class IR
{
  public:
    int pin_number = A0;
    int val[4] = {0};
    void set_pin(int pin)
    {
      pin_number = pin;
    }
    void init_ir()
    {
       pinMode(pin_number,INPUT);
    } 
    int read_ir()
    {
      return analogRead(pin_number);
    }
    
    int init_ir_values()
    { 
      while(!Serial.available()){}
      for(int i=0;i<4; i++){
        int start_read;
        Serial.println("start setup? T=1 ");
        while(Serial.parseInt() != 1)
        {
        }
        val[i] = read_ir();
        Serial.print("Value of: "); Serial.print(i); Serial.print(" is "); Serial.println(val[i]);
      }
    }
};


class Motor
{
public:
  int speed_pin = 0;
  int dir_pin = 0;
  
  void set_pin(int speed_pin_number, int dir_pin_number)
  {
    speed_pin = speed_pin_number;
    dir_pin = dir_pin_number;
  }
  
  void init_motor()
  {
    pinMode(speed_pin,OUTPUT);
    pinMode(dir_pin,OUTPUT); 
  }
  
  void set_speed(int val)
  {
    analogWrite(speed_pin,val);
  }
  
  void rotate_anitclockwise()
  {
    digitalWrite(dir_pin,0);
  }

   void rotate_clockwise()
  {
    digitalWrite(dir_pin,1);
  }
};


class IR ir_left; class IR ir_center; class IR ir_right;
Motor left_motor; Motor right_motor;


void setup() {
  Serial.begin(9600);
  
  ir_left.set_pin(pin_ir_left);
  ir_center.set_pin(pin_ir_center);
  ir_right.set_pin(pin_ir_right);
  
  /*Serial.print("init ir values for left");
  ir_left.init_ir_values();
  Serial.print("init ir values for center");
  ir_center.init_ir_values();
  Serial.print("init ir values for right");
  ir_right.init_ir_values();
  */
  left_motor.set_pin(pin_motor_left_speed, pin_motor_left_dir);    //speed, direction pin
  left_motor.init_motor(); 
  right_motor.set_pin(pin_motor_right_speed, pin_motor_right_dir);   //speed, direction pin
  right_motor.init_motor();  
}

void loop() {

  Serial.print(ir_left.read_ir());    Serial.print(" "); 
  Serial.print(ir_center.read_ir());  Serial.print(" "); 
  Serial.print(ir_right.read_ir());  Serial.print(" "); 
  Serial.println(" ");
  
  left_motor.set_speed(255);
  left_motor.rotate_clockwise();

  right_motor.set_speed(255);
  right_motor.rotate_clockwise();
  

  delay(1000);
}
