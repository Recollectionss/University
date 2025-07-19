package transformer;

import javax.xml.transform.*;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import java.io.File;

public class XSLTransformer {
    public static void transform(String xmlPath, String xslPath, String outputPath) throws TransformerException {
        TransformerFactory factory = TransformerFactory.newInstance();
        Source xslt = new StreamSource(new File(xslPath));
        Transformer transformer = factory.newTransformer(xslt);
        Source xml = new StreamSource(new File(xmlPath));
        transformer.transform(xml, new StreamResult(new File(outputPath)));
    }
}