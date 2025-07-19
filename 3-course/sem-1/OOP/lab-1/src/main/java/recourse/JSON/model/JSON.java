package recourse.JSON.model;

import candy.enums.CandyType;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Random;


public class JSON {
    public static String getRandomCandyName() {
        JSONParser parser = new JSONParser();
        try {
            File file = new File("./src/main/java/recourse/JSON/data/CandyInfo.json");
            FileReader reader = new FileReader(file);

            Object obj = parser.parse(reader);
            JSONObject jsonObject = (JSONObject) obj;

            JSONArray namesArray = (JSONArray) jsonObject.get("names");
            Random random = new Random();
            int randomIndex = random.nextInt(namesArray.size());

            return (String) namesArray.get(randomIndex);
        } catch (IOException | ParseException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static CandyType getRandomCandyType(){
        JSONParser parser = new JSONParser();
        try {
            File file = new File("./src/main/java/recourse/JSON/data/CandyInfo.json");
            FileReader reader = new FileReader(file);

            Object obj = parser.parse(reader);
            JSONObject jsonObject = (JSONObject) obj;

            JSONArray namesArray = (JSONArray) jsonObject.get("types");
            Random random = new Random();
            int randomIndex = random.nextInt(namesArray.size());

            String candyTypeStr = (String) namesArray.get(randomIndex);
            return CandyType.valueOf(candyTypeStr);
        }catch (IOException | ParseException e) {
            e.printStackTrace();
            return null;
        }
    }

}
