import javax.swing.*;
import javax.swing.Timer;
import java.applet.Applet;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.function.Consumer;



public class Main extends JApplet {
    MyPanel panel;

    public void init() {
        panel = new MyPanel(getParameter("str"));
        add(panel);
    }
}

class MyPanel extends JPanel implements ActionListener {
    Font font = new Font("TimesRoman", Font.BOLD, 24);

    String[] cornerBuffers;
    String drawnString;
    String fullString;
    HashMap<Integer, Character> flyingChars;
    int steps;

    double[] progress;
    int direction;

    Timer timer;
    ArrayList<Timer> timers;

    MyPanel(String str) {
        super();
        timer = new javax.swing.Timer(1, this);

        timers = new ArrayList<>();
        timers.add(new javax.swing.Timer(1, (actionEvent) -> {
            this.step(0);
        }));
        timers.add(new javax.swing.Timer(1, (actionEvent) -> {
            this.step(1);
        }));
        timers.add(new javax.swing.Timer(1, (actionEvent) -> {
            this.step(2);
        }));
        timers.add(new javax.swing.Timer(1, (actionEvent) -> {
            this.step(3);
        }));

        fullString = str;
        flyingChars = new HashMap<Integer, Character>();

        steps = 1000;
        direction = 1;
        drawnString = "";

        startTimers();
    }

    private void startTimers() {
        if(direction > 0) {
            progress = new double[]{0, 0, 0, 0};
            cornerBuffers = splitString(fullString, 4);
        } else {
            progress = new double[]{1.0, 1.0, 1.0, 1.0};
        }
        for(int i = 0; i < 4; ++i) {
            timers.get(i).setInitialDelay(i * steps / 10);
            timers.get(i).setDelay(1);
            timers.get(i).start();
        }
        timer.start();
    }

    private String[] splitString(String s, int n) {
        int subsize = s.length() / n;
        String[] substrings = new String[n];
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                substrings[i] = s.substring(0, (i + 1) * subsize);
            } else if (i == n - 1) {
                substrings[i] = s.substring(i * subsize);
            } else {
                substrings[i] = s.substring(i * subsize, (i + 1) * subsize);
            }
        }
        return substrings;
    }


    private void eachCorner(Consumer<Integer> f) {
        for (int i = 0; i < 4; ++i) {
            f.accept(i);
        }
    }


    public void step(int i) {
        if (direction > 0) {
            if (!flyingChars.containsKey(i) && cornerBuffers[i].length() > 0) {
                flyingChars.put(i, cornerBuffers[i].charAt(0));
                cornerBuffers[i] = cornerBuffers[i].substring(1);
            }

            if (!flyingChars.containsKey(i)) {
                return;
            }

            progress[i] += 1.0 / steps;

            if (progress[i] >= 1.0) {
                drawnString += flyingChars.get(i);
                flyingChars.remove(i);
                progress[i] = 0;
                timers.get(i).stop();
                timers.get(i).start();
            }
        } else {
            if (!flyingChars.containsKey(i) && drawnString.length() > 0) {
                flyingChars.put(i, drawnString.charAt(0));
                drawnString = drawnString.substring(1);
            }

            if (!flyingChars.containsKey(i)) {
                return;
            }

            progress[i] -= 1.0 / steps;

            if (progress[i] <= 0) {
                cornerBuffers[i] += flyingChars.get(i);
                flyingChars.remove(i);
                progress[i] = 1.0;
                timers.get(i).stop();
                timers.get(i).start();
            }
        }
    }

    public void step () {
        if(direction > 0 && drawnString.length() == fullString.length()
        || direction < 0 && drawnString.length() == 0 && flyingChars.isEmpty()) {

            direction = -direction;
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            startTimers();
        }
    }

    public void paint(Graphics g) {
        g.clearRect(0, 0, getWidth(), getHeight());
        int hcenter = getWidth() / 2;
        int vcenter = getHeight() / 2;

        g.setFont(font);
        int startX = hcenter - g.getFontMetrics().stringWidth(fullString) / 2;
        int endX = startX + g.getFontMetrics().stringWidth(fullString);

        int stringWidth = g.getFontMetrics().stringWidth(drawnString);
        if (direction > 0) {
            g.drawString(drawnString, startX, vcenter);
        } else {
            g.drawString(drawnString, endX - stringWidth, vcenter);
        }

        eachCorner(i -> {
            if (flyingChars.containsKey(i)) {
                int symWidth = g.getFontMetrics().charWidth(flyingChars.get(i));
                int symHeight = g.getFontMetrics().getHeight();

                int symTargetY = vcenter;
                int symTargetX;
                symTargetY = vcenter;
                if(direction > 0) {
                    symTargetX = startX + stringWidth + symWidth * i;
                } else {
                    symTargetX = endX - stringWidth + symWidth * i;
                }
                int symStartX = new int[]{0, getWidth(), 0, getWidth()}[i];
                int symStartY = new int[]{0, 0, getHeight(), getHeight()}[i];


                int xpos = (int) (progress[i] * (symTargetX - symStartX));
                int ypos = (int) (progress[i] * (symTargetY - symStartY));

                if (i % 2 == 1) {
                    xpos += getWidth();
                }

                if (i >= 2) {
                    ypos += getHeight();
                }

                g.drawString("" + flyingChars.get(i), xpos, ypos);
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        step();
        repaint();
    }
}



/*
<applet code="Main.class" width=100 height=50>
<param name="str" value="lolka">
</applet>
 */