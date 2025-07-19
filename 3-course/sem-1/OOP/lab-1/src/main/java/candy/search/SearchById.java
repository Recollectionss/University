package candy.search;

import candy.model.Candy;

import java.util.ArrayList;

public class SearchById {
    public Candy search(ArrayList<Candy> candies, int id) {
        for (Candy candy : candies) {
            if(candy.getId() == id) {
                return candy;
            }
        }
        return null;
    }
}
