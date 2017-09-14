
class Pair implements Comparable<Pair> {
    private String className;
    private long time;

    public Pair(String className, long time) {
        this.className = className;
        this.time = time;
    }

    public String getClassName() {
        return this.className;
    }

    public long getTime() {
        return this.time;
    }

    public int compareTo(Pair p) {
        if (this.time != p.time) {
            return new Long(this.time).compareTo(new Long(p.time));
        } else {
            return p.className.compareTo(this.className);
        }
    }

    public String toString() {
        return this.className + " " + this.time;
    }
}
