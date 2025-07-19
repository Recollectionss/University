package org.example;

import org.junit.jupiter.api.Test;
import org.w3c.dom.DOMException;
import parsers.dom.ParserDOM;

import javax.xml.parsers.ParserConfigurationException;
import org.xml.sax.SAXException;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.*;

public class ParserDOMTest {

    @Test
    public void testParse_ValidXML() throws ParserConfigurationException, IOException, SAXException {
        String validXML = """
                <candies>
                    <candy id="1">
                        <name>Chocolate Bar</name>
                        <energy>450</energy>
                        <type>chocolate</type>
                        <production>Sweet Inc.</production>
                        <ingredients>
                            <water>10.0</water>
                            <sugar>35.5</sugar>
                            <fructose>5.0</fructose>
                            <chocolateType>dark</chocolateType>
                            <vanillin>0.5</vanillin>
                        </ingredients>
                        <value>
                            <proteins>5.5</proteins>
                            <fats>20.0</fats>
                            <carbohydrates>60.0</carbohydrates>
                        </value>
                    </candy>
                </candies>
                """;

        Path tempFile = Files.createTempFile("test-valid", ".xml");
        Files.writeString(tempFile, validXML);

        assertDoesNotThrow(() -> ParserDOM.parse(tempFile.toString()));
        Files.deleteIfExists(tempFile);
    }

    @Test
    public void testParse_InvalidXML() {
        String invalidXML = """
                <candies>
                    <candy id="1">
                        <name>Chocolate Bar</name>
                        <energy>450</energy>
                """;

        Path tempFile = null;
        try {
            tempFile = Files.createTempFile("test-invalid", ".xml");
            Files.writeString(tempFile, invalidXML);
            Path finalTempFile = tempFile;
            assertThrows(SAXException.class, () -> ParserDOM.parse(finalTempFile.toString()));
        } catch (IOException e) {
            fail("Unexpected exception: " + e.getMessage());
        } finally {
            if (tempFile != null) {
                try {
                    Files.deleteIfExists(tempFile);
                } catch (IOException ignored) {
                }
            }
        }
    }
}
