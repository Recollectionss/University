package parsers.stax;

import candy.Candy;
import candy.Candy.Ingredients;
import parsers.utils.ParseUtils;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

public class ParserStAX {
    public static List<Candy> parse(String filePath) throws FileNotFoundException, XMLStreamException {
        List<Candy> candyList = new ArrayList<>();
        Candy currentCandy = null;
        Ingredients currentIngredients = null;
        boolean isInValue = false;

        XMLInputFactory factory = XMLInputFactory.newInstance();
        XMLEventReader eventReader = factory.createXMLEventReader(new FileInputStream(filePath));

        while (eventReader.hasNext()) {
            XMLEvent event = eventReader.nextEvent();

            if (event.isStartElement()) {
                StartElement startElement = event.asStartElement();
                String tagName = startElement.getName().getLocalPart();

                switch (tagName) {
                    case "candy":
                        currentCandy = new Candy();
                        String id = startElement.getAttributeByName(new javax.xml.namespace.QName("id")).getValue();
                        currentCandy.setId(id);
                        candyList.add(currentCandy);
                        break;
                    case "ingredients":
                        currentIngredients = new Ingredients();
                        if (currentCandy != null) {
                            currentCandy.setIngredients(currentIngredients);
                        }
                        break;
                    case "value":
                        isInValue = true;
                        break;
                    default:
                        if (currentCandy != null) {
                            String content = getCharacterData(eventReader);
                            if (currentIngredients != null && !isInValue) {
                                ParseUtils.setIngredientsProperty(currentIngredients, tagName, content);
                            } else if (isInValue) {
                                ParseUtils.setValueProperty(currentCandy, tagName, content);
                            } else {
                                ParseUtils.setCandyProperty(currentCandy, tagName, content);
                            }
                        }
                        break;
                }
            }

            if (event.isEndElement()) {
                EndElement endElement = event.asEndElement();
                String tagName = endElement.getName().getLocalPart();

                if ("candy".equals(tagName)) {
                    currentCandy = null;
                } else if ("ingredients".equals(tagName)) {
                    currentIngredients = null;
                } else if ("value".equals(tagName)) {
                    isInValue = false;
                }
            }
        }

        return candyList;
    }

    private static String getCharacterData(XMLEventReader eventReader) throws XMLStreamException {
        XMLEvent event = eventReader.nextEvent();
        if (event instanceof Characters) {
            return event.asCharacters().getData().trim();
        }
        return "";
    }
}

