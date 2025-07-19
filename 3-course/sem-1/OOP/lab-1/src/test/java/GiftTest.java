import candy.enums.CandyType;
import candy.model.Candy;
import candy.search.SearchById;
import gift.model.Gift;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

public class GiftTest {

    @Test
    public void testGiftCreationWithNameAndCandies() {
        ArrayList<Candy> candies = new ArrayList<>();
        candies.add(new Candy.CandyBuilder()
                .withName("Candy1")
                .withCandyType(CandyType.CHOCOLATE)
                .withSugar(10)
                .withPrice(15)
                .withWeight(100)
                .build());
        candies.add(new Candy.CandyBuilder()
                .withName("Candy2")
                .withCandyType(CandyType.CARAMEL)
                .withSugar(20)
                .withPrice(10)
                .withWeight(80)
                .build());

        Gift gift = new Gift("Birthday Gift", candies);

        assertEquals("Birthday Gift", gift.getName());
        assertEquals(2, gift.get_candies().size());
        assertEquals(25, gift.getTotalCost());
    }

    @Test
    public void testGiftCreationWithNameOnly() {
        Gift gift = new Gift("Christmas Gift");

        assertEquals("Christmas Gift", gift.getName());
        assertTrue(gift.get_candies().isEmpty());
    }

    @Test
    public void testFindCandyById() {
        Candy candy = new Candy.CandyBuilder()
                .withId(1)
                .withName("Candy1")
                .withCandyType(CandyType.CHOCOLATE)
                .withSugar(10)
                .withPrice(15)
                .withWeight(100)
                .build();

        ArrayList<Candy> candies = new ArrayList<>();
        candies.add(candy);
        Gift gift = new Gift("Gift with One Candy", candies);

        assertEquals(candy, new SearchById().search(gift.get_candies(),1));
    }

    @Test
    public void testFindCandyByIdThrowsException() {
        Gift gift = new Gift("Gift with No Candies");

        assertThrows(IllegalArgumentException.class, () -> gift.findCandyById(1));
    }

    @Test
    public void testAddCandy() {
        Gift gift = new Gift("Gift");

        Candy candy = new Candy.CandyBuilder()
                .withName("Candy1")
                .withCandyType(CandyType.CHOCOLATE)
                .withSugar(10)
                .withPrice(15)
                .withWeight(100)
                .build();

        gift.addCandy(candy);

        assertEquals(1, gift.get_candies().size());
        assertEquals(15, gift.getTotalCost());
    }

    @Test
    public void testDeleteCandy() {
        Candy candy = new Candy.CandyBuilder()
                .withName("Candy1")
                .withCandyType(CandyType.CHOCOLATE)
                .withSugar(10)
                .withPrice(15)
                .withWeight(100)
                .build();

        ArrayList<Candy> candies = new ArrayList<>();
        candies.add(candy);
        Gift gift = new Gift("Gift", candies);

        gift.deleteCandy(candy);

        assertTrue(gift.get_candies().isEmpty());
        assertEquals(0, gift.getTotalCost());
    }

    @Test
    public void testDeleteCandyThrowsException() {
        Gift gift = new Gift("Gift");

        Candy candy = new Candy.CandyBuilder()
                .withName("Candy1")
                .withCandyType(CandyType.CHOCOLATE)
                .withSugar(10)
                .withPrice(15)
                .withWeight(100)
                .build();

        assertThrows(IllegalArgumentException.class, () -> gift.deleteCandy(candy));
    }

    @Test
    public void testSetCandiesThrowsExceptionOnEmptyList() {
        Gift gift = new Gift("Gift");

        assertThrows(IllegalArgumentException.class, () -> gift.setCandies(new ArrayList<>()));
    }

    @Test
    public void testSetNameThrowsExceptionOnNull() {
        Gift gift = new Gift("Gift");

        assertThrows(IllegalArgumentException.class, () -> gift.setName(null));
    }

    @Test
    public void testSetName() {
        Gift gift = new Gift("Gift");
        gift.setName("New Gift");

        assertEquals("New Gift", gift.getName());
    }

    @Test
    public void testConstructorWithInvalidId() {
        assertThrows(IllegalArgumentException.class, () -> new Gift(-1, "Gift"));
    }
}
