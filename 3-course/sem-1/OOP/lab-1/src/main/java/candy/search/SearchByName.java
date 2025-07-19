package candy.search;

import candy.model.Candy;

import java.util.ArrayList;

public class SearchByName {
    public ArrayList<Candy> search(ArrayList<Candy> candies, String name) {
        ArrayList<Candy> result = new ArrayList<>();
        for (Candy candy : candies) {
            if(candy.getName().equals(name)) {
                result.add(candy);
            }
        }
        return result;
    }
}