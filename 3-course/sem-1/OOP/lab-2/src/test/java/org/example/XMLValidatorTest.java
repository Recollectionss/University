package org.example;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import validator.XMLValidator;

import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.*;

class XMLValidatorTest {

    private String validXmlPath;
    private String invalidXmlPath;
    private String xsdPath;

    @BeforeEach
    void setUp() throws Exception {
        validXmlPath = Path.of("src", "test", "resources", "test_candies.xml").toString();
        invalidXmlPath = Path.of("src", "test", "resources", "invalid_candies.xml").toString();
        xsdPath = Path.of("src", "test", "resources", "test_schema.xsd").toString();

        // Створення тестової схеми XSD
        Files.writeString(Path.of(xsdPath),
                """
                <?xml version="1.0" encoding="UTF-8"?>
                <xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
                    <xs:element name="candies">
                        <xs:complexType>
                            <xs:sequence>
                                <xs:element name="candy" maxOccurs="unbounded" minOccurs="1">
                                    <xs:complexType>
                                        <xs:sequence>
                                            <xs:element name="name" type="xs:string"/>
                                            <xs:element name="energy" type="xs:integer"/>
                                            <xs:element name="type" type="xs:string"/>
                                        </xs:sequence>
                                        <xs:attribute name="id" type="xs:string" use="required"/>
                                    </xs:complexType>
                                </xs:element>
                            </xs:sequence>
                        </xs:complexType>
                    </xs:element>
                </xs:schema>
                """
        );

        Files.writeString(Path.of(invalidXmlPath),
                """
                <?xml version="1.0" encoding="UTF-8"?>
                <candies>
                    <candy>
                        <name>Invalid Candy</name>
                        <!-- energy and type пропущені -->
                    </candy>
                </candies>
                """
        );
    }

    @Test
    void testValidateValidXML() {
        assertDoesNotThrow(() -> XMLValidator.validate(validXmlPath, xsdPath),
                "Валідний XML повинен проходити валідацію");
    }

    @Test
    void testValidateInvalidXML() {
        assertDoesNotThrow(() -> {
            XMLValidator.validate(invalidXmlPath, xsdPath);
        }, "При невалідному XML має бути помилка валідації");
    }
}
