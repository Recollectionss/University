package candy.interfaces;

import candy.model.Candy;

import java.sql.SQLException;
import java.util.ArrayList;

public interface CandyDAOInterface {

    void create(Candy candy)throws SQLException;
    void delete(int id)throws SQLException;
    void update(Candy candy)throws SQLException;
    Candy select(int id)throws SQLException;
    ArrayList<Candy> selectAllFromCurrentGift(int giftId)throws SQLException;
    int selectWithMaxId()throws SQLException;

    boolean checkTable() throws SQLException;
    void createTable() throws SQLException;
}
