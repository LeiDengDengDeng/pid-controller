package pid;

/**
 * @author deng
 * @date 2019/12/30
 */
public class PositionalPID extends BasePID {
    private double sumErr;
    private double lastErr;

    public PositionalPID(PIDParam pidParam) {
        super(pidParam);
        this.sumErr = 0;
        this.lastErr = 0;
    }

    public double collectAndCalculate(double currentVal) {
        double error = pidParam.getTargetVal() - currentVal;
        sumErr += error;

        double output = pidParam.getKP() * error + pidParam.getKI() * sumErr + pidParam.getKD() * (error - lastErr);

        lastErr = error;

        return adjustOutput(output);
    }
}
