import java.io.Serializable;
import java.text.DateFormat;
import java.text.MessageFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;

// One transport class
// for all kinds of transport
public class Transport extends Thread implements Serializable {

    // Type of this instance (bus, trolleybus, tram), route name and interval (in seconds)
    private String type = "UNKNOWN";
    private Route route = new Route("UNKNOWN");
    private int interval = 0;
    private Date createTime = null;

    public String getCreateTime() {
        DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        return MessageFormat.format(Tools.getLocalization().getProperty("transport_createtime"),
                getType(),
                dateFormat.format(createTime));
    }

    // Chance to crash (in percents)
    protected int crashChance = 20;
    // Route interval after crash will be increased for this value
    protected int intervalIncrement = 3;

    // Stop flag
    protected boolean stopFlag = false;


    // Constructor
    public Transport(String pType){
        setType(pType);
        // Set creating time
        createTime = new Date();
    }


    // Main method
    public void run(){
        // Check for data correctness
        // and if everything is ok, run thread
        if ((getType().equals("UNKNOWN")) || (getRoute().equals("UNKNOWN")) || (getInterval() <= 0)){
            setStopFlag(true);
            System.out.println(Tools.getLocalization().getProperty("transport_incorrectData") + getType() + "\".");
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
                    setInterval(getInterval() + intervalIncrement);
                }
                System.out.println(MessageFormat.format(Tools.getLocalization().getProperty("transport_crash"),
                        getType(),
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


    // Show information about this transport
    public void showInform() {
        System.out.println(MessageFormat.format(Tools.getLocalization().getProperty("transport_info"),
                getType(),
                getRoute(),
                getInterval()));
    }


    // Getters and setters
    public void setStopFlag(boolean pFlag) {
        this.stopFlag = pFlag;
    }


    public void setType(String pType){
        this.type = pType;
    }

    public String getType(){
        return type;
    }


    public void setRoute(String pRoute) {
        this.route.setRouteName(pRoute);
    }

    public String getRoute() {
        return route.getRouteName();
    }


    public void setInterval(int pInterval) {
        this.interval = pInterval;
    }

    public int getInterval() {
        return interval;
    }
}
