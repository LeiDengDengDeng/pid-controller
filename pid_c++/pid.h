#pragma once
#include <stdexcept>

struct PIDParam {
    // 以下的Kp、Ki、Kd代表的是P、I、D三部分的常量系数
    double Kp;
    double Ki;
    double Kd;
    double target_value;
    double range_min;
    double range_max;

    PIDParam(double kp, double ki, double kd, double pid_target_value)
        : Kp(kp), Ki(ki), Kd(kd), target_value(pid_target_value), use_range(false) {}

    PIDParam(double kp, double ki, double kd, double pid_target_value, double min, double max)
        : Kp(kp), Ki(ki), Kd(kd), target_value(pid_target_value), range_min(min), range_max(max), use_range(true) {
        if (range_min > range_max) {
            throw std::domain_error("illegal range");
        }
    }

    bool is_use_range() { return use_range; }

private:
    bool use_range;
};

class BasePID {
public:
    BasePID(PIDParam& pid_param) : _pid_param(pid_param) {}

    virtual double collect_and_calculate(const double& current_value) = 0;

protected:
    PIDParam _pid_param;

    void adjust_output(double& output);
};

class PositionalPID : public BasePID {
public:
    PositionalPID(PIDParam& pid_param) : BasePID(pid_param), _sum_err(0), _last_err(0) {}

    double collect_and_calculate(const double& current_value) override;

protected:
    double _sum_err;
    double _last_err;
};

class IncrementalPID : public BasePID {
public:
    IncrementalPID(PIDParam& pid_param) : BasePID(pid_param), _second_last_err(0), _last_err(0), _last_output(0) {}

    double collect_and_calculate(const double& current_value) override;

protected:
    double _second_last_err;
    double _last_err;
    double _last_output;
};