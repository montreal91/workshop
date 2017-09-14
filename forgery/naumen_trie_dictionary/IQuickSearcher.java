
import java.util.*;

public class IQuickSearcher implements ISearcher {
    private TreeMap<String, Long> index;

    public IQuickSearcher() {
        this.index = new TreeMap<String, Long>();
    }

    /**
    * Обновляет внутренние структуры данных для последующего быстрого поиска
    * @param classNames названия классов в проекте
    * @param modificationDates дата модификации класса в формате мс, прошедших с 1 января 1970 года
    */
    public void refresh(String[] classNames, long[] modificationDates) {
        assert classNames.length == modificationDates.length;
        for (int i = 0; i < classNames.length; i++){
            this.index.put(classNames[i], new Long(modificationDates[i]));
        }
    }

    /**
    * Ищет подходящие имена классов
    * название должно начинаться с start
    * @param start начало имени класса
    * @return массив длины от 0 до 12, имена классов, упорядоченный по дате модификации и лексиграфически.
    */
    public String[] guess(String start) {
        SortedMap<String, Long> subRes = this.index.subMap(start, start + "z");
        Long[] timesArray = subRes.values().toArray(new Long[subRes.size()]);
        Arrays.sort(timesArray);
        int length = 0;
        if (subRes.size() > 12) {
            length = 12;
        } else {
            length = subRes.size();
        }
        String finalRes[] = new String[length];
        for (Map.Entry<String, Long> entry : subRes.entrySet()) {
            Long val = entry.getValue();
            for (int i = 0; i < length; i++) {
                if (val == timesArray[i] && finalRes[i] == null) {
                    finalRes[i] = entry.getKey();
                } else if (val == timesArray[i] && finalRes[i] != null) {
                    continue;
                }
            }
        }
        return finalRes;
    }
}
