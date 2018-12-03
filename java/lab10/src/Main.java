import javax.swing.*;
import javax.swing.Timer;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.function.Consumer;



public class Main extends JApplet {
    MyPanel panel;

    public void init() {
        panel = new MyPanel(getParameter("text"));
        add(panel);
    }
}

class MyPanel extends JPanel implements ActionListener {
    Font font = new Font("TimesRoman", Font.BOLD, 24);

    StringBuffer cornersBuffer;
    StringBuffer drawnString;

    String fullString;
    HashMap<Integer, String> flyingStrings;
    int steps;

    double[] progress;
    int direction;

    Timer timer;
    ArrayList<Timer> timers;

    MyPanel(String str) {
        super();
        timer = new javax.swing.Timer(1, this);
        timer.setActionCommand("-1");

        timers = new ArrayList<>();
        for(int i = 0; i < 4; ++i) {
            Timer t = new javax.swing.Timer(1, this);
            t.setActionCommand("" + i);
            timers.add(t);
        }

        fullString = str;
        flyingStrings = new HashMap<Integer, String>();

        steps = 1000;
        direction = 1;
        startTimers();
    }

    private void startTimers() {
        if(direction > 0) {
            drawnString = new StringBuffer();
            cornersBuffer = new StringBuffer(fullString);
            progress = new double[]{0.3, 0.2, 0.1, 0.0};
        } else {
            drawnString = new StringBuffer(fullString);
            cornersBuffer = new StringBuffer();
            progress = new double[]{0.7, 0.8, 0.9, 1.0};
        }
        timer.start();
        for(int i = 0; i < 4; ++i) {
            timers.get(i).restart();
        }
    }


    private void eachCorner(Consumer<Integer> f) {
        for (int i = 0; i < 4; ++i) {
            f.accept(i);
        }
    }

    private int charWithSpacesLen(StringBuffer s) {
        int i;
        for(i = 1; i < s.length() && s.charAt(i) == ' '; ++i) {}
        return i;
    }


    public void step(int i) {
        if (direction > 0) {
            if (!flyingStrings.containsKey(i)) {
                if (cornersBuffer.length() > 0) {
                    int substrSize = charWithSpacesLen(cornersBuffer);
                    flyingStrings.put(i, cornersBuffer.substring(0, substrSize));
                    cornersBuffer = cornersBuffer.delete(0, substrSize);
                } else {
                    timers.get(i).stop();
                    return;
                }
            }
            progress[i] += 1.0 / steps;

            if (progress[i] >= 1.0) {
                drawnString.append(flyingStrings.get(i));
                flyingStrings.remove(i);
                progress[i] = 0;
            }
        } else {
            if (!flyingStrings.containsKey(i)) {
                if (drawnString.length() > 0) {
                    int substrSize = charWithSpacesLen(drawnString);
                    flyingStrings.put(i, drawnString.substring(0, substrSize));
                    drawnString = drawnString.delete(0, substrSize);
                } else {
                    timers.get(i).stop();
                    return;
                }
            }

            progress[i] -= 1.0 / steps;

            if (progress[i] <= 0) {
                flyingStrings.remove(i);
                progress[i] = 1.0;
            }
        }
    }

    public void step () {
        if(direction > 0 && drawnString.length() == fullString.length()
        || direction < 0 && drawnString.length() == 0 && flyingStrings.isEmpty()) {

            for(Timer t : timers) {
                t.stop();
            }
            timer.stop();
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

        int stringWidth = g.getFontMetrics().stringWidth(drawnString.toString());
        if (direction > 0) {
            g.drawString(drawnString.toString(), startX, vcenter);
        } else {
            g.drawString(drawnString.toString(), endX - stringWidth, vcenter);
        }

        eachCorner(i -> {
            if (flyingStrings.containsKey(i)) {
                int symWidth = g.getFontMetrics().charWidth(flyingStrings.get(i).charAt(0));
                int symHeight = g.getFontMetrics().getHeight();

                int symTargetY = vcenter;
                int symTargetX;
                symTargetY = vcenter;
                if(direction > 0) {
                    symTargetX = startX + stringWidth + symWidth * i / 2;
                } else {
                    symTargetX = endX - stringWidth - symWidth * (4-i) / 2;
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

                g.drawString("" + flyingStrings.get(i), xpos, ypos);
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        int command = Integer.parseInt(actionEvent.getActionCommand());

        if (command < 0) {
            step();
            repaint();
        } else {
            step(command);
        }
    }
}



/*
<applet code="Main.class" width=640 height=480>
<param name="text" value="Some text written by hands">
</applet>
 */