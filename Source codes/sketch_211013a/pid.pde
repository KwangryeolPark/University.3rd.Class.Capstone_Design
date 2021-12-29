class PID {

  PID(float kp, float ki, float kd) {
    _kp = kp;
    _ki = ki;
    _kd = kd;
  };

  void setTarget(float target) {
    _target = target;
  }

  float cal(float current) {
    _err = _target - current;

    _p = _err;
    _i += _err;
    _d = (_err - _pErr) / 0.1;

    _pErr = _err;

    return _p * _kp + _i * _ki + _d * _kd;
  };

  void clear() {
    _p = 0;
    _i = 0;
    _d = 0;
  }

  void setPID(float kp, float ki, float kd) {
    _kp = kp;
    _ki = ki;
    _kd = kd;
  };

  float _err = 0;
  float _pErr = 0;
  float _target = 0;
  float _kp, _ki, _kd;
  float _max = 10;
  float _p, _i, _d;
}
