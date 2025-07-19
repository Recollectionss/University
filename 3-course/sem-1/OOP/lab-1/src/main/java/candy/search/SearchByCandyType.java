package candy.search;

import candy.enums.CandyType;
import candy.model.Candy;

import java.util.ArrayList;

public class SearchByCandyType{
    public ArrayList<Candy> search(ArrayList<Candy> candies, CandyType candyType) {
        ArrayList<Candy> result = new ArrayList<>();
        for (Candy candy : candies) {
            if(candy.getCandyType().equals(candyType)) {
                result.add(candy);
            }
        }
        return result;
    }
}
