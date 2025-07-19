import candy.enums.CandyType;
import candy.model.Candy;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class CandyTest {

    @Test
    public void testCandyCreationWithValidValues() {
        Candy.CandyBuilder builder = new Candy.CandyBuilder();
        Candy candy = builder.withId(1)
                .withName("Snickers")
                .withCandyType(CandyType.CHOCOLATE)
                .withSugar(50)
                .withPrice(10)
                .withWeight(100)
                .build();

        assertEquals(1, candy.getId());
        assertEquals("Snickers", candy.getName());
        assertEquals(CandyType.CHOCOLATE, candy.getCandyType());
        assertEquals(50, candy.getSugar());
        assertEquals(10, candy.getPrice());
        assertEquals(100, candy.getWeight());
        assertEquals(50, candy.getSugarPercentagePer100g());
    }

    @Test
    public void testCandyBuilderWithDefaultValues() {
        Candy candy = Candy.CandyFactory.generateRandom();
        assertNotNull(candy.getName());
        assertNotNull(candy.getCandyType());
        assertTrue(candy.getSugar() > 0);
        assertTrue(candy.getWeight() > 0);
        assertTrue(candy.getPrice() > 0);
    }

    @Test
    public void testInvalidCandyName() {
        Candy.CandyBuilder builder = new Candy.CandyBuilder();
        assertThrows(IllegalArgumentException.class, () -> builder.withName("abc").build());
    }

    @Test
    public void testInvalidCandySugarValue() {
        Candy.CandyBuilder builder = new Candy.CandyBuilder();
        assertThrows(IllegalArgumentException.class, () -> builder.withSugar(-10).build());
    }

    @Test
    public void testInvalidCandyPrice() {
        Candy.CandyBuilder builder = new Candy.CandyBuilder();
        assertThrows(IllegalArgumentException.class, () -> builder.withPrice(-5).build());
    }

    @Test
    public void testInvalidCandyWeight() {
        Candy.CandyBuilder builder = new Candy.CandyBuilder();
        assertThrows(IllegalArgumentException.class, () -> builder.withWeight(-50).build());
    }

    @Test
    public void testCandySugarPercentageCalculation() {
        Candy.CandyBuilder builder = new Candy.CandyBuilder();
        Candy candy = builder.withName("Twixsss")
                .withCandyType(CandyType.CHOCOLATE)
                .withSugar(30)
                .withPrice(15)
                .withWeight(60)
                .build();

        assertEquals(50, candy.getSugarPercentagePer100g());
    }

    @Test
    public void testSetValidCandyName() {
        Candy.CandyBuilder builder = new Candy.CandyBuilder();
        Candy candy = builder.withName("Twixss")
                .withCandyType(CandyType.CHOCOLATE)
                .withSugar(30)
                .withPrice(15)
                .withWeight(60)
                .build();

        candy.setName("Marsis");
        assertEquals("Marsis", candy.getName());
    }

    @Test
    public void testSetCandySugarUpdatesPercentage() {
        Candy.CandyBuilder builder = new Candy.CandyBuilder();
        Candy candy = builder.withName("KitKat")
                .withCandyType(CandyType.CHOCOLATE)
                .withSugar(20)
                .withPrice(5)
                .withWeight(80)
                .build();

        candy.setSugar(40);
        assertEquals(50, candy.getSugarPercentagePer100g());
    }
}
