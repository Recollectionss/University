import DAO.MainDAO.BaseDAO;
import candy.enums.CandyType;
import candy.model.Candy;
import candy.search.RangeSearch;
import candy.search.SearchByCandyType;
import candy.search.SearchById;
import candy.sort.SortByCandyType;
import candy.sort.SortById;
import candy.sort.SortByName;
import candy.sort.SortBySugar;
import gift.model.Gift;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;

public class Main {

    final static String[] mainVariants ={
            "\n1. Create empty gift",
            "2. Create fill in gift",
            "3. Find gift",
            "4. Exit\n",
    };
    final static String[] giftVariants ={
            "Gift menu",
            "1. Add candy",
            "2. Find candies (by id)",
            "3. Remove candy(need find by id)",
            "4. Change info about candy(empty input stay default values)",
            "5. View all candy's",
            "6. View sorted candy",
            "7. Delete gift",
            "9. Exit from this menu",
    };
    final static String[] addCandyVariants ={
            "Add candy :",
            "1. Custom",
            "2. Generate random candy",
            "3. Exit from this menu",
    };
    final static String[] sortVariants ={
            "Sort by:",
            "1. Id",
            "2. Sugar",
            "3. Name",
            "4. Type",
            "5. Exit from this menu",
    };
    final static String[] findVariants ={
            "Sort by:",
            "1. Id",
            "2. Sugar",
            "3. Type",
            "4. Exit from this menu",
    };

    static BaseDAO dao = new BaseDAO();
    static Gift gift = null;
    static Candy candy = null;
    final static int maxGiftId;
    final static int maxCandyId;

    static {
        try {
            maxGiftId = dao.openConnection().getGiftDAO().selectWithMaxId();
            maxCandyId = dao.openConnection().getCandyDAO().selectWithMaxId();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        Candy.readIdCounterFromDb(maxCandyId);
        Gift.readIdCounterFromDb(maxGiftId);
        System.out.println(maxCandyId);
        System.out.println(maxGiftId);
        int selectedOption;
        boolean exit = true;
        while(exit) {
            printVariants(mainVariants);
            selectedOption = getUserInputInt(0,4);
            switch(selectedOption) {
            case 1: {
                gift = new Gift(getUserInputName(true));
                try {
                    dao.openConnection().getGiftDAO().create(gift);
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }
                gift.printGiftInfo();
                if (getUserInputShowMenu(true)) {
                    giftMenu();
                }
                break;
            }
            case 2: {
                gift = new Gift(getUserInputName(true));

                int candyCount;
                System.out.print("Enter candy (must be > 0): ");
                candyCount = getUserInputInt(0,100);

                for (int i = 0; i < candyCount; i++) {
                    gift.addCandy(Candy.CandyFactory.generateRandomForGift(gift.getId()));
                }

                try{
                    dao.openConnection().saveGiftWithCandy(gift).closeConnection();
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }

                gift.printGiftInfo();
                if (getUserInputShowMenu(true)) {
                    giftMenu();
                }
                break;
            }
            case 3:
                int giftId = getUserInputInt(0,maxGiftId);
                try {
                    gift = dao.openConnection().getGiftWithCandy(giftId);
                    dao.closeConnection();
                } catch (SQLException e) {
                    throw new RuntimeException(e);
                }
                giftMenu();
                break;
            case 4:
                exit = false;
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + selectedOption);
            }
        }
    }
    static void giftMenu() {
        int variant;
        boolean exit = true;
        while(exit) {
            printVariants(giftVariants);
            variant = Integer.parseInt(System.console().readLine());
            switch(variant) {
                case 1:
                    addCandyMenu();
                    break;
                case 2:{
                    ArrayList<Candy> find = actionFindCandyVariants();
                    if(!Objects.requireNonNull(find).isEmpty()) {
                        for(Candy candy : find) {
                            candy.printCandyInfo();
                        }
                    }else{
                        System.out.println("No candys found");
                    }
                    break;
                }
                case 3:{
                    int id = getUserInputInt(0,maxCandyId);
                    try{
                        gift.deleteCandy(new SearchById().search(gift.get_candies(),id));
                        System.out.println("Candy successfully deleted");
                    }catch (RuntimeException e) {
                        throw new RuntimeException(e);
                    }
                    break;
                }case 4:{
                    try {
                    int id = getUserInputInt(0,maxCandyId);
                    candy = new SearchById().search(gift.get_candies(),id);
                    candy.printCandyInfo();
                    writeCustomCandyInfo();
                        dao.openConnection().getCandyDAO().update(candy);
                    } catch (SQLException e) {
                        System.out.println(e);
                    }
                    break;
                }case 5:{
                    gift.printGiftInfo();
                    for(Candy candy : gift.get_candies()){
                        candy.printCandyInfo();
                    }
                    break;
                }case 6:{
                    ArrayList<Candy> sort = actionSortCandyVariants();
                    if (sort != null){
                        for(Candy candy : sort) {
                            candy.printCandyInfo();
                        }
                    }
                    break;
                }case 7:{
                    int input = getUserInputInt(0,1);
                    if(input == 1){
                        try {
                            dao.openConnection().deleteGiftWithCandy(gift.getId());
                            System.out.println("Gift successfully deleted");
                        } catch (SQLException e) {
                            throw new RuntimeException(e);
                        }
                    }
                    exit = false;
                    break;
                }
                case 9:
                    exit = false;
                    break;
            }
        }
    }
    static void addCandyMenu(){
        int variant;
        boolean exit = false;
        while(!exit) {
            printVariants(addCandyVariants);
            variant = Integer.parseInt(System.console().readLine());
            switch(variant) {
                case 1:
                    writeNewCandy();
                    try {
                        dao.openConnection().getCandyDAO().create(candy);
                        dao.closeConnection();
                    } catch (SQLException e) {
                        throw new RuntimeException(e);
                    }
                    candy = null;
                    break;
                case 2:
                    candy = Candy.CandyFactory.generateRandomForGift(gift.getId());
                    candy.printCandyInfo();
                    break;
                case 9:
                    exit = true;
                    break;
            }
        }
    }

