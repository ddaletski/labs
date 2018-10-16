import java.io.Serializable;

public class Route implements Serializable {

    private String routeName = "UNKNOWN";

    // Constructor
    public Route(String pRouteName) {
        setRouteName(pRouteName);
    }


    // Getter and setter
    public String getRouteName() {
        return routeName;
    }

    public void setRouteName(String pRouteName) {
        this.routeName = pRouteName;
    }
}