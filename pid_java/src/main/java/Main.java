import pid.BasePID;
import pid.IncrementalPID;
import pid.PIDParam;
import pid.PositionalPID;

/**
 * @author deng
 * @date 2019/12/30
 */
public class Main {
    public static void main(String[] args) {
        PIDParam param = new PIDParam(5, 1, 1, 80);

        System.out.println("--------------Positional--------------");

        BasePID pid = new PositionalPID(param);
        System.out.println("current:30,output:" + pid.collectAndCalculate(30));
        System.out.println("current:50,output:" + pid.collectAndCalculate(50));
        System.out.println("current:60,output:" + pid.collectAndCalculate(60));

        System.out.println("--------------------------------------\n");


        System.out.println("--------------Incremental-------------");

        pid = new IncrementalPID(param);
        System.out.println("current:30,output:" + pid.collectAndCalculate(30));
        System.out.println("current:50,output:" + pid.collectAndCalculate(50));
        System.out.println("current:60,output:" + pid.collectAndCalculate(60));

        System.out.println("--------------------------------------");
    }
}
