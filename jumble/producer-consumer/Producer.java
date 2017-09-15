package foor;

class Producer extends Thread {
    private CubbyHole cubbyhole;
    private int number;

    public Producer(CubbyHole c, int number) {
        this.cubbyhole = c;
        this.number = number;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            this.cubbyhole.put(i);
            System.out.println("Producer #" + this.number + " put " + i);
            try {
                sleep(1000);
            } catch (InterruptedException e) {}
        }
    }
}
