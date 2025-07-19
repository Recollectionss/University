package org.example;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import transformer.XSLTransformer;

import javax.xml.transform.TransformerException;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.*;

class XSLTransformerTest {

    private String xmlPath;
    private String xslPath;
    private String outputPath;

    @BeforeEach
    void setUp() throws Exception {
        xmlPath = Path.of("src", "test", "resources", "test_candies.xml").toString();
        xslPath = Path.of("src", "test", "resources", "test_transformer.xsl").toString();
        outputPath = Path.of("src", "test", "resources", "test_output.xml").toString();

        // Створення тестового XSL
        Files.writeString(Path.of(xslPath),
                """
                <?xml version="1.0" encoding="UTF-8"?>
                <xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
                    <xsl:template match="/">
                        <transformed>
                            <xsl:apply-templates select="//candy"/>
                        </transformed>
                    </xsl:template>
                    
                    <xsl:template match="candy">
                        <item>
                            <name><xsl:value-of select="name"/></name>
                        </item>
                    </xsl:template>
                </xsl:stylesheet>
                """
        );
    }

    @Test
    void testTransformValidFiles() throws Exception {
        XSLTransformer.transform(xmlPath, xslPath, outputPath);

        File outputFile = new File(outputPath);
        assertTrue(outputFile.exists(), "Output файл повинен існувати");

        String outputContent = Files.readString(Path.of(outputPath));
        assertTrue(outputContent.contains("<name>Chocolate Bar</name>"),
                "Результат повинен містити ім'я трансформованої цукерки");
    }

    @Test
    void testTransformInvalidXSL() {
        String invalidXslPath = Path.of("src", "test", "resources", "invalid_transformer.xsl").toString();

        assertThrows(TransformerException.class, () ->
                XSLTransformer.transform(xmlPath, invalidXslPath, outputPath));
    }

    @Test
    void testTransformMissingFiles() {
        String missingFilePath = "src/test/resources/missing.xml";

        assertThrows(TransformerException.class, () ->
                XSLTransformer.transform(missingFilePath, xslPath, outputPath));
    }
}
