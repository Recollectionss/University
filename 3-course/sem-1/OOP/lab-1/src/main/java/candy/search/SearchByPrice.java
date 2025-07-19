package candy.search;

import candy.model.Candy;

import java.util.ArrayList;

public class SearchByPrice {
    public ArrayList<Candy> search(ArrayList<Candy> candies, int price) {
        ArrayList<Candy> result = new ArrayList<>();
        for (Candy candy : candies) {
            if(candy.getPrice() == price) {
                result.add(candy);
            }
        }
        return result;
    }
}