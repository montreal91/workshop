package server;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import common.Vector;

/**
 * @author montreal <br>
 *         This class deals with all pakman game logic.
 *
 */
public class PakmanGameObject {
    private Vector            size;
    private ArrayList<Vector> walls;

    private final int         WALL    = 1010;
    private final int         SIZE    = 1011;
    private final char        COMMENT = '#';

    public PakmanGameObject() {
        this.walls = new ArrayList<Vector>();
        try {
            BufferedReader br = new BufferedReader(new FileReader("pakman_field.txt"));
            String line;
            int next = 0;
            while ((line = br.readLine()) != null) {
                if (line.length() == 0 || line.charAt(0) == COMMENT) {
                    continue;
                }
                if (line.equals("walls:")) {
                    next = WALL;
                    continue;
                }
                if (line.equals("size:")) {
                    next = SIZE;
                    continue;
                }
                if (next == WALL) {
                    this.walls.add(this.GetVectorFromConfigLine(line));
                } else if (next == SIZE) {
                    this.size = this.GetVectorFromConfigLine(line);
                } else {
                    continue;
                }
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Vector GetSize() {
        return this.size;
    }

    public ArrayList<Vector> GetWalls() {
        return this.walls;
    }

    private Vector GetVectorFromConfigLine(String config_line) {
        String[] split = config_line.split(";");
        if (split.length != 2) {
            throw new IllegalArgumentException();
        }
        return new Vector(Integer.valueOf(split[0]), Integer.valueOf(split[1]));
    }
}
