import candy.model.Candy;
import candy.search.RangeSearch;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class RangeSearchTest {

    @Test
    public void testSearchBySugarInRange() {
        ArrayList<Candy> candies = new ArrayList<>();
        candies.add(new Candy.CandyBuilder()
                .withName("Candy1")
                .withSugar(10)
                .withPrice(5)
                .withWeight(100)
                .build());
        candies.add(new Candy.CandyBuilder()
                .withName("Candy2")
                .withSugar(20)
                .withPrice(10)
                .withWeight(150)
                .build());
        candies.add(new Candy.CandyBuilder()
                .withName("Candy3")
                .withSugar(30)
                .withPrice(15)
                .withWeight(200)
                .build());

        List<Candy> result = RangeSearch.searchBySugar(candies, 15, 25);

        assertEquals(1, result.size());
        assertEquals("Candy2", result.get(0).getName());
    }

    @Test
    public void testSearchBySugarNoCandiesInRange() {
        ArrayList<Candy> candies = new ArrayList<>();
        candies.add(new Candy.CandyBuilder()
                .withName("Candy1")
                .withSugar(10)
                .withPrice(5)
                .withWeight(100)
                .build());
        candies.add(new Candy.CandyBuilder()
                .withName("Candy2")
                .withSugar(20)
                .withPrice(10)
                .withWeight(150)
                .build());

        List<Candy> result = RangeSearch.searchBySugar(candies, 21, 35);

        assertTrue(result.isEmpty());
    }

    @Test
    public void testSearchBySugarEmptyList() {
        ArrayList<Candy> candies = new ArrayList<>();

        List<Candy> result = RangeSearch.searchBySugar(candies, 10, 20);

        assertTrue(result.isEmpty());
    }

    @Test
    public void testSearchBySugarNullList() {
        List<Candy> result = RangeSearch.searchBySugar(null, 10, 20);

        assertTrue(result.isEmpty());
    }

    @Test
    public void testSearchBySugarPercentageInRange() {
        ArrayList<Candy> candies = new ArrayList<>();
        candies.add(new Candy.CandyBuilder()
                .withName("Candy1")
                .withSugar(10)
                .withPrice(5)
                .withWeight(100)
                .build());
        candies.add(new Candy.CandyBuilder()
                .withName("Candy2")
                .withSugar(25)
                .withPrice(10)
                .withWeight(150)
                .build());
        candies.add(new Candy.CandyBuilder()
                .withName("Candy3")
                .withSugar(35)
                .withPrice(15)
                .withWeight(200)
                .build());

        List<Candy> result = RangeSearch.searchBySugarPer100g(candies, 15, 17);

        assertEquals(1, result.size());
        assertEquals("Candy2", result.getFirst().getName());
    }


    @Test
    public void testSearchBySugarPercentageNoCandiesInRange() {
        ArrayList<Candy> candies = new ArrayList<>();
        candies.add(new Candy.CandyBuilder()
                .withName("Candy1")
                .withSugar(10)
                .withPrice(5)
                .withWeight(100)
                .build());
        candies.add(new Candy.CandyBuilder()
                .withName("Candy2")
                .withSugar(20)
                .withPrice(10)
                .withWeight(150)
                .build());

        List<Candy> result = RangeSearch.searchBySugarPer100g(candies, 55, 65);
        assertTrue(result.isEmpty());
    }

    @Test
    public void testSearchBySugarPercentageEmptyList() {
        ArrayList<Candy> candies = new ArrayList<>();

        List<Candy> result = RangeSearch.searchBySugarPer100g(candies, 10, 20);

        assertTrue(result.isEmpty());
    }

    @Test
    public void testSearchBySugarPercentageNullList() {
        List<Candy> result = RangeSearch.searchBySugarPer100g(null, 10, 20);

        assertTrue(result.isEmpty());
    }
}
