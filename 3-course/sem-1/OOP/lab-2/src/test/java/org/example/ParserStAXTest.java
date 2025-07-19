package org.example;

import candy.Candy;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import parsers.stax.ParserStAX;

import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;
import java.nio.file.Path;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class ParserStAXTest {

    private String validXmlPath;

    @BeforeEach
    void setUp() {
        validXmlPath = Path.of("src", "test", "resources", "test_candies-2.xml").toString();
    }

    @Test
    void testParseWithValidXML() throws FileNotFoundException, XMLStreamException {
        List<Candy> candies = ParserStAX.parse(validXmlPath);

        assertEquals(1, candies.size(), "Повинна бути 1 цукерка");

        Candy candy = candies.get(0);
        assertEquals("Chocolate Bar", candy.getName());
        assertEquals(250, candy.getEnergy());
        assertEquals("Chocolate", candy.getType());

        assertNotNull(candy.getIngredients());
        assertEquals(0.5f, candy.getIngredients().getWater());
        assertEquals(30.0f, candy.getIngredients().getSugar());

        assertNotNull(candy.getValue());
        assertEquals(2.0, candy.getValue().getProteins());
        assertEquals(10.0, candy.getValue().getFats());
        assertEquals(50.0, candy.getValue().getCarbohydrates());
    }

    @Test
    void testParseWithInvalidXML() {
        String invalidXmlPath = Path.of("src", "test", "resources", "test_invalid.xml").toString();

        assertThrows(FileNotFoundException.class, () -> ParserStAX.parse(invalidXmlPath));
    }
}

