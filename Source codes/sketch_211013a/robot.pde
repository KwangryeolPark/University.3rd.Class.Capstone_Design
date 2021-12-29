class Robot {
  Robot(float x, float y, float angle) {
    _VR.set(0, 0);
    _VL.set(0, 0);
    _R_position.set(x, y);
    _L_motor_position.set(x - (_dr / 2.0) * cos(angle), y - (_dr / 2.0) * sin(angle));
    _R_motor_position.set(x + (_dr / 2.0) * cos(angle), y + (_dr / 2.0) * sin(angle));
    _R_theta = PI / 2 + angle;
  };

  void wheel(float l, float r) {
    if (_status == 1) {
      _vr = r;
      _vl = l;
      if (_vr < 0 || _vl < 0) {
        _dir = -1;
      } else if (_vr > 0 || _vl > 0) {
        _dir = 1;
      }
      _R_delta = (_vr - _vl) / _dr;
      _R_theta = _R_theta + _R_delta;
      if (_R_theta > PI * 2) {
        _R_theta = _R_theta - PI * 2;
      }
      if (_R_theta < 0) {
        _R_theta = _R_theta + PI * 2;
      }

      _VR.set(_vr * cos(_R_theta), _vr * sin(_R_theta));
      _VL.set(_vl * cos(_R_theta), _vl * sin(_R_theta));

      _V_robot = PVector.div(PVector.add(_VR, _VL), 2);

      //    _R_position = PVector.add(_V_robot, _R_position);
      _L_motor_position = PVector.add(_VL, _L_motor_position);
      _R_motor_position = PVector.add(_VR, _R_motor_position);
      _R_position = PVector.add(_L_motor_position, _R_motor_position);
      _R_position = PVector.div(_R_position, 2);
    }
  };

  void motor(float l, float r) {
    wheel(-l, -r);
  }


  PVector get() {
    return _R_position;
  };

  PVector rmotor() {
    return _R_motor_position;
  };

  PVector lmotor() {
    return _L_motor_position;
  };

  float direction() {
    return _R_theta;
  }

  void show() {
    strokeWeight(5);
    stroke(0, 0, 0);
    point(_R_position.x, _R_position.y);

    /*    stroke(255, 0, 0);
     point(robot.rmotor().x, robot.rmotor().y);
     
     stroke(0, 255, 0);
     point(robot.lmotor().x, robot.lmotor().y);*/

    strokeWeight(1);
    stroke(0);
    noFill();
    ellipse(_R_position.x, _R_position.y, _dr, _dr);
    line(_R_position.x, _R_position.y,
      _R_position.x + _dir * _direction_bar * cos(_R_theta), _R_position.y + _dir * _direction_bar * sin(_R_theta));
  }

  void stop() {
    _status = 0;
  }
  void start() {
    _status = 1;
  }

  void setTarget(PVector target) {
    PVector robotD = PVector.fromAngle(direction());
    PVector targetVector = PVector.sub(target, _R_position);

    float distance = PVector.dist(target, _R_position);
    float radian = PVector.angleBetween(robotD, targetVector);
    if (asin((robotD.x * targetVector.y - robotD.y * targetVector.x) / (distance)) < 0) {
      radian = -radian;
    }

//    println(radian / PI * 180);
    if (_status == 1) {
      float pidA = pid1.cal(radian);
      float pidD = pid2.cal(distance);

      //  println(pid);
      wheel(pidA - pidD, -pidA - pidD);
    }
  };


  PID pid1 = new PID(10, 0, 0);
  PID pid2 = new PID(0.05, 0, 0.01);
  float _vr = 0, _vl = 0;
  float _R_theta = 0;
  float _dr = 50;
  float _R_delta = 0;
  float _direction_bar = 50;
  int _dir = 1;
  int _status = 1;

  PVector _R_position = new PVector();
  PVector _VR = new PVector();
  PVector _VL = new PVector();
  PVector _V_robot = new PVector();
  PVector _L_motor_position = new PVector();
  PVector _R_motor_position = new PVector();
}
