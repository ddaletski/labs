import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Properties;

// Main class
// Launches application and handles user commands
public class Main {

    // Main function
    // starts when the application runs
    public static void main(String [] args){
        // Localization variables
        String language;
        String country;

        // Check in-parameters and set parameters for locale or default locale parameters
        if (args.length != 2) {
            language = new String("ru");
            country = new String("RU");
        }
        else {
            language = new String(args[0]);
            country = new String(args[1]);
        }

        Properties props = null;

        // Set language from cmd params
        try {
            // Default language (no cmd params)
            InputStream utf8in = ClassLoader.getSystemResourceAsStream("localization/LocalizationBundle.properties");
            switch (language) {
                case "ru":
                    utf8in = ClassLoader.getSystemResourceAsStream("localization/LocalizationBundle_ru_RU.properties");
                    break;
                case "by":
                    utf8in = ClassLoader.getSystemResourceAsStream("localization/LocalizationBundle_by_BY.properties");
                    break;
                case "en":
                    utf8in = ClassLoader.getSystemResourceAsStream("localization/LocalizationBundle_en_GB.properties");
                    break;
            }
            Reader reader = new InputStreamReader(utf8in, "UTF-8");
            props = new Properties();
            props.load(reader);
        }
        catch (Exception ex) {

        }

        // Set localization to the Tools class
        Tools.setLocalization(props);

        TransportSystem system = new TransportSystem();
        system.startSystem();
    }
}
