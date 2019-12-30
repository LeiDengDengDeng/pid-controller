package pid;

/**
 * @author deng
 * @date 2019/12/30
 */
public class IncrementalPID extends BasePID {
    private double secondLastErr;
    private double lastErr;
    private double lastOutput;

    public IncrementalPID(PIDParam pidParam) {
        super(pidParam);
        this.secondLastErr = 0;
        this.lastErr = 0;
        this.lastOutput = 0;
    }

    public double collectAndCalculate(double currentVal) {
        double error = pidParam.getTargetVal() - currentVal;
        // 用的是图上公式的第一步，为了和位置式PID中的kP、kI、Kd保持意义一致
        double delta_output = pidParam.getKP() * (error - lastErr)
                + pidParam.getKI() * error
                + pidParam.getKD() * (error - 2 * lastErr + secondLastErr);
        double output = lastOutput + delta_output;

        // 使用调整前的值保存为lastOutput，避免数据丢失
        lastOutput = output;
        secondLastErr = lastErr;
        lastErr = error;

        return adjustOutput(output);
    }
}
