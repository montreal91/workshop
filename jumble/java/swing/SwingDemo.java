
import javax.swing.*;

public class SwingDemo {
  SwingDemo() {
    JFrame jfrm = new JFrame("A Simple Swing Application");

    jfrm.setSize(275, 100);
    jfrm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    JLabel jlab = new JLabel("GUI programming with Swing.");
    jfrm.add(jlab);
    jfrm.setVisible(true);
  }

  public static void main(String args[]) {
    SwingUtilities.invokeLater(new Runnable() {
      public void run() {
        new SwingDemo();
      }
    });
  }
}
