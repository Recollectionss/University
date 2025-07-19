package gift.model;

import candy.model.Candy;
import gift.interfaces.GiftInterface;

import java.util.ArrayList;

public class Gift implements GiftInterface {
    private static int _idCounter = 0;
    private final int _id;
    private String _name;
    private ArrayList<Candy> _candies;
    private int _totalCost;


    public Gift(String name,ArrayList<Candy> candies) {
        _id = ++_idCounter;
        _name = name;
        _candies = new ArrayList<Candy>(candies);
        for (Candy candy : candies) {
            _totalCost += candy.getPrice();
        }
    }
    public Gift(String name){
        _id = ++_idCounter;
        _name = name;
        _candies = new ArrayList<>();
    }

    public Gift(int id, String name) {
//        if (id < _idCounter) {
//            throw new IllegalArgumentException("ID must be greater than or equal to " + _idCounter);
//        }
        _id = id;
        _name = name;
    }
    public Gift (int id, String name, ArrayList<Candy> candies) {
//        if (id < _idCounter) {
//            throw new IllegalArgumentException("ID must be greater than or equal to " + _idCounter);
//        }
        _id = id;
        _name = name;
        _candies = candies;
    }

    public void printGiftInfo(){
        System.out.println("//////////////////////////");
        System.out.println("Id:" + _id);
        System.out.println("Name:" + _name);
        System.out.println("TotalCost:" + _totalCost);
        System.out.println("Candies contains:" + _candies.size());
        System.out.println("//////////////////////////");
    }

    public Candy findCandyById(int id){
        for (Candy candy : _candies) {
            if(candy.getId() == id){
                return candy;
            }
        }
        throw new IllegalArgumentException("Candy not found");
    }

    public void addCandy(Candy candy){
        _candies.add(candy);
        _totalCost += candy.getPrice();
    }

    public void deleteCandy(Candy candy){
        if(!_candies.contains(candy)){
            throw new IllegalArgumentException("Candy not found");
        }
        _candies.remove(candy);
        _totalCost -= candy.getPrice();
    }

    public void setCandies(ArrayList<Candy> candies){
        if (candies.isEmpty()){
            throw new IllegalArgumentException("candies size must be not empty");
        }
        for (Candy candy : candies) {
            _totalCost += candy.getPrice();
        }
        _candies = candies;
    }
    public void setName(String name){
        if (name == null){
            throw new IllegalArgumentException("name must not be null");
        }
        _name = name;
    }

    public int getId(){return _id;}
    public String getName(){return _name;}
    public int getTotalCost() {return _totalCost;}
    public ArrayList<Candy> get_candies() {return new ArrayList<>(_candies);}
    public static void readIdCounterFromDb(int idCounter){
        if (_idCounter == 0){
            _idCounter = idCounter;
        }
    }
}
