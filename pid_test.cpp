#include <iostream>
#include <chrono>
#include <thread>
#include <vector>   
#include <tuple>
#include <limits>
#include <iomanip>  // 为对齐输出

class PIDController {
public:
    PIDController(double kp, double ki, double kd)
        : kp_(kp), ki_(ki), kd_(kd), integral_(0.0), prev_error_(0.0) {}

    double compute(double setpoint, double process_variable, double dt) {
        double error = setpoint - process_variable;
        integral_ += error * dt;
        double derivative = (error - prev_error_) / dt;
        double output = kp_ * error + ki_ * integral_ + kd_ * derivative;
        prev_error_ = error;
        return output;
    }

    void reset() {
        integral_ = 0.0;
        prev_error_ = 0.0;
    }

private:
    double kp_, ki_, kd_;
    double integral_;
    double prev_error_;
};

std::tuple<double, double, double> autoTunePID(double setpoint) {
    double best_kp = 0, best_ki = 0, best_kd = 0;
    double best_score = std::numeric_limits<double>::max();

    std::cout << "Kp\tKi\tKd\tOvershoot\tError\tSettleStep\tScore\n";

    for (double kp = 0.5; kp <= 3.0; kp += 0.5) {
        for (double ki = 0.0; ki <= 0.3; ki += 0.05) {
            for (double kd = 0.0; kd <= 0.1; kd += 0.02) {
                PIDController pid(kp, ki, kd);
                double process_variable = 20.0;
                double dt = 0.1;
                double max_overshoot = 0.0;
                double final_error = 0.0;
                int settle_step = 50;

                for (int i = 0; i < 50; ++i) {
                    double output = pid.compute(setpoint, process_variable, dt);
                    process_variable += output * dt;

                    double overshoot = process_variable - setpoint;
                    if (overshoot > max_overshoot) {
                        max_overshoot = overshoot;
                    }
                    if (std::abs(process_variable - setpoint) < 0.5 && settle_step == 50) {
                        settle_step = i;
                    }
                }
                final_error = std::abs(process_variable - setpoint);
                double score = final_error + max_overshoot * 2 + settle_step * 0.5;

                // 输出当前测试的参数及结果
                std::cout << std::fixed << std::setprecision(2)
                          << kp << "\t" << ki << "\t" << kd << "\t"
                          << max_overshoot << "\t\t"
                          << final_error << "\t"
                          << settle_step << "\t\t"
                          << score << "\n";

                if (score < best_score) {
                    best_score = score;
                    best_kp = kp;
                    best_ki = ki;
                    best_kd = kd;
                }
            }
        }
    }

    return {best_kp, best_ki, best_kd};
}

int main() {
    double setpoint = 50.0;

    auto [best_kp, best_ki, best_kd] = autoTunePID(setpoint);
    std::cout << "\n----- PID Auto-Tuning Completed -----\n";
    std::cout << "Best PID Parameters Found: "
              << "Kp=" << best_kp
              << ", Ki=" << best_ki
              << ", Kd=" << best_kd << "\n\n";

    PIDController pid(best_kp, best_ki, best_kd);
    double process_variable = 20.0;
    double dt = 0.1;

    for (int i = 0; i < 50; ++i) {
        double output = pid.compute(setpoint, process_variable, dt);
        process_variable += output * dt;

        std::cout << "Step " << i << ": Output = " << output
                  << ", Process Variable = " << process_variable << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dt * 1000)));
    }

    return 0;
}
