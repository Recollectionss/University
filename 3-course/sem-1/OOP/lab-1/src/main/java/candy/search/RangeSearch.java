package candy.search;

import candy.model.Candy;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class RangeSearch {

    private static List<Candy> searchByRange(ArrayList<Candy> sortedCandies, int low, int high, Comparator<Candy> comparator) {
        int lowIndex = Collections.binarySearch(sortedCandies, new Candy.CandyBuilder().withSugar((int) ((low * sortedCandies.get(0).getWeight()) / 100.0)).build(), comparator);
        if (lowIndex < 0) {
            lowIndex = -lowIndex - 1;
        }

        int highIndex = Collections.binarySearch(sortedCandies, new Candy.CandyBuilder().withSugar((int) ((high * sortedCandies.get(0).getWeight()) / 100.0)).build(), comparator);
        if (highIndex < 0) {
            highIndex = -highIndex - 2;
        }

        if (lowIndex <= highIndex) {
            return sortedCandies.subList(lowIndex, highIndex + 1);
        }

        return Collections.emptyList();
    }

    private static ArrayList<Candy> getSortedCandies(ArrayList<Candy> candies, Comparator<Candy> comparator) {
        ArrayList<Candy> sortedCandies = new ArrayList<>(candies);
        sortedCandies.sort(comparator);
        return sortedCandies;
    }

    public static List<Candy> searchBySugar(ArrayList<Candy> candies, int low, int high) {
        if (candies == null || candies.isEmpty()) {
            return Collections.emptyList();
        }
        ArrayList<Candy> sortedCandies = getSortedCandies(candies, Comparator.comparingInt(Candy::getSugar));
        return searchByRange(sortedCandies, low, high, Comparator.comparingInt(Candy::getSugar));
    }

    public static List<Candy> searchBySugarPer100g(ArrayList<Candy> candies, int low, int high) {
        if (candies == null || candies.isEmpty()) {
            return Collections.emptyList();
        }
        ArrayList<Candy> sortedCandies = getSortedCandies(candies, Comparator.comparingInt(Candy::getSugarPercentagePer100g));

        List<Candy> result = new ArrayList<>();
        for (Candy candy : sortedCandies) {
            int sugarPercentage = candy.getSugarPercentagePer100g();
            if (sugarPercentage >= low && sugarPercentage <= high) {
                result.add(candy);
            }
        }

        return result;
    }

}