    static ArrayList<Candy> actionSortCandyVariants(){
        while (true){
            printVariants(sortVariants);
            int input = getUserInputInt(0,6);
            if(input >= 0 && input <= 6){
                switch(input) {
                    case 1 -> {return new SortById().sort(gift.get_candies());}
                    case 2 -> {return new SortBySugar().sort(gift.get_candies());}
                    case 3 -> {return new SortByName().sort(gift.get_candies());}
                    case 4 -> {return new SortByCandyType().sort(gift.get_candies());}
                    case 5 -> {return null;}
                    default -> throw new IllegalStateException("Unexpected value: " + input);
                }
            }
        }
    }
    static ArrayList<Candy> actionFindCandyVariants(){
        ArrayList<Candy> candies = new ArrayList<>();
        printVariants(findVariants);
        int input = getUserInputInt(0,5);

        switch(input) {
            case 1 -> {
                int id = getUserInputInt(0, maxCandyId);
                candies.add(new SearchById().search(gift.get_candies(), id));
                return candies;
            }
            case 2 -> {
                System.out.println("Write min sugar");
                int min = getUserInputInt(0, 1000);
                System.out.println("Write max sugar");
                int max = getUserInputInt(min, 1000);
                return new ArrayList<>(RangeSearch.searchBySugar(gift.get_candies(),min,max)) ;
            }
            case 3 -> {
                CandyType candyType = selectType();
                return new SearchByCandyType().search(gift.get_candies(), candyType);
            }
            case 4 -> {return null;}
        }
        return null;
    }

    static void printVariants(String[] variant){
        for (String s : variant) {
            System.out.println(s);
        }
    }

    private static String getUserInputName(boolean variant){
        String variantName = variant ? "Gift" : "Candy";
        System.out.print("Please enter " + variantName + " name: ");

        String name = "default";

        boolean exit = false;
        while (!exit) {
            name = System.console().readLine();
            if (name.length() > 5){
                exit = true;
            }else {
                System.out.println("Please enter a valid name: ");
            }
        }

        return name;
    }

    private static boolean getUserInputShowMenu(boolean variant){
        String variantName = variant ? "Gift" : "Candy";
        System.out.print("Show menu about this " + variantName + " :  y/n");
        String input;

        while (true) {
            input = System.console().readLine();
            if (input.equals("y") || input.equals("n")) {
                break;
            } else {
                System.out.println("Invalid input. Please enter 'y' or 'n'.");
            }
        }

        return input.equals("y");
    }

    private static int getUserInputInt(int min,int max){
        int input = 0;
        boolean exit = false;
        while (!exit) {
            try {

                input = Integer.parseInt(System.console().readLine());
                if (input < min && !(input < max)){
                    System.out.println("Please enter a valid number.( => 0)");
                }else {
                    exit = true;
                }

            } catch (NumberFormatException e) {
                System.out.println("Please enter a valid number.");
            }
        }

        return input;
    }

