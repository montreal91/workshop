
import java.util.ArrayList;
import java.util.Collections;

public class TrieNode {
    private char letter;
    private long time;
    private static final long NOT_ENTRY = -1;
    private static final long NOT_EXIST = -2;
    private static final int MAX_RESULTS = 12;
    private ArrayList<TrieNode> children;

    public TrieNode(char letter) {
        this.letter = letter;
        this.time = NOT_ENTRY;
        this.children = new ArrayList<TrieNode>();
    }

    public TrieNode(char letter, long time) {
        this.letter = letter;
        this.time = time;
        this.children = new ArrayList<TrieNode>();;
    }

    public char getLetter() {
        return this.letter;
    }

    public ArrayList<TrieNode> getChildren() {
        return this.children;
    }

    public void addChild(TrieNode child) {
        this.children.add(child);
    }

    public void putWord(String word, long time) {
        TrieNode currentNode = this;
        int i = 0;
        while (i < word.length()) {
            boolean foundChild = false;
            for (TrieNode child : currentNode.getChildren()) {
                if (word.charAt(i) == child.getLetter()) {
                    currentNode = child;
                    i++;
                    foundChild = true;
                    break;
                }
            }
            if (!foundChild) {
                TrieNode newNode = new TrieNode(word.charAt(i));
                currentNode.addChild(newNode);
                currentNode = newNode;
                i++;
            }
        }
        currentNode.setTime(time);
    }

    public void setTime(long time) {
        this.time = time;
    }

    public long getTime() {
        return this.time;
    }

    public long keyInTrie(String key) {
        TrieNode currentNode = this;
        int i = 0;
        while (i < key.length()) {
            boolean foundChild = false;
            for (TrieNode child : currentNode.getChildren()) {
                if (key.charAt(i) == child.getLetter()) {
                    currentNode = child;
                    i++;
                    foundChild = true;
                    break;
                }
            }
            if (!foundChild) {
                return NOT_EXIST;
            }
        }
        return currentNode.getTime();
    }

    public TrieNode getNodeByKey(String key) {
        if (this.keyInTrie(key) == NOT_EXIST) {
            return this;
        } else {
            TrieNode currentNode = this;
        int i = 0;
        while (i < key.length()) {
            for (TrieNode child : currentNode.getChildren()) {
                if (key.charAt(i) == child.getLetter()) {
                    currentNode = child;
                    i++;
                    break;
                }
            }
        }
        return currentNode;
        }
    }

    public ArrayList<Pair> getClassNames() {
        StringBuilder sb = new StringBuilder();
        if (this.children.size() == 0) {
            sb.append(this.letter);
            Pair p = new Pair(sb.toString(), this.time);
            ArrayList<Pair> al = new ArrayList<Pair>();
            al.add(p);
            return al;
        } else if (this.time > NOT_ENTRY) {
            ArrayList<Pair> al = new ArrayList<Pair>();
            for (TrieNode child : this.children) {
                al.addAll(child.getClassNames());
            }
            ArrayList<Pair> alRes = new ArrayList<Pair>();
            for (Pair p : al) {
                sb.delete(0, sb.length());
                sb.append(this.letter);
                sb.append(p.getClassName().toCharArray());
                Pair newPair = new Pair(sb.toString(), p.getTime());
                alRes.add(newPair);
            }
            sb.delete(0, sb.length());
            sb.append(this.letter);
            Pair p = new Pair(sb.toString(), this.time);
            alRes.add(p);
            Collections.sort(alRes, Collections.reverseOrder());
            return this.cut(alRes);
        } else {
            ArrayList<Pair> al = new ArrayList<Pair>();
            for (TrieNode child : this.children) {
                al.addAll(child.getClassNames());
            }
            ArrayList<Pair> alRes = new ArrayList<Pair>();
            for (Pair p : al) {
                sb.delete(0, sb.length());
                sb.append(this.letter);
                sb.append(p.getClassName().toCharArray());
                Pair newPair = new Pair(sb.toString(), p.getTime());
                alRes.add(newPair);
            }
            Collections.sort(alRes, Collections.reverseOrder());
            return this.cut(alRes);
        }
    }

    private ArrayList<Pair>cut(ArrayList<Pair> list) {
        if (list.size() < MAX_RESULTS) {
            return list;
        }
        ArrayList<Pair> res = new ArrayList<Pair>(MAX_RESULTS);
        for (int i = 0; i < MAX_RESULTS; i++) {
            res.add(list.get(i));
        }
        return res;
    }
}
