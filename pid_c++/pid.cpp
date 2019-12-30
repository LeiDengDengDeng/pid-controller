#include "pid.h"
#include <iostream>

void BasePID::adjust_output(double& output) {
    if (_pid_param.is_use_range()) {
        if (output > _pid_param.range_max) {
            output = _pid_param.range_max;
        } else if (output < _pid_param.range_min) {
            output = _pid_param.range_min;
        }
    }
}

double PositionalPID::collect_and_calculate(const double& current_value) {
    double error = _pid_param.target_value - current_value;
    _sum_err += error;

    double output = _pid_param.Kp * error + _pid_param.Ki * _sum_err + _pid_param.Kd * (error - _last_err);

    _last_err = error;

    adjust_output(output);
    return output;
}

double IncrementalPID::collect_and_calculate(const double& current_value) {
    double error = _pid_param.target_value - current_value;
    // 用的是图上公式的第一步，为了和位置式PID中的Kp、Ki、Kd保持意义一致
    double delta_output = _pid_param.Kp * (error - _last_err) + _pid_param.Ki * error +
                          _pid_param.Kd * (error - 2 * _last_err + _second_last_err);
    double output = _last_output + delta_output;

    // 使用调整前的值保存为last_output，避免数据丢失
    _last_output = output;
    _second_last_err = _last_err;
    _last_err = error;

    adjust_output(output);
    return output;
}

int main() {
    PIDParam param(5, 1, 1, 80);

    std::cout << "--------------Positional--------------" << std::endl;

    PositionalPID positional_pid(param);
    std::cout << "current:30,output:" << positional_pid.collect_and_calculate(30) << std::endl;
    std::cout << "current:50,output:" << positional_pid.collect_and_calculate(50) << std::endl;
    std::cout << "current:60,output:" << positional_pid.collect_and_calculate(60) << std::endl;

    std::cout << "--------------------------------------\n" << std::endl;

    std::cout << "--------------Incremental-------------" << std::endl;

    IncrementalPID incremental_pid(param);
    std::cout << "current:30,output:" << incremental_pid.collect_and_calculate(30) << std::endl;
    std::cout << "current:50,output:" << incremental_pid.collect_and_calculate(50) << std::endl;
    std::cout << "current:60,output:" << incremental_pid.collect_and_calculate(60) << std::endl;

    std::cout << "--------------------------------------" << std::endl;

    return 0;
}