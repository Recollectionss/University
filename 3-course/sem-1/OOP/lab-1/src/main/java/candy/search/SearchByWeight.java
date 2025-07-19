package candy.search;

import candy.model.Candy;

import java.util.ArrayList;

public class SearchByWeight {
    public ArrayList<Candy> search(ArrayList<Candy> candies, int weight) {
        ArrayList<Candy> result = new ArrayList<>();
        for (Candy candy : candies) {
            if(candy.getWeight() == weight) {
                result.add(candy);
            }
        }
        return result;
    }
}
