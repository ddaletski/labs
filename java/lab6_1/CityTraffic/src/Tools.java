import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.text.MessageFormat;
import java.util.Properties;
import java.util.ResourceBundle;
import java.util.Scanner;

// Tools class (connector)
// includes static methods to work with Transports
public class Tools {

    // Localization
    private static Properties localization;

    public static Properties getLocalization() {
        return localization;
    }

    public static void setLocalization(Properties localization) {
        Tools.localization = localization;
    }

    private static Scanner scanner = new Scanner(System.in);


    // Try to serialize pTransport instance
    public static void serialize(Transport pTransport){
        try {
            // streams (save to executable folder)
            FileOutputStream fileOutputStream = new FileOutputStream(pTransport.getType() + ".file");
            ObjectOutputStream objectOutputStream = new ObjectOutputStream(fileOutputStream);
            // actually serializing
            objectOutputStream.writeObject(pTransport);
            // close streams
            objectOutputStream.flush();
            objectOutputStream.close();
            fileOutputStream.close();
        }
        catch (Exception ex){
            System.out.println(MessageFormat.format(Tools.getLocalization().getProperty("tools_error"),
                    pTransport.getType(),
                    ex.getMessage()));
        }
    }


    // Try to deserialize pTransport instance
    // returns true if successful or false if it is not
    public static boolean deserialize(Transport pTransport) {
        try {
            // streams
            FileInputStream fileInputStream = new FileInputStream(pTransport.getType() + ".file");
            ObjectInputStream objectInputStream = new ObjectInputStream (fileInputStream);
            // actually deserializing
            Transport temp = (Transport) objectInputStream.readObject();
            // transfer data from deserialized class to existing
            pTransport.setType(temp.getType());
            pTransport.setRoute(temp.getRoute());
            pTransport.setInterval(temp.getInterval());
            // close streams
            fileInputStream.close();
            objectInputStream.close();

            return true;
        }
        catch (Exception ex) {
            System.out.println(MessageFormat.format(Tools.getLocalization().getProperty("tools_error2"),
                    pTransport.getType(),
                    ex.getMessage()));
            return false;
        }
    }


    // Input route name and interval
    public static void inputData(Transport pTransport) {
        String tempRoute = "";
        int tempInterval = 0;

        // Try to input route name and check correctness
        do{
            System.out.print(Tools.getLocalization().getProperty("tools_inputroute") + pTransport.getType() + "\": ");
            tempRoute = scanner.nextLine();

            if (tempRoute.length() < 1){
                System.out.println(Tools.getLocalization().getProperty("tools_errinputroute"));
            }
        }
        while (tempRoute.length() < 1);
        // Set new route name
        pTransport.setRoute(tempRoute);

        // Try to input interval value and check correctness
        do{
            System.out.print(MessageFormat.format(Tools.getLocalization().getProperty("tools_inputinterval"),
                    pTransport.getType()));
            try{
                tempInterval = Integer.valueOf(scanner.nextLine());

                // interval can't be equal 0
                if (tempInterval <= 0) throw new Exception();
            }
            catch (Exception ex){
                System.out.println(Tools.getLocalization().getProperty("tools_errinputinterval"));
                tempInterval = 0;
            }
        }
        while (tempInterval == 0);

        // Set new interval value
        pTransport.setInterval(tempInterval);
    }


    // Show info for this Transport instance
    public static void showInfo(Transport pTransport){
        pTransport.showInform();
    }
}