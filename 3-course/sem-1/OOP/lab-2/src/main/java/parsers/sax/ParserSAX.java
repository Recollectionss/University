package parsers.sax;

import candy.Candy;
import org.xml.sax.SAXException;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

public class ParserSAX {
    public static void parse(String path) throws ParserConfigurationException, SAXException, IOException {
        SAXParserFactory factory = SAXParserFactory.newInstance();
        SAXParser saxParser = factory.newSAXParser();

        UserHandler userHandler = new UserHandler();

        File xmlFile = new File(path);
        saxParser.parse(xmlFile, userHandler);

    }

    public static List<Candy> parse(InputStream inputStream)
            throws ParserConfigurationException, SAXException, IOException {
        SAXParserFactory factory = SAXParserFactory.newInstance();
        SAXParser saxParser = factory.newSAXParser();

        UserHandler userHandler = new UserHandler();

        saxParser.parse(inputStream, userHandler);
        return userHandler.getCandyList();
    }
}

