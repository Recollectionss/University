package validator;

import javax.xml.XMLConstants;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import java.io.File;

public class XMLValidator {
    public static void validate(String xmlFilePath, String xsdFilePath) {
        File xmlFile = new File(xmlFilePath);
        File xsdFile = new File(xsdFilePath);

        try {
            SchemaFactory factory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
            Schema schema = factory.newSchema(xsdFile);
            Validator validator = schema.newValidator();
            validator.validate(new StreamSource(xmlFile));
            System.out.println("Good");
        } catch (Exception e) {
            System.out.println("Validation error: " + e.getMessage());
        }
    }
}
