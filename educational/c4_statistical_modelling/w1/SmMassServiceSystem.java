
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import java.awt.Dimension;
import java.awt.GridLayout;
import javax.swing.JButton;
import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;

public class SmMassServiceSystem implements Runnable {
    private final String WINDOW_CAPTION = "Mass Service System";
    
    /**
     * Time step in milliseconds
     */
    private final int TIME_STEP = 250;
    
    private Timer inner_timer;
    private long ticks_since_start;
    private long ticks_since_last_request;
    private long ticks_until_next_request;
    private long no_requests_ticks;
    private long total_requests;
    private long lost_requests;
    
    private long[] channels_list;
    
    private GridLayout main_frame_layout;
    private JFrame main_frame;
    private JSpinner lambda;
    private JSpinner channels;
    
    /**
     * Time spent by channel for servicing the request in seconds.
     */
    private JSpinner service_time;
    
    private JButton start_system_button;
    private JButton stop_system_button;
    private JLabel requests_label;
    private JLabel ticks_since_start_label;
    private JLabel ticks_since_last_request_label;
    private JLabel ticks_until_next_request_label;
    private JLabel available_channels_label;
    private JLabel no_request_probability_label;
    private JLabel lost_request_probability_label;
    
    public SmMassServiceSystem() {
        this.inner_timer = new Timer(
            TIME_STEP,
            e -> processSystemTick()
        );
        this.ticks_since_start = 0;
        this.ticks_since_last_request = 0;
        this.ticks_until_next_request = 1;
        this.no_requests_ticks = 0;
        
        this.total_requests = 0;
        this.lost_requests = 0;
        
        Double l_min = new Double(0.1);
        Double l_max = new Double(50.0);
        Double l_step = new Double(0.1);
        SpinnerNumberModel lambda_model = new SpinnerNumberModel(l_min, l_min, l_max, l_step);
        this.lambda = new JSpinner(lambda_model);
        
        Integer ch_min = new Integer(1);
        Integer ch_max = new Integer(100);
        Integer ch_step = new Integer(1);
        SpinnerNumberModel channels_model = new SpinnerNumberModel(ch_min, ch_min, ch_max, ch_step);
        this.channels = new JSpinner(channels_model);
        
        Long t_min = new Long(1);
        Long t_max = new Long(100);
        Long t_step = new Long(1);
        SpinnerNumberModel time_model = new SpinnerNumberModel(t_min, t_min, t_max, t_step);
        this.service_time = new JSpinner(time_model);

        
        this.main_frame_layout = new GridLayout(0,2);
        this.main_frame = new JFrame(this.WINDOW_CAPTION);
        this.main_frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);

        Dimension main_frame_dimension = new Dimension(400, 50);
        this.main_frame.setMinimumSize(main_frame_dimension);
        this.main_frame.setLayout(this.main_frame_layout); 
        
        this.main_frame.add(new JLabel("Lambda"));
        this.main_frame.add(lambda);
        
        this.main_frame.add(new JLabel("Channels"));
        this.main_frame.add(this.channels);
        
        this.main_frame.add(new JLabel("Service Time"));
        this.main_frame.add(this.service_time);
        
        this.start_system_button = new JButton("Start System");
        this.start_system_button.addActionListener(
            e -> startSystem()
        );
        this.main_frame.add(this.start_system_button);
        
        this.stop_system_button = new JButton("Stop System");
        this.stop_system_button.addActionListener(
            e -> stopSystem()
        );
        this.stop_system_button.setEnabled(false);
        this.main_frame.add(this.stop_system_button);
        
        this.main_frame.add(new JLabel("Requests"));
        this.requests_label = new JLabel();
        this.main_frame.add(this.requests_label);
        
        this.main_frame.add(new JLabel("Time since start"));
        this.ticks_since_start_label = new JLabel();
        this.main_frame.add(this.ticks_since_start_label);
        
        this.main_frame.add(new JLabel("Time since last request"));
        this.ticks_since_last_request_label = new JLabel();
        this.main_frame.add(this.ticks_since_last_request_label);
        
        this.main_frame.add(new JLabel("Ticks until next request"));
        this.ticks_until_next_request_label = new JLabel();
        this.main_frame.add(this.ticks_until_next_request_label);
        
