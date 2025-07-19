package parsers.dom;

import candy.Candy;
import candy.Candy.Ingredients;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import parsers.utils.ParseUtils;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ParserDOM {
    public static void parse(String path) throws ParserConfigurationException, IOException, SAXException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder docBuilder = factory.newDocumentBuilder();
        Document xmldoc = docBuilder.parse(new File(path));

        Element rootElement = xmldoc.getDocumentElement();
        System.out.println("Root element name is " + rootElement.getTagName());

        NodeList nodes = rootElement.getElementsByTagName("candy");
        List<Candy> candyList = new ArrayList<>();

        for (int i = 0; i < nodes.getLength(); i++) {
            Node node = nodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element candyElement = (Element) node;
                Candy candy = new Candy();

                ParseUtils.setCandyProperty(candy, "id", candyElement.getAttribute("id"));
                ParseUtils.setCandyProperty(candy, "name", ParseUtils.parseStringElement(candyElement, "name"));
                ParseUtils.setCandyProperty(candy, "energy", ParseUtils.parseStringElement(candyElement, "energy"));
                ParseUtils.setCandyProperty(candy, "type", ParseUtils.parseStringElement(candyElement, "type"));
                ParseUtils.setCandyProperty(candy, "production", ParseUtils.parseStringElement(candyElement, "production"));

                Ingredients ingredients = new Ingredients();
                Element ingredientsElement = (Element) candyElement.getElementsByTagName("ingredients").item(0);
                if (ingredientsElement != null) {
                    ParseUtils.setIngredientsProperty(ingredients, "water", ParseUtils.parseStringElement(ingredientsElement, "water"));
                    ParseUtils.setIngredientsProperty(ingredients, "sugar", ParseUtils.parseStringElement(ingredientsElement, "sugar"));
                    ParseUtils.setIngredientsProperty(ingredients, "fructose", ParseUtils.parseStringElement(ingredientsElement, "fructose"));
                    ParseUtils.setIngredientsProperty(ingredients, "chocolateType", ParseUtils.parseStringElement(ingredientsElement, "chocolateType"));
                    ParseUtils.setIngredientsProperty(ingredients, "vanillin", ParseUtils.parseStringElement(ingredientsElement, "vanillin"));
                }
                candy.setIngredients(ingredients);

                Element valueElement = (Element) candyElement.getElementsByTagName("value").item(0);
                if (valueElement != null) {
                    ParseUtils.setValueProperty(candy, "proteins", ParseUtils.parseStringElement(valueElement, "proteins"));
                    ParseUtils.setValueProperty(candy, "fats", ParseUtils.parseStringElement(valueElement, "fats"));
                    ParseUtils.setValueProperty(candy, "carbohydrates", ParseUtils.parseStringElement(valueElement, "carbohydrates"));
                }

                candyList.add(candy);
            }
        }

        for (Candy candy : candyList) {
            System.out.println(candy);
        }
    }
}
