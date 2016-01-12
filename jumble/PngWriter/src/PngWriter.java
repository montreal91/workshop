
import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.*;
import java.io.File;
import java.io.IOException;
import java.util.TreeSet;

public class PngWriter extends Component implements ActionListener {
    String descs[] = {
        "Original",
        "Convolve : LowPass",
        "Convolve : Sharpen",
        "LookupOp",
    };

    int opIndex;
    private BufferedImage bi, biFiltered;
    int w, h;

    // Sharpening filter kernel
    public static final float[] SHARPEN3x3 = {
        0.0f, -1.0f, 0.0f,
        -1.0f, 5.0f, -1.0f,
        0.0f, -1.0f, 0.0f
    };

    // Low-pass filter kernel
    public static final float[] BLUR3x3 = {
        0.1f, 0.1f, 0.1f,
        0.1f, 0.2f, 0.1f,
        0.1f, 0.1f, 0.1f
    };

    public PngWriter() {
        try {
            bi = ImageIO.read( new File( "bld.jpg" ) );
            w = bi.getWidth( null );
            h = bi.getHeight( null );

            if ( bi.getType() != BufferedImage.TYPE_INT_RGB ) {
                BufferedImage bi2   = new BufferedImage( w, h, BufferedImage.TYPE_INT_RGB );
                Graphics big        = bi2.getGraphics();
                big.drawImage( bi, 0, 0, null );
                biFiltered          = bi = bi2;
            }
        } catch ( IOException e ) {
            System.out.println( "Image could not be read" );
            System.exit( 1 );
        }
    }

    public Dimension getPreferredSize() {
        return new Dimension( w, h );
    }

    String[] getDescriptions() {
        return descs;
    }

    void setOpIndex( int i ) {
        opIndex = i;
    }

    public void paint( Graphics g ) {
        filterImage();
        g.drawImage( biFiltered, 0, 0, null );
    }

    int lastOp;
    public void filterImage() {
        BufferedImageOp op = null;

        if ( opIndex == lastOp ) {
            return;
        }

        lastOp = opIndex;
        switch ( opIndex ) {
            case 0:
                biFiltered = bi;
                return;
            case 1: // Low pass filter
            case 2: // sharpen
                float[] data = ( opIndex == 1 ) ? BLUR3x3 : SHARPEN3x3;
                op = new ConvolveOp( new Kernel( 3, 3, data ), ConvolveOp.EDGE_NO_OP, null );
                break;
            case 3: // Lookup
                byte lut[] = new byte[256];
                for ( int j=0; j<256; j++ ) {
                    lut[j] = ( byte )( 256 - j );
                }
                ByteLookupTable blut = new ByteLookupTable( 0, lut );
                op = new LookupOp( blut, null );
                break;

        }

        biFiltered = new BufferedImage( w, h, BufferedImage.TYPE_INT_RGB );
        op.filter( bi, biFiltered );
    }

    public String[] getFormats() {
        String[] formats = ImageIO.getWriterFormatNames();
        TreeSet<String> formatSet = new TreeSet<String>();

        for ( String s : formats ) {
            formatSet.add( s.toLowerCase() );
        }
        return formatSet.toArray( new String[0] );
    }

    public void actionPerformed( ActionEvent e ) {
        JComboBox cb = (JComboBox)e.getSource();
        if ( cb.getActionCommand().equals( "SetFilter" ) ) {
            setOpIndex( cb.getSelectedIndex() );
            repaint();
        } else if ( cb.getActionCommand().equals( "Formats" ) ) {
            String format = (String)cb.getSelectedItem();
            File saveFile = new File( "savedimage." + format );
            JFileChooser chooser = new JFileChooser();
            chooser.setSelectedFile( saveFile );

            int rval = chooser.showSaveDialog( cb );
            if ( rval == JFileChooser.APPROVE_OPTION ) {
                saveFile = chooser.getSelectedFile();

                try {
                    ImageIO.write( biFiltered, format, saveFile );
                } catch ( IOException ex) {}
            }
        }
    }

    public static void main( String s[] ) {
        JFrame f = new JFrame( "Save Image Sample" );
        f.addWindowListener(
            new WindowAdapter() {
                public void windowClosing( WindowEvent e ) {
                    System.exit( 0 );
                }
            }
        );

        PngWriter si = new PngWriter();
        f.add( "Center", si );
        JComboBox choices = new JComboBox(si.getDescriptions());
        choices.setActionCommand("SetFilter");
        choices.addActionListener(si);
        JComboBox formats = new JComboBox(si.getFormats());
        formats.setActionCommand("Formats");
        formats.addActionListener(si);
        JPanel panel = new JPanel();
        panel.add(choices);
        panel.add(new JLabel("Save As"));
        panel.add(formats);
        f.add("South", panel);
        f.pack();
        f.setVisible(true);
    }
}
