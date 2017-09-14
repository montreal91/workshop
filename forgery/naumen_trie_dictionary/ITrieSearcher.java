
import java.util.ArrayList;

public class ITrieSearcher implements ISearcher {
    private TrieNode root;

    public ITrieSearcher() {
        this.root = new TrieNode(' ');;
    }

    /**
    * Обновляет внутренние структуры данных для последующего быстрого поиска
    * @param classNames названия классов в проекте
    * @param modificationDates дата модификации класса в формате мс, прошедших с 1 января 1970 года
    */
    public void refresh(String[] classNames, long[] modificationDates) {
        assert classNames.length == modificationDates.length;
        for (int i = 0; i < classNames.length; i++){
            this.root.putWord(classNames[i], modificationDates[i]);
        }
    }

    /**
    * Ищет подходящие имена классов
    * название должно начинаться с start
    * @param start начало имени класса
    * @return массив длины от 0 до 12, имена классов, упорядоченный по дате модификации и лексиграфически.
    */
    public String[] guess(String start) {
        TrieNode guessNode = this.root.getNodeByKey(start);
        if (guessNode.getLetter() == this.root.getLetter()) {
            return new String[0];
        } else {
            String prefix = start.substring(0, start.length() - 1);
            ArrayList<Pair> guessPairs = guessNode.getClassNames();
            int len;
            if (guessPairs.size() < 12) {
                len = guessPairs.size();
            } else {
                len = 12;
            }
            String res[] = new String[len];
            for (int i = 0; i < len; i++) {
                res[i] = prefix + guessPairs.get(i).getClassName();
            }
            return res;
        }
    }
}
