import java.text.MessageFormat;
import java.util.Random;

public class Bus extends Transport {

    public Bus(String pType) {
        super(pType);
    }


    // Main method (overrided super method)
    public void run(){
        // Check for data correctness
        // and if everything is ok, run thread
        if ((getType().equals("UNKNOWN")) || (getRoute().equals("UNKNOWN")) || (getInterval() <= 0)){
            setStopFlag(true);
            System.out.println("Некорректно заполнена информация для Автобуса.");
        }
        else {
            setStopFlag(false);
        }

        while (!stopFlag) {
            System.out.println(getType() + " начал движение по маршруту \"" + getRoute() + "\".");

            // simulate route moving
            try {
                Thread.sleep(getInterval() * 1000);
            }
            catch (InterruptedException e) {
            }

            // generate a crash with some chance
            if (new Random().nextInt(101) <= crashChance){
                String message;
                // Randomly choose between calling reserve transport and increasing interval
                if (new Random().nextInt(2) == 0){
                    message = "На маршрут выйдет резервный " + getType() + ".";
                }
                else{
                    message = "Интервал движения увеличен на " + intervalIncrement + " секунд.";
                    setInterval(getInterval() + intervalIncrement);
                }
                System.out.println(MessageFormat.format("С Автобусом на маршруте \"{0}\" произошла поломка.\n" +
                                "{1}",
                        getRoute(),
                        message));
            }
            else{
                // if there are no crashes transport finishes moving the route
                System.out.println(getType() + " закончил движение по маршруту \"" + getRoute() + "\".");
            }

            // Wait 1 second
            try {
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {
            }
        }
    }
}