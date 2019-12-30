package pid;

import lombok.Getter;

/**
 * @author deng
 * @date 2019/12/30
 */
@Getter
public class PIDParam {
    private double kP;
    private double kI;
    private double kD;
    private double targetVal;
    private double rangeMin;
    private double rangeMax;
    private boolean useRange;

    public PIDParam(double kP, double kI, double kD, double targetVal) {
        this.kP = kP;
        this.kI = kI;
        this.kD = kD;
        this.targetVal = targetVal;
        this.useRange = false;
    }

    public PIDParam(double kP, double kI, double kD, double targetVal, double rangeMin, double rangeMax) {
        if (rangeMin > rangeMax) {
            throw new RuntimeException("illegal range");
        }

        this.kP = kP;
        this.kI = kI;
        this.kD = kD;
        this.targetVal = targetVal;
        this.rangeMin = rangeMin;
        this.rangeMax = rangeMax;
        this.useRange = true;
    }
}