    static void writeNewCandy(){
        String name;
        int weight;
        int price;
        int sugar;
        CandyType candyType;

        name = "default";
        weight = 0;
        price = 0;
        sugar = 0;
        candyType = CandyType.DEFAULT;

        System.out.println("Need custom name? (y/n): ");
        if (getUserConfirmation()) {
            System.out.println("Enter name: ");
            name = getUserInputName(false);
        }

        System.out.println("Need custom price? (y/n): ");
        if (getUserConfirmation()) {
            System.out.println("Enter price: ");
            price = getUserInputInt(1, 1000);
        }

        System.out.println("Need custom weight? (y/n): ");
        if (getUserConfirmation()) {
            System.out.println("Enter weight: ");
            weight = getUserInputInt(1, 1000);
        }

        System.out.println("Need custom sugar content? (y/n): ");
        if (getUserConfirmation()) {
            System.out.println("Enter sugar content: ");
            sugar = getUserInputInt(1, 1000);
        }

        System.out.println("Need custom type of candy? (y/n): ");
        if (getUserConfirmation()) {
            candyType = selectType();
        }

        candy = new Candy.CandyBuilder()
                .withGiftId(gift.getId())
                .withSugar(sugar)
                .withPrice(price)
                .withWeight(weight)
                .withName(name)
                .withCandyType(candyType)
                .build();

        candy.printCandyInfo();
    }


    static void writeCustomCandyInfo() {
        String name;
        int weight;
        int price;
        int sugar;
        CandyType candyType;


        System.out.println("Current candy values:");
        System.out.println("Name: " + candy.getName());
        System.out.println("Price: " + candy.getPrice());
        System.out.println("Weight: " + candy.getWeight());
        System.out.println("Sugar: " + candy.getSugar());
        System.out.println("Type: " + candy.getCandyType());

        name = candy.getName();
        price = candy.getPrice();
        weight = candy.getWeight();
        sugar = candy.getSugar();
        candyType = candy.getCandyType();

        System.out.println("Change candy name? (y/n): ");
        if (getUserConfirmation()) {
            System.out.println("Enter name (empty for random): ");
            name = getUserInputName(false);
        }

        System.out.println("Change candy price? (y/n): ");
        if (getUserConfirmation()) {
            System.out.println("Enter price (0 for random value): ");
            price = getUserInputInt(0, 1000);
        }

        System.out.println("Change candy weight? (y/n): ");
        if (getUserConfirmation()) {
            System.out.println("Enter weight (0 for random value): ");
            weight = getUserInputInt(0, 1000);
        }

        System.out.println("Change sugar content? (y/n): ");
        if (getUserConfirmation()) {
            System.out.println("Enter sugar content (0 for random value): ");
            sugar = getUserInputInt(0, 1000);
        }

        System.out.println("Change type of candy? (y/n): ");
        if (getUserConfirmation()) {
            candyType = selectType();
        }

        candy = new Candy.CandyBuilder()
                .withGiftId(gift.getId())
                .withId(candy.getId())
                .withSugar(sugar)
                .withPrice(price)
                .withWeight(weight)
                .withName(name)
                .withCandyType(candyType)
                .build();

        candy.printCandyInfo();
    }

    static Scanner scanner = new Scanner(System.in);
    static boolean getUserConfirmation() {
        String input = scanner.nextLine();
        return input.equalsIgnoreCase("y");
    }

    static CandyType selectType(){
        CandyType candyType;

        while(true){
            System.out.println("Candy type: ");
            System.out.println("0. Default \n1. CHOCOLATE \n2. CARAMEL \n3. GUMMY \n4. HARD_CANDY \n5. LOLLIPOP \n");
            int switchType = getUserInputInt(0, 5);
            if(switchType >= 0 && switchType <= 5){
                candyType = switch (switchType) {
                    case 0 -> CandyType.DEFAULT;
                    case 1 -> CandyType.CHOCOLATE;
                    case 2 -> CandyType.CARAMEL;
                    case 3 -> CandyType.GUMMY;
                    case 4 -> CandyType.HARD_CANDY;
                    case 5 -> CandyType.LOLLIPOP;
                    default -> throw new IllegalStateException("Unexpected value: " + switchType);
                };
                return candyType;
            }
            System.out.println("Unexpected value: " + switchType);
        }
    }
}
