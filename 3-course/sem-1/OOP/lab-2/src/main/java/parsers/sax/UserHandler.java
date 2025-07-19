//package parsers.sax;
//
//import org.xml.sax.SAXException;
//import org.xml.sax.Attributes;
//import org.xml.sax.helpers.DefaultHandler;
//
//import java.util.Objects;
//
//public class UserHandler extends DefaultHandler {
//    private StringBuilder buffer = new StringBuilder();
//    private int indentLevel = 0;
//
//    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
//        if (Objects.equals(qName, "root")) {
//            System.out.println("Start Element: " + qName);
//        } else {
//           if(Objects.equals(qName, "candy")) {
//               indentLevel++;
//               printIndent();
//               System.out.print(qName + ": ");
//               System.out.print('\n');
//               indentLevel++;
//           }else if(Objects.equals(qName, "value") || Objects.equals(qName, "ingredients")){
//               printIndent();
//               System.out.print(qName + ": ");
//               System.out.print('\n');
//               indentLevel++;
//           }else{
//               printIndent();
//               System.out.print(qName + ": ");
//               indentLevel++;
//           }
//        }
//    }
//
//    public void endElement(String uri, String localName, String qName) {
//        if (Objects.equals(qName, "root")) {
//            System.out.println("End Element: " + qName);
//        } else {
//
//            if (buffer.length() > 0) {
//                System.out.println(buffer.toString().trim());
//            }
//            buffer.setLength(0);
//            if(Objects.equals(qName, "candy")){
//                indentLevel-=2;
//            }else{
//                indentLevel--;
//            }
//        }
//    }
//
//    public void characters(char[] ch, int start, int length) {
//        buffer.append(new String(ch, start, length));
//    }
//
//    private void printIndent() {
//        for (int i = 0; i < indentLevel; i++) {
//            System.out.print("    ");
//        }
//    }
//}
package parsers.sax;

import candy.Candy;
import candy.Candy.Ingredients;
import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;
import parsers.utils.ParseUtils;

import java.util.ArrayList;
import java.util.List;

public class UserHandler extends DefaultHandler {
    private final StringBuilder buffer = new StringBuilder();
    private final List<Candy> candyList = new ArrayList<>();
    private Candy currentCandy = null;
    private Ingredients currentIngredients = null;
    private boolean isInIngredients = false;
    private boolean isInValue = false;

    public List<Candy> getCandyList() {
        return candyList;
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) {
        buffer.setLength(0);

        if ("candy".equals(qName)) {
            currentCandy = new Candy();
            candyList.add(currentCandy);
        } else if ("ingredients".equals(qName)) {
            currentIngredients = new Ingredients();
            isInIngredients = true;
        } else if ("value".equals(qName)) {
            isInValue = true;
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) {
        String content = buffer.toString().trim();

        if ("candy".equals(qName)) {
            if (currentCandy != null && currentIngredients != null) {
                currentCandy.setIngredients(currentIngredients);
            }
            currentCandy = null;
        } else if ("ingredients".equals(qName)) {
            isInIngredients = false;
        } else if ("value".equals(qName)) {
            isInValue = false;
        } else if (currentCandy != null) {
            if (isInIngredients && currentIngredients != null) {
                ParseUtils.setIngredientsProperty(currentIngredients, qName, content);
            } else if (isInValue) {
                ParseUtils.setValueProperty(currentCandy, qName, content);
            } else {
                ParseUtils.setCandyProperty(currentCandy, qName, content);
            }
        }

        buffer.setLength(0);
    }

    @Override
    public void characters(char[] ch, int start, int length) {
        buffer.append(ch, start, length);
    }
}