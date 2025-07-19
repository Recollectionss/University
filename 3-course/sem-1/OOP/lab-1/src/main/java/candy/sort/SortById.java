package candy.sort;

import candy.model.Candy;

import java.util.ArrayList;
import java.util.Comparator;

public class SortById implements candy.interfaces.CandySortStrategyInterface {
    @Override
    public ArrayList<Candy> sort(ArrayList<Candy> candies) {
        ArrayList<Candy> sorted =new ArrayList<>(candies);
        sorted.sort(Comparator.comparing(Candy::getId));
        return sorted;
    }
}
