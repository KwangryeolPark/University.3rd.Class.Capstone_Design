#ifndef _PID_H
#define _PID_H

class PID {
  public:
    PID(float, float, float);           //  Set the echo of p, i, d gain
    void setLmt(float, float, float);   //  Set the limitation of _p, _i, _d
    void setCur(float);                 //  Set current
    void setTrg(float);                 //  Set target
    void setRng(float, float);                 //  Set the rang of pid;
    float pid(void);

  private:
    float _kp, _ki, _kd;
    float _pLmt, _iLmt, _dLmt;
    float _p, _i, _d;
    float _pErr;
    float _target, _current;
    float _mRng, _MRng;
};

PID::PID(float kp, float ki, float kd) {
  _kp = kp;
  _ki = ki;
  _kd = kd;
};

void PID::setLmt(float pLmt, float iLmt, float dLmt) {
  _pLmt = pLmt;
  _iLmt = iLmt;
  _dLmt = dLmt;
};

void PID::setCur(float current) {
  _current = current;
};

void PID::setTrg(float target) {
  _target = target;
};

void PID::setRng(float mRng, float MRng) {
  _mRng = mRng;
  _MRng = MRng;
};

float PID::pid(void) {
  float err = _target - _current;

  _p = err;
  _i = _i + err;
  _d = (err - _pErr) / 1000.0;

  float p, i, d;

  p = _p * _kp;
  i = _i * _ki;
  d = _d * _kd;

  if (p > _pLmt) {
    p = _pLmt;
  } else if (p < -_pLmt) {
    p = -_pLmt;
  }

  if (i > _iLmt) {
    i = _iLmt;
  } else if (i < -_iLmt) {
    i = -_iLmt;
  }

  if (d > _dLmt) {
    d = _dLmt;
  } else if (d < -_dLmt) {
    d = -_dLmt;
  }

  _pErr = err;

  float pid = p + i + d;

  if (pid > _MRng) {
    return _MRng;
  } else if (pid < _mRng) {
    return _mRng;
  }
  return pid;
};


#endif
