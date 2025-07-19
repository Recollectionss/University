package candy.interfaces;

import candy.model.Candy;

import java.util.ArrayList;

public interface CandySearchStrategyInterface {
    ArrayList<Candy> search(ArrayList<Candy> candies);
}
