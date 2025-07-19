package org.example;


import candy.Candy;
import org.junit.jupiter.api.Test;
import org.xml.sax.SAXException;
import parsers.sax.ParserSAX;
import parsers.sax.UserHandler;

import javax.xml.parsers.ParserConfigurationException;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class ParserSAXTest {

    @Test
    void testParseWithValidXML() throws ParserConfigurationException, SAXException, IOException {
        String validXml = """
                <?xml version="1.0"?>
                <candies>
                    <candy id='a1'>
                                    <name>Example Candy</name>
                                    <energy>100</energy>
                                    <type>Chocolate</type>
                                    <ingredients>
                                        <water>0.5</water>
                                        <sugar>25.0</sugar>
                                        <fructose>10.0</fructose>
                                        <chocolateType>Dark</chocolateType>
                                        <vanillin>0.1</vanillin>
                                    </ingredients>
                                    <value>
                                        <proteins>1.5</proteins>
                                        <fats>3.0</fats>
                                        <carbohydrates>20.0</carbohydrates>
                                    </value>
                                    <production>Example Production</production>
                                </candy>
                </candies>
                """;

        ByteArrayInputStream inputStream = new ByteArrayInputStream(validXml.getBytes(StandardCharsets.UTF_8));

        List<Candy> candies = ParserSAX.parse(inputStream);
        assertEquals(1, candies.size(), "Має бути 1 елемент Candy");

        Candy candy = candies.get(0);
        assertEquals("Example Candy", candy.getName());
        assertEquals(100, candy.getEnergy());
        assertEquals("Chocolate", candy.getType());

        assertNotNull(candy.getIngredients());
        assertEquals(0.5f, candy.getIngredients().getWater());
        assertEquals(25.0f, candy.getIngredients().getSugar());
    }

    @Test
    void testParseWithEmptyXML() throws ParserConfigurationException, SAXException, IOException {
        String emptyXml = """
                <?xml version="1.0"?>
                <candies></candies>
                """;

        ByteArrayInputStream inputStream = new ByteArrayInputStream(emptyXml.getBytes(StandardCharsets.UTF_8));
        UserHandler userHandler = new UserHandler();

        ParserSAX.parse(inputStream);

        List<Candy> candies = userHandler.getCandyList();
        assertTrue(candies.isEmpty(), "Список має бути порожнім");
    }

    @Test
    void testParseWithInvalidXML() {
        String invalidXml = """
                <?xml version="1.0"?>
                <candies>
                    <candy>
                        <id>1</id>
                        <name>Chocolate
                        <!-- Помилка: тег закриття відсутній -->
                </candies>
                """;

        ByteArrayInputStream inputStream = new ByteArrayInputStream(invalidXml.getBytes(StandardCharsets.UTF_8));
        UserHandler userHandler = new UserHandler();

        assertThrows(SAXException.class, () -> {
            ParserSAX.parse(inputStream);
        });
    }
}
