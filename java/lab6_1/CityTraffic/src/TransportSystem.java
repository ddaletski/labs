import java.text.DateFormat;
import java.text.MessageFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class TransportSystem {

    private static Date createTime = null;

    public static String getCreateTime() {
        DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        return MessageFormat.format(Tools.getLocalization().getProperty("transystem_createtime"),
                dateFormat.format(createTime));
    }

    private static Scanner scanner = new Scanner(System.in);

    // Initialize Transport threads
    private static Bus bus = new Bus(Tools.getLocalization().getProperty("transystem_bus"));
    private static Trolleybus trolleybus = new Trolleybus(Tools.getLocalization().getProperty("transystem_trolleybus"));
    private static Tram tram = new Tram(Tools.getLocalization().getProperty("transystem_tram"));

    public TransportSystem() {
        createTime = new Date();
    }

    // Main simulation method
    public static void startSystem() {
        // Say Hello
        System.out.println(Tools.getLocalization().getProperty("transystem_hello"));

        // Try to read serialized files
        // or input data into them if they aren't available
        if (!Tools.deserialize(bus)){
            Tools.inputData(bus);
        }
        if (!Tools.deserialize(trolleybus)){
            Tools.inputData(trolleybus);
        }
        if (!Tools.deserialize(tram)){
            Tools.inputData(tram);
        }

        // Show classes create time
        System.out.println(Tools.getLocalization().getProperty("transystem_showtime"));
        System.out.println(getCreateTime());
        System.out.println(bus.getCreateTime());
        System.out.println(trolleybus.getCreateTime());
        System.out.println(tram.getCreateTime());

        // Show transport information
        showInfo();

        // Start simulation (run Transport threads)
        startSimulation();

        // Handling user commands:
        //      1 - show information about transport
        //      2 - input data for transport
        //      3 - serialize classes and close application
        String temp = "";
        while (true){
            temp = scanner.nextLine();

            switch (temp){
                case "1":
                    showInfo();
                    break;
                case "2":
                    inputData();
                    break;
                case "3":
                    exitApp();
                    break;
            }
        }
    }


    // Start simulation (run Transport threads)
    private static void startSimulation(){
        System.out.println(Tools.getLocalization().getProperty("transystem_start"));
        bus.start();
        trolleybus.start();
        tram.start();
    }


    // Show transport information
    private static void showInfo() {
        System.out.println(Tools.getLocalization().getProperty("transystem_transparams"));
        Tools.showInfo(bus);
        Tools.showInfo(trolleybus);
        Tools.showInfo(tram);
        System.out.println("\n");
    }


    // Input transport data
    private static void inputData() {
        // Stop transport
        stopTransport();

        // recreate tansport (reset threads)
        bus = new Bus("Автобус");
        trolleybus = new Trolleybus("Троллейбус");
        tram = new Tram("Трамвай");

        // Start input
        System.out.println("\nВвод параметров транспорта:");
        Tools.inputData(bus);
        Tools.inputData(trolleybus);
        Tools.inputData(tram);


        startSimulation();
    }


    // Serialize classes and close application
    private static void exitApp() {
        // Stop transport
        stopTransport();
        // Serialize classes
        System.out.println(Tools.getLocalization().getProperty("transystem_serialize"));
        Tools.serialize(bus);
        Tools.serialize(trolleybus);
        Tools.serialize(tram);
        System.out.println(Tools.getLocalization().getProperty("transystem_serializesuccess"));
        System.out.println(Tools.getLocalization().getProperty("transystem_end"));
        // Closing application
        System.exit(0);
    }


    // Stop transport
    private static void stopTransport() {
        // Stop threads
        System.out.println(Tools.getLocalization().getProperty("transystem_wait"));
        bus.setStopFlag(true);
        trolleybus.setStopFlag(true);
        tram.setStopFlag(true);

        // Wait for stop
        try {
            bus.join();
            trolleybus.join();
            tram.join();
        }
        catch (Exception ex){
            ex.printStackTrace();
        }
    }
}