        this.main_frame.add(new JLabel("Available channels"));
        this.available_channels_label = new JLabel();
        this.main_frame.add(this.available_channels_label);
        
        this.main_frame.add(new JLabel("No requests probability"));
        this.no_request_probability_label = new JLabel();
        this.main_frame.add(this.no_request_probability_label);
        
        this.main_frame.add(new JLabel("Lost request probability"));
        this.lost_request_probability_label = new JLabel();
        this.main_frame.add(this.lost_request_probability_label);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new SmMassServiceSystem());
    }

    public void run() {
        this.main_frame.pack();
        this.main_frame.setVisible(true);
    }

    private void printData() {
        double val = (double)this.lambda.getValue();
        this.requests_label.setText(Double.toString(val));
        this.ticks_since_start_label.setText(
            Long.toString(this.ticks_since_start)
        );
        this.ticks_since_last_request_label.setText(
            Long.toString(this.ticks_since_last_request)
        );
        this.ticks_until_next_request_label.setText(
            Long.toString(this.ticks_until_next_request)
        );
        double no_request_probability = (double)this.no_requests_ticks / this.ticks_since_start;
        this.no_request_probability_label.setText(
            Double.toString(no_request_probability)
        );
        
        double lost_request_probability = 0;
        if (this.total_requests > 0) {
            lost_request_probability = (double)this.lost_requests / this.total_requests;
        }
        
        this.lost_request_probability_label.setText(
            Double.toString(lost_request_probability)
        );
        
        int avch = this.getNumberOfAvailableChannels();
        String text = Integer.toString(avch) + " / " + Integer.toString(this.channels_list.length);
        this.available_channels_label.setText(text);
    }
    
    private void processSystemTick() {
        for (int i = 0; i < this.channels_list.length; i++) {
            if (this.channels_list[i] > 0) {
                this.channels_list[i]--;
            }
        }
        int max_channels = (int)this.channels.getValue();
        if (this.getNumberOfAvailableChannels() == max_channels) {
            this.no_requests_ticks++;
        }
        if (this.isNewRequestCreated()) {
            this.total_requests++;
            if (this.getNumberOfAvailableChannels() == 0) {
                this.lost_requests++;
            }
            for (int i = 0; i < this.channels_list.length; i++) {
                if (this.channels_list[i] == 0) {
                    long st = (long)this.service_time.getValue();
                    this.channels_list[i] = new Long(st);
                    break;
                }
            }
            this.ticks_since_last_request = 0;
            this.ticks_until_next_request = this.getRandomInt();
            this.ticks_since_start++;
            this.printData();
            return;
        }
        this.ticks_since_start++;
        this.ticks_since_last_request++;
        this.printData();
    }

    private void startSystem() {
        this.start_system_button.setEnabled(false);
        this.stop_system_button.setEnabled(true);
        this.setInputEnabled(false);
        
        int num_channels = (int)this.channels.getValue();
        this.channels_list = new long[num_channels];
        this.ticks_until_next_request = this.getRandomInt();
        this.inner_timer.start();
    }

    private void stopSystem() {
        this.inner_timer.stop();
        this.requests_label.setText("");
        this.start_system_button.setEnabled(true);
        this.stop_system_button.setEnabled(false);
        this.setInputEnabled(true);
        this.ticks_since_start = 0;
        this.ticks_since_last_request = 0;
        this.ticks_until_next_request = this.getRandomInt();
        this.no_requests_ticks = 0;
        this.total_requests = 0;
        this.lost_requests = 0;
    }
    
    private void setInputEnabled(boolean enabled) {
        this.lambda.setEnabled(enabled);
        this.channels.setEnabled(enabled);
        this.service_time.setEnabled(enabled);
    }
    
    private boolean isNewRequestCreated() {
        boolean cond0 = this.ticks_until_next_request == 0;
        boolean cond1 = this.ticks_since_last_request == this.ticks_until_next_request;
        boolean cond2 = this.ticks_since_start > 0;
        return cond0 || (cond1 && cond2);
    }
    
    private long getRandomInt() {
        double lbd = (double)this.lambda.getValue();
        return SmDiscrete.getPoissonDistribution(lbd);
    }
    
    private int getNumberOfAvailableChannels() {
        int res = 0;
        for (long ch : this.channels_list) {
            if (ch == 0) {
                res++;
            }
        }
        return res;
    }
}
