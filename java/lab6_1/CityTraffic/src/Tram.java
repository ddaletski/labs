import java.text.MessageFormat;
import java.util.Random;

public class Tram extends Transport {

    public Tram(String pType) {
        super(pType);
    }


    // Main method (overrided super method)
    public void run(){
        // Check for data correctness
        // and if everything is ok, run thread
        if ((getType().equals("UNKNOWN")) || (getRoute().equals("UNKNOWN")) || (getInterval() <= 0)){
            setStopFlag(true);
            System.out.println(Tools.getLocalization().getProperty("tram_incorrectData"));
        }
        else {
            setStopFlag(false);
        }

        while (!stopFlag) {
            System.out.println(getType() + Tools.getLocalization().getProperty("transport_start") + getRoute() + "\".");

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
                    message = Tools.getLocalization().getProperty("transport_reserve") + getType() + ".";
                }
                else{
                    message = MessageFormat.format(Tools.getLocalization().getProperty("transport_delay"),
                            intervalIncrement);
                }
                System.out.println(MessageFormat.format(Tools.getLocalization().getProperty("tram_crash"),
                        getRoute(),
                        message));
            }
            else{
                // if there are no crashes transport finishes moving the route
                System.out.println(getType() + Tools.getLocalization().getProperty("transport_end") + getRoute() + "\".");
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
