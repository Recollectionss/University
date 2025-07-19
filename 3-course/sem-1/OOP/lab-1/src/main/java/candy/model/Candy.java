package candy.model;
import candy.enums.CandyType;
import candy.interfaces.CandyInterface;
import recourse.JSON.model.JSON;

public class Candy implements CandyInterface {
    private static int _idCounter = 0;
    private final int _id;
    private String _name;
    private CandyType _candyType;
    private int _sugar;
    private int _price;
    private int _weight;
    int _giftId;

    public void printCandyInfo(){
        System.out.println("//////////////////////////");
        System.out.println("ID: " + _id);
        System.out.println("Name: " + _name);
        System.out.println("CandyType: " + _candyType);
        System.out.println("Sugar: " + _sugar);
        System.out.println("Price: " + _price);
        System.out.println("SugarPercentagePer100g: " + calc_sugarPercentagePer100g());
        System.out.println("Weight: " + _weight);
        System.out.println("//////////////////////////");
    }


    private Candy(int id,String name, CandyType candyType, int sugar, int price, int weight,int giftId) {
        if (id == 0){
            _id = ++_idCounter;
        }else{
            _id = id;
        }
        _name = name;
        _candyType = candyType;
        _sugar = sugar;
        _price = price;
        _weight = weight;
        _giftId = giftId;
    }
    private Candy(){

        _id = 0;
    }

    public static void readIdCounterFromDb(int idCounter){
        if (_idCounter == 0){
            _idCounter = idCounter;
        }
    }

    private int calc_sugarPercentagePer100g() {
        return (int) Math.round(((double) this._sugar / this._weight) * 100);
    }




    public int getId() {return _id;}
    public int getGiftId() {return _giftId;}
    public String getName() {return _name;}
    public CandyType getCandyType() {return _candyType;}
    public int getSugar() {return _sugar;}
    public int getPrice() {return _price;}
    public int getSugarPercentagePer100g() {return calc_sugarPercentagePer100g();}
    public int getWeight() {return _weight;}

    public void setGiftId(int giftId) {this._giftId = giftId;}
    public void setName(String name) {
        if (name.length() <= 5) {
            throw new IllegalArgumentException("Candy's name must have at least 5 characters");
        }
        this._name = name;
    }

    public void setCandyType(CandyType candyType) {
        this._candyType = candyType;
    }

    public void setSugar(int sugar) {
        if (sugar <= 0) {
            throw new IllegalArgumentException("Candy's sugar must have a positive value");
        }
        this._sugar = sugar;
        calc_sugarPercentagePer100g();
    }

    public void setPrice(int price) {
        if (price <= 1) {
            throw new IllegalArgumentException("Candy's price must have a positive value");
        }
        this._price = price;
    }

    public void setWeight(int weight) {
        if (weight <= 1) {
            throw new IllegalArgumentException("Candy's weight must have a positive value");
        }
        this._weight = weight;
        calc_sugarPercentagePer100g();
    }


    public static class CandyBuilder {

        int id;
        String _name;
        CandyType _candyType;
        int _sugar;
        int _price;
        int _weight;
        int _giftId;

        public CandyBuilder() {}

        public CandyBuilder withId(int id) {
            if (id <= 0 && id < _idCounter) {
                throw new IllegalArgumentException("Candy's id must have a positive value");
            }
            this.id = id;
            return this;
        }

        public CandyBuilder withName(String name ){
            if (name.equals("default")){
                name = JSON.getRandomCandyName();
            }
            if(name.length() <= 5){
                throw new IllegalArgumentException("Candy's name must have at least 5 characters");
            }
            this._name = name;
            return this;
        }

        public CandyBuilder withCandyType(CandyType _candyType) {
            if (_candyType == CandyType.DEFAULT){
                _candyType = JSON.getRandomCandyType();
            }
            this._candyType = _candyType;
            return this;
        }

        public CandyBuilder withSugar(int sugar) {
            if (sugar == 0){
                this._sugar = (int)(Math.random()*100) + 1;
                return this;
            }
            if (sugar < 0){
                throw new IllegalArgumentException("Candy's sugar must have a positive value");
            }
            this._sugar = sugar;
            return this;
        }

        public CandyBuilder withPrice(int _price) {
            if (_price == 0){
                this._price = (int)(Math.random()*100) + 1;
                return this;
            }
            if (_price < 0){
                throw new IllegalArgumentException("Candy's price must have a positive value");
            }
            this._price = _price;
            return this;
        }

        public CandyBuilder withWeight(int weight) {
            if (weight == 0) {
                this._weight = (int)(Math.random() * 100) + 1;
            } else if (weight < 0) {
                throw new IllegalArgumentException("Candy's weight must have a positive value");
            } else {
                this._weight = weight;
            }
            return this;
        }

        public CandyBuilder withGiftId(int giftId) {
            this._giftId = giftId;
            return this;
        }

        public Candy build(){
            return new Candy(id,_name, _candyType, _sugar, _price, _weight,_giftId);
        }
    }
    public static class CandyFactory{
        public static Candy generateRandom(){
            return new CandyBuilder().withName("default").withCandyType(CandyType.DEFAULT).withWeight(0).withSugar(0).withPrice(0).build();
        }
        public static Candy generateRandomForGift(int giftId){
            return new CandyBuilder().withName("default").withCandyType(CandyType.DEFAULT).withWeight(0).withSugar(0).withPrice(0).withGiftId(giftId).build();
        }
        public static Candy generateCandyForSearch(){
            return  new Candy();
        }
    }
}