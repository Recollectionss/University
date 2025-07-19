package org.example;

import candy.Candy;
import org.xml.sax.SAXException;
import parsers.dom.ParserDOM;
import parsers.sax.ParserSAX;
import parsers.stax.ParserStAX;
import transformer.XSLTransformer;
import validator.XMLValidator;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.XMLStreamException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.util.List;

public class App
{
    static final String XML_PATH = "src/candy.xml";
    static final String XSD_PATH = "src/candies.xsd";
    static final String XSL_PATH = "src/candy.xsl";
    static final String OUT_PATH = "src/candy_transform.xml";

    public static void main( String[] args ){
       try{
           ParserDOM.parse(XML_PATH);
           ParserSAX.parse(XML_PATH);
           List<Candy> candyList = ParserStAX.parse(XML_PATH);
           for (Candy candy : candyList) {
//               System.out.println(candy);
               candy.getId();
           }
           XMLValidator.validate(XML_PATH,XSD_PATH);
           XSLTransformer.transform(XML_PATH,XSL_PATH,OUT_PATH);
       }catch(ParserConfigurationException | SAXException | IOException | TransformerException | XMLStreamException e){
           e.printStackTrace();
       }
    }
}
