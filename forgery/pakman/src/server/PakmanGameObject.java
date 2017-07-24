package server;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import common.Directions;
import common.Vector;

/**
 * @author montreal <br>
 *         This class deals with all pakman game logic.
 *
 */
public class PakmanGameObject {
    private final char        COMMENT  = '#';

    /**
     * Time in server ticks
     */
    private int               movement_time;

    private Directions        pakman_direction;

    private Vector            pakman_position;
    private int               pakman_speed;
    private final int         POSITION = 1000;

    private Vector            size;
    private final int         SIZE     = 1011;
    private final int         SPEED    = 1111;
    private final int         WALL     = 1010;
    private ArrayList<Vector> walls;

    public PakmanGameObject() {
        this.walls = new ArrayList<Vector>();
        this.pakman_direction = Directions.NONE;
        try {
            BufferedReader br = new BufferedReader(new FileReader("pakman_field.txt"));
            String line;
            int next = 0;
            while ((line = br.readLine()) != null) {
                if (line.length() == 0 || line.charAt(0) == this.COMMENT) {
                    continue;
                }
                if (line.equals("walls:")) {
                    next = this.WALL;
                    continue;
                }
                if (line.equals("size:")) {
                    next = this.SIZE;
                    continue;
                }
                if (line.equals("speed:")) {
                    next = this.SPEED;
                    continue;
                }
                if (line.equals("position:")) {
                    next = this.POSITION;
                    continue;
                }

                if (next == this.WALL) {
                    this.walls.add(PakmanGameObject.GetVectorFromConfigLine(line));
                } else if (next == this.SIZE) {
                    this.size = PakmanGameObject.GetVectorFromConfigLine(line);
                } else if (next == this.SPEED) {
                    this.pakman_speed = PakmanGameObject.GetIntFromConfigLine(line);
                } else if (next == this.POSITION) {
                    this.pakman_position = PakmanGameObject.GetVectorFromConfigLine(line);
                } else {
                    continue;
                }
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Directions GetPakmanDirection() {
        return this.pakman_direction;
    }

    public Vector GetPakmanPosition() {
        return this.pakman_position;
    }

    public Vector GetSize() {
        return this.size;
    }

    public ArrayList<Vector> GetWalls() {
        return this.walls;
    }

    public void SetPakmanDirection(Directions direction) {
        if (this.pakman_direction != direction) {
            this.pakman_direction = direction;
            this.movement_time = 0;
        }
    }

    public void StopPakman() {
        this.pakman_direction = Directions.NONE;
        this.movement_time = 0;
    }

    public void Update() {
        if (this.movement_time >= this.pakman_speed) {
            Vector next_pos = this.GetNextPakmanPosition();
            if (!this.IsPointWall(next_pos)) {
                this.pakman_position = next_pos;
                this.movement_time = 0;
            }

        }
        this.AddMovementTick();
    }

    private void AddMovementTick() {
        if (this.pakman_direction != Directions.NONE) {
            this.movement_time++;
        }
    }

    private Vector GetNextPakmanPosition() {
        Vector res;
        if (this.pakman_direction == Directions.UP) {
            res = new Vector(this.pakman_position.GetX(), this.pakman_position.GetY() - 1);
        } else if (this.pakman_direction == Directions.DOWN) {
            res = new Vector(this.pakman_position.GetX(), this.pakman_position.GetY() + 1);
        } else if (this.pakman_direction == Directions.RIGHT) {
            res = new Vector(this.pakman_position.GetX() + 1, this.pakman_position.GetY());
        } else if (this.pakman_direction == Directions.LEFT) {
            res = new Vector(this.pakman_position.GetX() - 1, this.pakman_position.GetY());
        } else {
            res = this.pakman_position;
        }
        return res;
    }

    private boolean IsPointWall(Vector point) {
        for (Vector wall : this.walls) {
            if (point.GetX() == wall.GetX() && point.GetY() == wall.GetY()) {
                return true;
            }
        }
        return false;
    }

    private final static String SEPARATOR = ";";

    private static int GetIntFromConfigLine(String config_line) {
        return Integer.valueOf(config_line).intValue();
    }

    private static Vector GetVectorFromConfigLine(String config_line) {
        String[] split = config_line.split(PakmanGameObject.SEPARATOR);
        if (split.length != 2) {
            throw new IllegalArgumentException("Syntax error in config file");
        }
        return new Vector(Integer.valueOf(split[0]).intValue(), Integer.valueOf(split[1]).intValue());
    }
}
